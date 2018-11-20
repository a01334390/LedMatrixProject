/*
 * Messaging Logic
 * This handles the scrolling logic and implements the LEDControl library
 * https://xantorohara.github.io/led-matrix-editor/#8166661818666681
 * Alpha Team 1.0
 * Built on November 10th, 2018
 * Refactored on November 19th, 2018
 */

#include <avr/pgmspace.h>
#include <LedControl.h>
#include "alphabet.h"

//Se define el numero de paneles a utilizar
#define numDevices 4    
//Definimos la configuracion del panel
#define DIN_PIN 13
#define CLK_PIN 12
#define CS_PIN 11

// Se le añade un delay, mientras más chico mejor
// TODO: Control de delay con un potenciometro
#define DELAY 10
// Buffer del mensaje, con esto deberíamos poder guardar y luego procesar el mensaje
unsigned long messageBff [14] = {0};
// Conectamos el panel con la libreria
LedControl panelController = LedControl(DIN_PIN,CLK_PIN,CS_PIN,numDevices);
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
