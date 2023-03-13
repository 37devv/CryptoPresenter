#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
StaticJsonDocument<512> doc;

void displayCurrencyPrice(String currency, float price)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(currency);
  lcd.setCursor(0, 1);
  lcd.print(price, 2);
  lcd.print("CHF");
}

void setup()
{
  Serial.begin(115200);
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
    Serial.println("start");
    String jsonString = Serial.readStringUntil('\n');
    Serial.println(jsonString);
    DeserializationError error = deserializeJson(doc, jsonString);
    if (error)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Parsing Error");
    }
    else
    {
      displayCurrencyPrice("BTC/BITCOIN", doc["bitcoin"]["chf"].as<float>());
      delay(2000);
      displayCurrencyPrice("ADA/CARDANO", doc["cardano"]["chf"].as<float>());
      delay(2000);
      displayCurrencyPrice("ETH/ETHEREUM", doc["ethereum"]["chf"].as<float>());
      delay(2000);
      displayCurrencyPrice("LTC/LITECOIN", doc["litecoin"]["chf"].as<float>());
      delay(2000);
      displayCurrencyPrice("XRP/RIPPLE", doc["ripple"]["chf"].as<float>());
      delay(2000);
      displayCurrencyPrice("SOL/SOLANA", doc["solana"]["chf"].as<float>());
    }
  }
  delay(1);
}