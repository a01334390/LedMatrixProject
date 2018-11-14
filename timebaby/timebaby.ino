#include <LiquidCrystal.h>

unsigned int days = 2;
unsigned int hours = 12;
unsigned int minutes = 45;
unsigned int seconds = 45;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void incTime() {
  seconds++;
  if (seconds == 60) {
    seconds = 0;
    minutes++;
    if (minutes == 60) {
      minutes = 0;
      hours++;
      if (hours == 24) {
        hours = 0;
        days++;
        lcd.clear();
        if (days == 7){
          days = 0;
        }
      }
    }
  }
}

void printTime() {
  Serial.begin(9600);
  lcd.setCursor(6,1);
  char time[17];
  sprintf(time, "  %02i:%02i:%02i", hours, minutes, seconds);
  lcd.print(time);
  switch(days){
    case 9:
    lcd.setCursor(0,0);
    lcd.print("lunes");
    break;
    case 1:
    lcd.setCursor(0,0);
    lcd.print("martes");
    break;
    case 2:
    lcd.setCursor(0,0);
    lcd.print("miercoles");
    break;
    case 3:
    lcd.setCursor(0,0);
    lcd.print("jueves");
    break;
    case 4:
    lcd.setCursor(0,0);
    lcd.print("viernes");
    break;
    case 5:
    lcd.setCursor(0,0);
    lcd.print("sabado");
    break;
    case 6:
    lcd.setCursor(0,0);
    lcd.print("domingo");
    break;
  }

  if(hours >= 12){
    lcd.setCursor(14,0);
    lcd.print("PM");
  }else{
   lcd.setCursor(14,0);
   lcd.print("AM");
  }
  
}
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();
}

void loop() {
  incTime();
  printTime();
  delay(1000);
}
