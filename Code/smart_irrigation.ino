#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
#define SOIL A0
#define RAIN 2
#define IR 3
#define RELAY 4
#define BUZZER 5

// Soil moisture threshold
#define SOIL_THRESHOLD 700

int soilValue;

void setup() {
  pinMode(RAIN, INPUT);
  pinMode(IR, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Active LOW relay: HIGH = Pump OFF
  digitalWrite(RELAY, HIGH);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
}

void loop() {

  // Read sensor values
  soilValue = analogRead(SOIL);
  int rainValue = digitalRead(RAIN);
  int irValue = digitalRead(IR);

  // ---------------- SOIL CONDITION ----------------
  String soilStatus;

  if (soilValue > SOIL_THRESHOLD) {
    soilStatus = "DRY";
  } else {
    soilStatus = "WET";
  }

  // ---------------- RAIN CONDITION ----------------
  String rainStatus;

  if (rainValue == LOW) {
    rainStatus = "YES";
  } else {
    rainStatus = "NO";
  }

  // ---------------- PUMP CONTROL ----------------
  String pumpStatus;

  // Pump ON when soil is dry and there is no rain
  if (soilValue > SOIL_THRESHOLD && rainValue == HIGH) {
    digitalWrite(RELAY, LOW);
    pumpStatus = "ON";
  } else {
    digitalWrite(RELAY, HIGH);
    pumpStatus = "OFF";
  }

  // ---------------- INTRUSION DETECTION ----------------
  String obstacleStatus;

  if (irValue == LOW) {
    digitalWrite(BUZZER, HIGH);
    obstacleStatus = "YES";
  } else {
    digitalWrite(BUZZER, LOW);
    obstacleStatus = "NO";
  }

  // ---------------- LCD DISPLAY ----------------
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.print(soilStatus);
  lcd.print(" R:");
  lcd.print(rainStatus);

  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(pumpStatus);
  lcd.print(" O:");
  lcd.print(obstacleStatus);

  // Serial monitor
  Serial.print("Soil: ");
  Serial.print(soilValue);
  Serial.print(" | Rain: ");
  Serial.print(rainStatus);
  Serial.print(" | Pump: ");
  Serial.print(pumpStatus);
  Serial.print(" | Obstacle: ");
  Serial.println(obstacleStatus);

  delay(1000);
}
