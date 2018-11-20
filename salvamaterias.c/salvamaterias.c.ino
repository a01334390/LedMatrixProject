/*
 * Proyecto "Salvamaterias"
 * Escrito por: 
 * >> Kai Kawasaki Ueda - A01336424
 * >> Jorge Espinosa Lara - A01337002
 * >> Andrés Bustamante Díaz - A01172912
 * >> Luis Daniel Medina Cazarez - A01651070
 * >> Fernando Martin Garcia Del Angel
 * Escrito y compilado por ultima vez el 19 de Nov. del 2018
 */

 // Librerias requeridas
#include <Keypad.h>
#include "messages.h"
#include "animator.h"


/* Mensajes predefinidos
 * Estos mensajes se almacenan en Disco (NO RAM) para salvar memoria
 */
const unsigned char text1[] = {
    "Aun no sabemos usar apuntadores "
};
const unsigned char text2[] PROGMEM = {
    "Por que Dios nos hizo asi "
};
const unsigned char text3[] PROGMEM = {
    "A veces siento que debimos ser Lic. en Comunicacion "
};
const unsigned char text4[] PROGMEM = {
    "Estoy seguro que esto nos puede dar un 100% "
};
const unsigned char text5[] PROGMEM = {
    "V A P O R W A V E "
};
const unsigned char text6[] PROGMEM = {
    "Kai no existe, son los papas "
};
const unsigned char text7[] PROGMEM = {
    "Culo el que repruebe "
};
const unsigned char text8[] PROGMEM = {
    "Tengo sed de la MALA! <3 "
};
const unsigned char text9[] PROGMEM = {
    "Si nadie entra a calidad, no nos pueden detener "
};
const unsigned char text10[] PROGMEM = {
    "1 -> 2 -> 3 -> 4 -> 5 -> 6"
};

// Mensajes para el menu

const unsigned char defaulty[] PROGMEM = {
    "Esta opcion no existe"
};

const unsigned char init_m[] PROGMEM = {
   "Bienvenido al proyecto final de avanzadas, selecciona una opcion:     "
};

const unsigned char op1[] PROGMEM = {
    "Selecciona un mensaje pregrabado: "
};

const unsigned char INTENS[] PROGMEM = {
    "Indica una intensidad: "
};

// Codigo para manejar el teclado de matriz de 4x4

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {10, 9, 8, 7}; 
byte colPins[COLS] = {6, 5, 4, 3}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys),rowPins,colPins,ROWS,COLS);

/*
 * El programa inicia en modo de salvado de energia
 * Le damos la intensidad mas baja al inicio y la cambiamos despues
 * Reiniciamos el display
 * Iniciamos una conexion serial para DEBUG
 */
int intensity = 1;

void setup(){
    //For the keypad
    Serial.begin(9600);
    //For the LCD Display
    restartDisplay();
}
/*
 * Restart Display
 * Contiene el codigo para reiniciar el display y darle una intensidad
 * PARAMS: NONE
 * RETURNS: NONE
 */
void restartDisplay(){
  for (int x=0; x<numDevices; x++){
        panelController.shutdown(x,false);       
        panelController.setIntensity(x,intensity);      
        panelController.clearDisplay(x);         
    }
}

/*
 * Main Application loop
 * Corre toda la logica de la aplicacion
 */
void loop(){
  panelPrint(init_m);
  restartDisplay();
  displayMenu();
  //Corre hasta el fin de los tiempos
  while(1){
    //Bloqueamos al sistema para recibir un input
    char customKey = customKeypad.waitForKey();
    if (customKey){
      Serial.println(customKey);
      switch(customKey){
        case '1':
        restartDisplay();
        panelPrint(op1);
        switch(customKeypad.waitForKey()){
          case '1':
          panelPrint(text1);
          break;
          case '2':
          panelPrint(text2);
          break;
          case '3':
          panelPrint(text3);
          break;
          case '4':
          panelPrint(text4);
          break;
          case '5':
          panelPrint(text5);
          break;
          case '6':
          panelPrint(text6);
          break;
          case '7':
          panelPrint(text7);
          break;
          case '8':
          panelPrint(text8);
          break;
          case '9':
          panelPrint(text9);
          break;
          case '0':
          panelPrint(text10);
          break;
          default:
          break;
        }
        //Fin seleccion
        restartDisplay();
        displayMenu();
        break;
        case '2':
        //Codigo de animacion PACMAN
        restartDisplay();
        displayAnimation();
        restartDisplay();
        displayMenu();
        break;
        case '3':
        //Codigo de animacion ARROW
        restartDisplay();
        displayAnimation2();
        restartDisplay();
        displayMenu();
        break;
        case '4':
        restartDisplay();
        panelPrint(INTENS);
        char sel = customKeypad.waitForKey();
        int i_sel = sel - '0';
        intensity = i_sel;
        restartDisplay();
        displayMenu();
        break;
        default:
        restartDisplay();
        panelPrint(defaulty);
        restartDisplay();
        displayMenu();
        break;
      }
    }
  }
}
