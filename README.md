# Led Matrix Project

<a href="https://paypal.me/a01334390"><img src="https://img.shields.io/badge/paypal-donate-blue.svg?longCache=true&style=flat-square" alt="current version" /></a>
<a href="http://twitter.com/A01334390"><img src="https://img.shields.io/badge/twitter-@A01334390-blue.svg?longCache=true&style=flat-square" alt="twitter handle" /></a>
<a href="https://developer.apple.com/swift"><img src="https://img.shields.io/badge/platform-Arduino-blue.svg" alt="Arduino Compatible" /></a>
<a href="https://en.wikipedia.org/wiki/C99"><img src="https://img.shields.io/badge/language-C99-yellow.svg" alt="language" /></a>
<a href="https://en.wikipedia.org/wiki/MIT_License"><img src="https://img.shields.io/badge/license-MIT-lightgray.svg?longCache=true&style=flat-square" alt="license" /></a>

Este es un proyecto de manipulación de una Matríz de LED de 8x32 LEDs utilizando un Arduino UNO R3, el controlador MAX7219 y un teclado de matríx 4x4 para la materia de **Programación Avanzada**. De la misma manera, se está utilizando un display de pantalla líquida para un proyecto de tiempo.

## Partes necesarias para este proyecto
### Para la primer parte del proyecto
* [Matríz de LED de 8x8 con MAX7219 cuadruple](https://www.taloselectronics.com/products/kit-matriz-led-de-8-8-con-max7219-cuadruple)
* [Teclado matricial 4x4](https://www.taloselectronics.com/products/teclado-matricial-4x4)
* [Arduino Uno R3 ATMEGA328](https://www.taloselectronics.com/pages/search-results-page?q=arduino+uno)

### Para la segunda parte del proyecto

* [Arduino Uno R3 ATMEGA328](https://www.taloselectronics.com/pages/search-results-page?q=arduino+uno)
* [Display LCD 16x2 HD44780 con luz de fondo azul](https://www.taloselectronics.com/products/display-lcd-16x2-hd44780-con-luz-de-fondo-azul)
* [Potenciometro de 10K Ohm](https://www.taloselectronics.com/products/potenciometro-miniatura-sin-switch-de-10-k-ohm)
* [Resistencia de 220 Ohm](https://www.taloselectronics.com/products/paquete-de-resistencias-73-valores-diferentes-1460-piezas)
* **OPCIONAL** [Reloj de tiempo RTC1302 con batería e I2C](https://www.taloselectronics.com/products/reloj-de-tiempo-real-rtc1307-con-bateria-e-i2c)

## Cableado del Arduino y componentes
### Primera parte
El link al diagrama de planeacion de cableado en [Fritzing](http://fritzing.org/home/) se encuentra [aqui](https://s3-us-west-1.amazonaws.com/martntn/sls.fzz)
![Diagrama en Fritzing, proyecto 1](https://s3-us-west-1.amazonaws.com/martntn/sls_bb.png)

### Segunda parte
El link al diagrama de planeacion de cableado en [Fritzing](http://fritzing.org/home/) se encuentra [aqui](https://s3-us-west-1.amazonaws.com/martntn/sls+2.fzz)
![Diagrama en Fritzing, proyecto 2](https://s3-us-west-1.amazonaws.com/martntn/wk_bb.png)


# Programación del proyecto
El proyecto fue desarrollado principalmente en C en el estándar '99 para desarrollo en Arduino. Se utilizaron un gran número de librerías Open Source para el manejo del display de matríz de LED tales como:

* [LedControl.h](http://wayoda.github.io/LedControl/pages/software) - Librería para el control de LEDs
* [Keypad.h](https://playground.arduino.cc/code/keypad) - Librería para el control del teclado de matríz
* [LiquidCrystal.h](https://www.arduino.cc/en/Reference/LiquidCrystal) - Librería para el control del cristal líquido

El alfabeto y animaciones fueron creadas usando la página del proyecto de Xantoro Hara en su IDE. Este se encuentra en [esta](https://xantorohara.github.io/led-matrix-editor/) página.

## Código de la aplicación
El principal componente para el manejo de los mensajes en Scroll es con el código a continuación:
```
 /*
 * Print Message
 * Este método imprime el mensaje utilizando el buffer, enmascarando cada bit.
 * PARAMS:  None
 * RETURNS: None
 */
void printMessage(){
    int i;
    // Loop 7 veces por el font de 5 x 7
    for (i=0;i<7;i++){                    
        // Se obtiene el valor bajo de buffer  
        unsigned long x = messageBff [i*2];     
        // Se copia el bit de orden mayor perdido en rotación
        byte b = bitRead(x,31);
        // Se copia el valor perdido en la rotación                 
        x*=2;
        // Se rota el bit a la izquierda                            
        messageBff [i*2] = x;
        // Store new low buffer                   
        x = messageBff [i*2+1];
        // Se obtiene la entrada más alta del buffer
        x*=2;
        // Se rota a la izquierda un bit                        
        bitWrite(x,0,b);
        // Se almacena este bit                      
        messageBff [i*2+1] = x;
        // Se almacena nuevamente este como el mayor valor
    }
    for (i = 0;i < 7; i++){  
        // Se obtiene el valor del buffer               
        unsigned long x = messageBff [i*2+1];
        // Se enmascara el primer caracter   
        byte y = x;           
        // Se envia al chip MAX7219 correspondiente                
        panelController.setRow(3,i,y);                       
        x = messageBff [i*2];  
        // Se enmascara el segundo caracter                    
        y = (x>>24);        
//       Se envia al chip MAX7219 correspondiente
        panelController.setRow(2,i,y);  
        // Se enmascara el tercero caracter                       
        y = (x>>16);
        //Se envia al chip MAX7219 correspondiente
        panelController.setRow(1,i,y);     
        // Se enmascara el cuarto caracter                    
        y = (x>>8);
        //Se envia al chip MAX7219 correspondiente
        panelController.setRow(0,i,y);                       
    }
    delay(DELAY);
}

/*
 * Load Message
 * Este método carga el mensaje a la memoria del buffer
 * PARAMS:  ascii, un caracter en ASCII
 * RETURNS: None
 */
void loadMessage(int ascii){
    if (!(ascii >= 32 && ascii <= 127))
        return;
    for (int i = 0;i < 7;i++){      
        /*estas variables son long porque funcionan como apuntadores que guardan una fila de la letra, 
        podemos cambiarlos a char * que es directamente 
        el pointer pero no se si de errores de compilacion despues 
        y no tengo como estarlo compilando gggg
        */                
        unsigned long c = pgm_read_byte_near(alphabet + ((ascii - 32) << 3) + i); 
        unsigned long x = messageBff [i<<1];     
        /* aqui funciona la magia del scroll, 
         * lo que hace es que va reescribiendo el ultimo caracter con el nuevo, 
         * o sea, la primera vez esta vacio y luego lo va pusheando
         */
        x |= c;                              
        messageBff [i<<1] = x;                   
    }
    ///esta chistoso porque no hay byte en c, ç
    //entonces esta definido en una libreria pero no se cuantos bytes tenga, 
    //tiene mas de uno
    int elementNear = alphabet + ((ascii - 32) << 3) + 7;
    byte count = pgm_read_byte_near(elementNear); 
    for (byte x = 0; x < count; x++){
        printMessage();
    }
}

/*
 * Panel Print
 * Este es el principal método para imprimir el mensaje en el panel
 * PARAMS:  messageString, un mensaje en apuntador de char
 * RETURNS: None
 */
void panelPrint(unsigned char * mssg) {
    int i = 0;
    ///no quiero mover esta funcion pero en teoria podrias manejar esto como un arreglo 
    //y evitar llamar a traer esa funcion entonces solo seria algo como *(messageString)
    int chr = pgm_read_byte_near(mssg);
    while (chr != 0){
        loadMessage(chr);
        i++;
        chr = pgm_read_byte_near(mssg + i);
        //// y aqui seria algo como *(++messageString) aunque no se que pasa cuando llegas al final del arreglo i te regresa 0 o problemas con el pointer
    } 
}
```

El código para el manejo de animaciones es dependiente de cada animación, pero el ejemplo de PacMan se maneja de la siguiente manera:
```
 void displayImage(const byte* image, int panel) {
   for (int i = 0; i< 8; i++) {
      for (int j = 0; j < 8; j++) {
        panelController.setLed(panel, i, j, bitRead(image[i], 7 - j));
      }
    } 
}
```


## Autores

* **Fernando Martin Garcia Del Angel** - *A01334390* - Algoritmo inicial de Scroll y principal cableador
* **Luis Daniel Medina Cazarez** - *A01651070* - Algoritmo avanzado de Scroll de Mensajes y de animaciones
* **Jorge Espinosa Lara** - *A01337002* - Desarrollador del algoritmo de animaciones y mantenedor de Github
* **Andrés Bustamante Díaz** - *A01172912* - Desarollador del programa de reloj y Arduino Consultant
* **Kai Kawasaki Ueda** - *A01336424* - Trabajo inicial, código de manejo del teclado y cableado del display líquido

## Reconocimientos

* Al Dr. Rafael Lozano Espinosa por su apoyo y atención a lo largo de la materia.
