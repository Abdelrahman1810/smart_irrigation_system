#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define moisture sensor pin
int moisturePin = A0;

// Define relay module pins
int relayPin = 7;

// Define LCD connections
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize LCD display
  lcd.init();
  lcd.backlight();
 if (digitalRead(2) == LOW) {
    // Print "Smart Irrigation is ON" to the LCD screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SMART IRRIGATION");
    lcd.setCursor(0, 1);
    lcd.print("is ON");
    // Wait for 4 seconds before returning to the moisture and watering screen
    delay(4000);
  }
  lcd.clear();
  // Initialize relay module pin
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Read moisture sensor value
  int moistureValue = analogRead(moisturePin);

  // Map moisture sensor value to a range of 0-100
  int moisturePercent = map(moistureValue, 0, 1023, 100, 0);

  // Display moisture percentage on LCD
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moisturePercent);
  lcd.print("%");

  // Check moisture level and turn on water pump if needed
  if (moisturePercent < 50) {
    digitalWrite(relayPin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Watering ...");
  } else {
    digitalWrite(relayPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Not Watering");
  }

  // Wait for 1 seconds before reading moisture sensor again
  delay(1000);
}