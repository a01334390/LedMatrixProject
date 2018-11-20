#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

const int pinCS = 10;
const int numberOfHorizontalDisplays = 8;
const int numberOfVerticalDisplays = 1;
 
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

const int wait = 20; // Velocidad a la que realiza el scroll
 
const int spacer = 1;
const int width = 5 + spacer;

String cadena[]= {"Prometec","Tutoriales de Arduino","Electronica","Robotica infantil","S4A","Raspberry Pi","Programacion","Arduino","Comunicaciones","Sensores","IoT"};  //textos

void setup() {
	matrix.setIntensity(7); // Ajustar el brillo entre 0 y 15
	Serial.begin(9600);
	// Ajustar segun las necesidades
	matrix.setPosition(0, 0, 0); // El primer display esta en <0, 0>
	matrix.setPosition(1, 1, 0); // El segundo display esta en <1, 0>
	matrix.setPosition(2, 2, 0); // El tercer display esta en <2, 0>
	matrix.setPosition(3, 3, 0); // El cuarto display esta en <3, 0>
	matrix.setPosition(4, 4, 0); // El quinto display esta en <4, 0>
	matrix.setPosition(5, 5, 0); // El sexto display esta en <5, 0>
	matrix.setPosition(6, 6, 0); // El séptimo display esta en <6, 0>
	matrix.setPosition(7, 7, 0); // El octavo display esta en <7, 0>
	matrix.setPosition(8, 8, 0); // El noveno display esta en <8, 0>
	matrix.setRotation(0, 1);    // Posición del display
	matrix.setRotation(1, 1);    // Posición del display
	matrix.setRotation(2, 1);    // Posición del display
	matrix.setRotation(3, 1);    // Posición del display
	matrix.setRotation(4, 1);    // Posición del display
	matrix.setRotation(5, 1);    // Posición del display
	matrix.setRotation(6, 1);    // Posición del display
	matrix.setRotation(7, 1);    // Posición del display
	matrix.setRotation(8, 1);    // Posición del display
}


void printMatrix(String str) {
	String cadena = str;

	for (int i = 0; i < width * cadena.length() + matrix.width() - 1 - spacer; i++) {
		matrix.fillScreen(LOW);
		int letter = i / width;
		int x = (matrix.width() - 1) - i % width;
		int y = (matrix.height() - 8) / 2; // Centrar el texto
		while (x + width - spacer >= 0 && letter >= 0) {
			if (letter < cadena.length()) {
				matrix.drawChar(x, y, cadena[letter], HIGH, LOW, 1);
			}
			letter--;
			x -= width;
		}
		matrix.write(); // Muestra loscaracteres
		delay(wait);
	}

}

int main(int argc, char const *argv[]) {
	/* code */
	int option;
	int option2;
	time_t rawtime;
	struct tm *timeinfo;
	char* mesage;

	printf("Bienvenido al programa del proyecto final de PA, hecho por: un asiatico, un aficionado de disney, un spartan, un mexicano y un mexicano blanco\n");
	printf("Este programa te permite escojer entre varias opciones para mostrar cosas asombrosas en la matriz de LEDs\n");

	do {
		printf("Ingresa la opcion que quieras:\n");
		printf("\t 1) Mostrar la hora actual\n");
		printf("\t 2) Mostrar un mensaje personalizado\n");
		printf("\t 3) Escojer un mensaje predeterminado\n");
		printf("\t 4) Mostrar animación\n");
		printf("\t ingresa 0 para acabar o cualquier otro número mayor a 4\n");
		option = scanf("%d",&option);

		switch(option) {
			case 1 :
				time(&rawtime);
				timeinfo = localtime(&rawtime);
				printf("Current local time %s \n", asctime(timeinfo));
				mesage = asctime(timeinfo);
				break;
			case 2 :
				printf("Ingresa tu mensaje personalizado:\n");
				mesage= scanf("%s", mesage);
				break;

			case 3 :
				printf("Tenemos estos mensajes predeterminados, escoje uno: \n");
				printf("\t 1) Martin es bien gay\n");
				printf("\t 2) Andres es bien gay\n");
				printf("\t 3) Daniel es bien gay\n");
				printf("\t 4) Jorge es bien gay\n");
				printf("\t 5) Kai es bien gay\n");
				option2 = scanf("%d", &option2);
				switch(option2) {
					case 1:
						mesage = "1";
					break;

					case 2:
						mesage = "2";
					break;

					case 3:
						mesage = "3";
					break;

					case 4:
						mesage = "4";
					break;

					case 5:
						mesage = "5";
					break;

					default:
						mesage = "blah";
					break;
				}

				break;

			case 4 :
				printf("Animación desplegandoce\n");
				//mesage = "";
				break;

			default :
				mesage = "CLEAAAAN"
				break;
		}

		printMatrix(mesage);
	}while (opcion > 0 && opcion < 5);
	
	return 0;
}