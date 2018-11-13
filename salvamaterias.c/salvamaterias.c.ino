/*
 * Salvamaterias.c
 * Written in one swift move by:
 * >> Kai
 * >> Jorge
 * >> Andres
 * >> Daniel
 * >> Martin
 * https://xantorohara.github.io/led-matrix-editor/#8166661818666681
 */
 
#include <Keypad.h>
#include "printer.h"
#include "animator.h"

//Predefined Messages
const unsigned char *text1[] = {
    "Aun no sabemos usar apuntadores ",
    "popo"
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
    "Bienvenido al proyecto final de avanzadas, selecciona una opcion:          "
};
const unsigned char op1[] PROGMEM = {
    "Presione alguna tecla del 1 al 10 para un mensaje pregrabado: "
};

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys),rowPins,colPins,ROWS,COLS);


/*
 * We set the board so that:
 * > It starts up in Power saving mode
 * > Intensity is low
 */
void setup(){
    //For the keypad
    Serial.begin(9600);
    //For the LCD Display
    for (int x=0; x<numDevices; x++){
        lc.shutdown(x,false);       
        lc.setIntensity(x,1);      
        lc.clearDisplay(x);         
    }
}

void restartDisplay(){
  for (int x=0; x<numDevices; x++){
        lc.shutdown(x,false);       
        lc.setIntensity(x,1);      
        lc.clearDisplay(x);         
    }
}

int kn_pressed = 1;

void loop(){
  scrollMessage(text10);
  restartDisplay();
  displayMenu();
  while(kn_pressed){
    char customKey = customKeypad.getKey();
    if (customKey){
      Serial.println(customKey);
      switch(customKey){
        case '1':
        restartDisplay();
        scrollMessage(op1);
        //Codigo de seleccion de mensajes
        //Fin seleccion
        restartDisplay();
        displayMenu();
        break;
        case '2':
        //Codigo de animacion
        restartDisplay();
        displayAnimation();
        restartDisplay();
        displayMenu();
        break;
        case '3':
        //Codigo de reloj
        restartDisplay();
        displayMenu();
        break;
        default:
        //Codigo de salida
        restartDisplay();
        kn_pressed = 0;
        break;
      }
    }
  }
}
