#include <LiquidCrystal.h>
#include <iarduino_RTC.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
iarduino_RTC time(RTC_DS1302,3,6,5);

enum PrintFunction
{
  Blink,          // PrintTimeBlink()
  TravelingLine,  // PrintTimeTravelingLine()
};

bool blinked = false;
PrintFunction pf;

void setup()
{
  Serial.begin(115200);
  pinMode(A5, INPUT);

  pf = PrintFunction::TravelingLine;
  time.begin();
  lcd.begin(16, 2);
  //time.settime(01,56,14,30,04,18,1);
}

void loop()
{
  //Serial.println(time.gettime("d.m.y H:i:s D"));
  int delayTime = 0;
  switch(pf)
  {
    case PrintFunction::Blink:
      delayTime = PrintTimeBlink();
      break;
    case PrintFunction::TravelingLine:
      delayTime = PrintTimeTravelingLine();
      break;
  }

  int sensorValue = analogRead(A5);  
  lcd.setCursor(5,1);
  static String s = "T " + String(int(sensorValue/10.23) - 39) + "*C";
  lcd.print(s);
  
  delay(delayTime);
}

int PrintTimeBlink()
{
  lcd.setCursor(0, 0);
    if (blinked)
  {
    lcd.print(time.gettime("d.m.Y H:i:s D"));
    blinked = false;
  }
  else
  {
    lcd.print(time.gettime("d.m.Y H i s D"));
    blinked = true;
  }

  return 500;
}

int PrintTimeTravelingLine()
{
  static char *newString = new char[16];
  static int pos = 15;
  static int pLine = 1;
  
  if (pos == 15)
  {
    lcd.clear();
  }

  static char *string = time.gettime("d.m.Y H:i:s D");
  static int lineSize = strlen(string);
  if (lineSize <= 16)
  {
    lcd.setCursor(pos, 0);
    lcd.print(string);
    pos--;
    if (pos < 0) pos = 15;
  }
  else
  {    
    if(pos == 0)
    {
      strncpy(newString, string + pLine, 16);
      //Serial.println(newString);
      lcd.setCursor(0, 0);
      lcd.print(newString);
      if ((pLine + 16) >= lineSize)
      {
        pLine = 1;
        pos = 15;
        newString = "";
      }
      else
        pLine++;
    }
    else
    {
      lcd.setCursor(pos, 0);
      lcd.print(string);
      pos--;
    }
  }

  return 600;
}

