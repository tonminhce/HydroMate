/* 
CONNECTION:
X Joystick        - A0
Y Joystick        - A1\\
HUMIDITY SENSOR   - A2
RED LED           - D7
GREEN LED         - D6
PUMP RELAY        - D8
*/

// #include <LiquidCrystal_I2C.h>
// LiquidCrystal_I2C lcd(0x27, 16, 2);
#include "U8glib.h"
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE); 

int xVal = A1;
int yVal = A0;
int wateringLevel = 40;
int humSensor = A3;
bool flag100 = false;
bool flag100level = false;
int delayTime = 200;
int redLight = 7;
int greenLight = 6;
int pumpRelay = 8;
int but = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(pumpRelay, OUTPUT);
  pinMode(humSensor, INPUT);
  pinMode(xVal, INPUT);
  pinMode(yVal, INPUT);
  pinMode(redLight, OUTPUT);
  pinMode(greenLight, OUTPUT);
  u8g.firstPage();
  Serial.begin(9600);
}

void oledPrint(int humPercent, int waterPercent){
  u8g.setFont(u8g_font_9x15B);
  // u8g.setPrintPos(0, 18);
  u8g.drawStr(0,18,"Do am: ");
  u8g.setPrintPos(65,19);
  u8g.print(humPercent);
  u8g.print('%');

  u8g.drawStr(0,30,"Tuoi: ");
  u8g.setPrintPos(65,32);
  u8g.print(waterPercent);
  u8g.print('%');
}

void loop() {
  // put your main code here, to run repeatedly:
  // int x = analogRead(xVal);
  
  if (wateringLevel >= 100) flag100level = true;
  int y = analogRead(yVal);
  
  if (y <= 300 && wateringLevel < 100){
    wateringLevel++;
    //delayTime = 200;
  }else if (y >= 700 && wateringLevel > 0){
    wateringLevel--;
    //delayTime = 200;
  }

  // if (flag100level == true && wateringLevel < 100){
  //   lcd.clear();
  //   flag100level = false;
  // }

  int humVal = analogRead(humSensor);
  int humPercent = map(humVal, 1023, 0, 0, 100);
  // if (humPercent >= 100) flag100 = true;
  // if (flag100 == true && humPercent < 100){
  //   // lcd.clear();
  //   flag100 = false;
  // }
  Serial.print("Do am: "); Serial.println(humPercent);
  Serial.print("Tuoi: "); Serial.println(wateringLevel); //Serial.println('%');
  Serial.println(y);

  if (humPercent <= wateringLevel){
    digitalWrite(redLight, HIGH);
    digitalWrite(greenLight, LOW);
    digitalWrite(pumpRelay, HIGH);
    // Serial.println("Dang tuoi");
  }
  else{
    digitalWrite(redLight, LOW);
    digitalWrite(greenLight, HIGH);
    digitalWrite(pumpRelay, LOW);
    // Serial.println("Khong tuoi");
  }
  u8g.firstPage();
  do{
    oledPrint(humPercent, wateringLevel);
  } while(u8g.nextPage());
  
  // lcd.setCursor(0, 0);
  // lcd.print("Do am: ");
  // lcd.setCursor(7, 0);
  // lcd.print(humPercent);
  // lcd.setCursor(10, 0);
  // lcd.print('%');
  // lcd.setCursor(0, 1);
  // lcd.print("Tuoi: ");
  // lcd.setCursor(6, 1);
  // lcd.print(wateringLevel);
  // lcd.setCursor(9,1);
  // lcd.print('%');

  // int b = digitalRead(but);

  // Serial.print("X: "); Serial.print(x); Serial.print(", ");
  // Serial.print("y: "); Serial.print(y); Serial.print(", ");
  // Serial.print("B: "); Serial.println(b);

  delay(delayTime);
}
