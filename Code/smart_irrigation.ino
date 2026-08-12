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

int soilValue;

void setup() {
  pinMode(RAIN, INPUT);
  pinMode(IR, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RELAY, HIGH); // Pump OFF initially (for active LOW relay)

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
}

void loop() {

  // Read sensors
  soilValue = analogRead(SOIL);
  int rainValue = digitalRead(RAIN);
  int irValue = digitalRead(IR);

  // Soil condition
  String soilStatus;
  if (soilValue > 700) {
    soilStatus = "DRY";
  } else {
    soilStatus = "WET";
  }

  // Rain condition
  String rainStatus;
  if (rainValue == LOW) {
    rainStatus = "YES";
  } else {
    rainStatus = "NO";
  }

  // Pump control using IF-ELSE
  String pumpStatus;
  if (soilValue > 700 && rainValue == HIGH) {
    digitalWrite(RELAY, LOW);   // Pump ON (active LOW relay)
    pumpStatus = "ON";
  } else {
    digitalWrite(RELAY, HIGH);  // Pump OFF
    pumpStatus = "OFF";
  }

  // IR + Buzzer
  String obstacleStatus;
  if (irValue == LOW) {
    digitalWrite(BUZZER, HIGH);
    obstacleStatus = "YES";
  } else {
    digitalWrite(BUZZER, LOW);
    obstacleStatus = "NO";
  }

  // Display on LCD
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

  delay(1000);
}
