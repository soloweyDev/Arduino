#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <stdio.h>

#define LCD_LED 3  // ШИМ пин подключения подсветки LCD

#define LCD_RENEW 250           // обновление экрана
//****************************
LiquidCrystal_I2C lcd(0x3F,20,4);  // обычно китайские модули I2C для экрана имеют адрес 0x27 или 0x3F

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(1,0);
  lcd.print("SmokeClock");
  lcd.setCursor(3,1);
  lcd.print("voltNik");
  lcd.setCursor(10,2);
  lcd.print("SmokeClock");
  lcd.setCursor(13,3);
  lcd.print("voltNik");
}

void loop()
{
}
