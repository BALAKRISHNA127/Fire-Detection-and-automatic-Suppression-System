#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int gasSensorPin = 3;
const int flameSensorPin = 2;
const int gasAlarmPin = 5;
const int pumpPin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(gasSensorPin, INPUT);
  pinMode(flameSensorPin, INPUT);
  pinMode(gasAlarmPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas & Flame");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring...");
  delay(2000);

  digitalWrite(gasAlarmPin, LOW);
  digitalWrite(pumpPin, HIGH);

}

void loop() {
  int gasDetected = digitalRead(gasSensorPin);
  int flameDetected = digitalRead(flameSensorPin);

  // Check gas detection
  if (gasDetected == LOW) {
    Serial.println("Location Alert: https://maps.app.goo.gl/K2H7WjgtyZeRUdeAA Gas detected!");
    digitalWrite(gasAlarmPin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Gas: Detected    ");
    delay(5000);  // Keep the gas alarm on for 5 seconds
    digitalWrite(gasAlarmPin, LOW);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Gas: None        ");
  }

  // Check flame detection
  if (flameDetected == LOW) {
    Serial.println("Location Alert: https://maps.app.goo.gl/K2H7WjgtyZeRUdeAA Flame detected!");
    digitalWrite(pumpPin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Flame: Detected  ");
    delay(5000);
  } else {
    digitalWrite(pumpPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Flame: None      ");
  }

  delay(1000);
}
