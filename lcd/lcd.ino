#include <LiquidCrystal.h>
#include <iarduino_RTC.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
iarduino_RTC time(RTC_DS1302,3,6,5);

void setup()
{
  Serial.begin(115200);
  pinMode(A5, INPUT);

  time.begin();
  time.settime(01,47,20,28,04,18,6);
  
  lcd.begin(16, 2);
  
  lcd.setCursor(0,0);
  lcd.write(time.gettime("d.m.Y H:i:s D"));
  
  lcd.setCursor(0,1);
  lcd.write("Tem: ");
}

void loop()
{
  Serial.println(time.gettime("d-m-Y, H:i:s, D"));
  
  int sensorValue = analogRead(A5);
  
  lcd.setCursor(7,1);
  String s = String(float(sensorValue/10.23) - 39.0) + "*C";
  lcd.print(s);
  
  delay(1000);
}
