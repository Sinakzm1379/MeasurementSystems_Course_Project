//adding LCD library

#include<LiquidCrystal.h>
int rs = 7;
int en = 6;
int d4 = 5;
int d5 = 4;
int d6 = 3;
int d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

// adding HX711 library

#include "HX711.h"
int Dout = A0;
int Sck = A1;
long reading;
HX711 scale;

// defining required parameters

int Cal_btn = 12;
int ini_btn = 10;
int CalBtn_cond;
int Ini_cond;
long calibration_factor;
int cal_weight = 100;
float actual_weight;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  scale.begin(Dout,Sck);
  lcd.begin(16,2);
}

void loop() {
  // Calibration process
  lcd.setCursor(0,0);
  Serial.println("remove any weight from the load cell");
  lcd.print("Remove weights");
  delay(3000);
  lcd.setCursor(0,0);
  Serial.println("put a 100g weight on the load cell");
  lcd.print("put 100g weight");
  delay(3000);
  CalBtn_cond = digitalRead(Cal_btn);
 
  while(CalBtn_cond == 1){
    CalBtn_cond = digitalRead(Cal_btn);
    delay(100);
  }
  reading = scale.read();
  calibration_factor = reading/cal_weight;
  Serial.print("calibration factor is: ");
  Serial.println(calibration_factor);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("calibration");
  lcd.setCursor(0,1);
  lcd.print("factor is ");
  lcd.setCursor(11,1);
  lcd.print(calibration_factor, DEC);
  
  while(true){
    Ini_cond = digitalRead(ini_btn);
    delay(100);
    
    if(Ini_cond == 0){
      reading = scale.read();
      actual_weight = reading/calibration_factor;
      Serial.print("Weight = ");
      Serial.print(actual_weight);
      Serial.println(" g");
      delay(500);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("measured weight is:");
      lcd.setCursor(0,1);
      lcd.print(actual_weight,DEC);
      lcd.setCursor(5,1);
      lcd.print("            ");
      lcd.setCursor(7,1);
      lcd.print("g");
      
    }
    
  }
  
}
