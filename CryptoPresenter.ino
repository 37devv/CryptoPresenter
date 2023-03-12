#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
StaticJsonDocument<512> doc;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for data");
}

void loop()
{

  if (Serial.available() > 0)
  {

    String jsonString = Serial.readStringUntil('\n');

    DeserializationError error = deserializeJson(doc, jsonString);
    if (error)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Error parsing JSON");
    }
    else
    {

      while (true)
      {

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("BTC/BITCOIN");
        lcd.setCursor(0, 1);
        lcd.print(doc["bitcoin"]["chf"].as<float>(), 2);
        lcd.print("CHF");
        delay(5000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ADA/CARDANO");
        lcd.setCursor(0, 1);
        lcd.print(doc["cardano"]["chf"].as<float>(), 2);
        lcd.print("CHF");
        delay(5000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ETH/ETHEREUM");
        lcd.setCursor(0, 1);
        lcd.print(doc["ethereum"]["chf"].as<float>(), 2);
        lcd.print("CHF");
        delay(5000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LTC/LITECOIN");
        lcd.setCursor(0, 1);
        lcd.print(doc["litecoin"]["chf"].as<float>(), 2);
        lcd.print("CHF");
        delay(5000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("XRP/RIPPLE");
        lcd.setCursor(0, 1);
        lcd.print(doc["ripple"]["chf"].as<float>(), 2);
        lcd.print("CHF");
        delay(5000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SOL/SOLANA");
        lcd.setCursor(0, 1);
        lcd.print(doc["solana"]["chf"].as<float>(), 2);
        lcd.print("CHF");
        delay(5000);
      }
    }
  }
}
