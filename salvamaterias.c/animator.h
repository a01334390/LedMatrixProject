/*
 * Animation Library
 * This handles the animations and menu on the panel
 * https://xantorohara.github.io/led-matrix-editor/#8166661818666681
 * Alpha Team 1.0
 * Built on November 10th, 2018
 * Refactored on November 19th, 2018
 */
 
const byte IMAGES[][8] = {
{
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B10000000,
  B10011000,
  B00011000,
  B10000000,
  B00000000,
  B00000000
},{
  B00000000,
  B10000000,
  B11000000,
  B11011000,
  B00011000,
  B11000000,
  B10000000,
  B00000000
},{
  B10000000,
  B11000000,
  B11100000,
  B11111000,
  B00011000,
  B11100000,
  B11000000,
  B10000000
},{
  B11110000,
  B11100000,
  B11000000,
  B00011000,
  B00011000,
  B11110000,
  B11100000,
  B11000000
},{
  B11111000,
  B11110000,
  B11100000,
  B10011000,
  B10011000,
  B11111000,
  B11110000,
  B11100000
},{
  B11110000,
  B11111000,
  B01111100,
  B11111100,
  B11000000,
  B11111100,
  B11111000,
  B11110000
},{
  B01111000,
  B11111100,
  B10111110,
  B11111110,
  B11100000,
  B11111110,
  B11111100,
  B01111000
},{
  B00111100,
  B01111110,
  B11011111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
},{
  B00111110,
  B01111100,
  B11011000,
  B11110000,
  B11110000,
  B11111110,
  B01111110,
  B00111100
},{
  B00111100,
  B01111110,
  B11011111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
},{
  B00011110,
  B00111111,
  B01101111,
  B01111111,
  B01111000,
  B01111111,
  B00111111,
  B00011110
},{
  B00001111,
  B00011111,
  B00110111,
  B00111111,
  B00111100,
  B00111111,
  B00011111,
  B00001111
},{
  B00000111,
  B00001111,
  B00011011,
  B00011111,
  B00011110,
  B00011111,
  B00001111,
  B00000111
},{
  B00000011,
  B00000111,
  B00001101,
  B00001111,
  B00001111,
  B00001111,
  B00000111,
  B00000011
},{
  B00000001,
  B00000011,
  B00000110,
  B00000111,
  B00000111,
  B00000111,
  B00000011,
  B00000001
},{
  B00000000,
  B00000001,
  B00000011,
  B00000011,
  B00000011,
  B00000011,
  B00000001,
  B00000000
},{
  B00000000,
  B00000000,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
}};
const int IMAGES_LEN = sizeof(IMAGES)/8;

const byte IMAGES2[][8] = {
{
  B00111100,
  B01111110,
  B11011111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
},{
  B00111100,
  B01111110,
  B11011111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
},{
  B00111100,
  B01111110,
  B11011111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
},{
  B00111100,
  B01111110,
  B11011111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
},{
  B00111100,
  B01111110,
  B11011111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
},{
  B00111100,
  B01111110,
  B11111111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
},{
  B00111100,
  B01111110,
  B11111111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
},{
  B00111100,
  B01111110,
  B11011111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
},{
  B00111100,
  B01111110,
  B11011111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
},{
  B00111100,
  B01111110,
  B11011111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
},{
  B00111100,
  B01111110,
  B11011111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
},{
  B00111100,
  B01111110,
  B11011111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
}};
const int IMAGES_LEN2 = sizeof(IMAGES2)/8;

const unsigned char pacwins[] PROGMEM = {
    "PACMAN WINS      "
};
/*
 * Display Image
 * Aplicacion principal para el despliegue de animaciones
 * Escribe LED por LED la animacion en panel
 * PARAMS: image, el arreglo de la imagen. int, el panel a donde enviar la animacion
 * RETURNS: NONE
 */
void displayImage(const byte* image, int panel) {
   for (int i = 0; i< 8; i++) {
      for (int j = 0; j < 8; j++) {
        panelController.setLed(panel, i, j, bitRead(image[i], 7 - j));
      }
    } 
}
/*
 * Display Animation
 * Escribe la animacion de PACMAN
 * PARAMS: NONE
 * RETURNS: NONE
 */
void displayAnimation(){
  //Show initial frame in all panels
  for(int i = 0; i < numDevices; i++){
    displayImage(IMAGES[0], i);
  }
  //Eating Pacman
  for(int panel = numDevices; panel > -1; --panel){
    for(int x = 0; x < IMAGES_LEN; x++){
      displayImage(IMAGES[x], panel);
      delay(10);
    } 
  }
  //Show Pacman wins message
  panelPrint(pacwins);
  //Show Pacman endorsing
  for(int x = 0; x < IMAGES_LEN2; x++){
      displayImage(IMAGES2[x], numDevices-1);
      delay(50);
  }
}

const byte ARROW[][8] = {
{
  B10001000,
  B11001100,
  B11101110,
  B11111111,
  B11111111,
  B11101110,
  B11001100,
  B10001000
},{
  B01000100,
  B01100110,
  B01110111,
  B11111111,
  B11111111,
  B01110111,
  B01100110,
  B01000100
},{
  B00100010,
  B00110011,
  B10111011,
  B11111111,
  B11111111,
  B10111011,
  B00110011,
  B00100010
},{
  B00010001,
  B10011001,
  B11011101,
  B11111111,
  B11111111,
  B11011101,
  B10011001,
  B00010001
}};
const int ARROWS = sizeof(ARROW)/8;

void displayAnimation2(){
  //Show initial frame in all panels
  for(int i = 0; i < numDevices; i++){
    displayImage(ARROW[0], i);
  }

for(int x = 0; x < 10; x++){
 for(int i = 0; i < numDevices; i++){
    displayImage(ARROW[i], 0);
    displayImage(ARROW[i], 1);
    displayImage(ARROW[i], 2);
    displayImage(ARROW[i], 3);
    delay(1);
  } 
}

}

void displayAnimation3(){
  //Show initial frame in all panels
  for(int i = 0; i < numDevices; i++){
    displayImage(IMAGES[0], i);
  }
  //Eating Pacman
  for(int panel = numDevices; panel > -1; --panel){
    for(int x = 0; x < IMAGES_LEN; x++){
      displayImage(IMAGES[x], panel);
      delay(10);
    } 
  }
  //Show Pacman wins message
  panelPrint(pacwins);
  //Show Pacman endorsing
  for(int x = 0; x < IMAGES_LEN2; x++){
      displayImage(IMAGES2[x], numDevices-1);
      delay(50);
  }
}



const byte CLOCK[][8] = {
{
  B00111100,
  B01110110,
  B11010011,
  B10010001,
  B10011101,
  B11000011,
  B01100110,
  B00111100
}};
const int CLOCK_LEN = sizeof(CLOCK)/8;

const byte PACMAN[][8] = {
{
  B00111100,
  B01111110,
  B11011111,
  B11111111,
  B11110000,
  B11111111,
  B01111110,
  B00111100
}};
const int PACMAN_LEN = sizeof(PACMAN)/8;

const byte MESSAGE[][8] = {
{
  B01111110,
  B10111101,
  B11011011,
  B11100111,
  B11111111,
  B11111111,
  B11111111,
  B11111111
}};
const int MESSAGE_LEN = sizeof(MESSAGE)/8;


const byte INTENSITY[][8] = {
{
  B00000000,
  B00001000,
  B00011100,
  B00111110,
  B00111110,
  B00100010,
  B00100010,
  B00000010
}};
const int INTENSITY_LEN = sizeof(INTENSITY)/8;


void displayMenu(){
  displayImage(MESSAGE[0],numDevices-1);
  displayImage(PACMAN[0],numDevices-2);
  displayImage(ARROW[0],numDevices-3);
  displayImage(INTENSITY[0],numDevices-4);
}
