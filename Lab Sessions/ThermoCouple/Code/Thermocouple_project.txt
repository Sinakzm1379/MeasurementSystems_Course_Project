#include <SPI.h>
//#include <Wire.h>
#include "Adafruit_MAX31855.h"

#include <LiquidCrystal.h>
int rs = 8;
int en = 9;
int d4 = 10;
int d5 = 11;
int d6 = 12;
int d7 = 13;

#define SO   3
#define CS   4
#define SCK  2

Adafruit_MAX31855 Thermocouple(SCK,CS,SO);
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

float int_temp;
float temp;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  delay(500); // waiting for max to stabilize
  lcd.clear();
  
}

void loop() {
  
    lcd.clear();
    lcd.setCursor(0,0);
    int_temp = Thermocouple.readInternal();
    lcd.print("Int Temp ");
    lcd.print(int_temp);
    temp = Thermocouple.readCelsius();
    lcd.setCursor(0,1);
    lcd.print("Temp is ");
    lcd.print(temp-int_temp+1.5);
    delay(1000);
    
}
