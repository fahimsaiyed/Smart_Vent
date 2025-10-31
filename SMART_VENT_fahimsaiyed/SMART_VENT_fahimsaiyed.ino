#include <LiquidCrystal.h>
#include <Servo.h>

// Pin definitions
#define MQ_PIN A0       // Gas sensor analog input
#define TEMP_PIN A1     // Temperature sensor analog input (e.g., LM35)
#define SERVO_PIN 10    // Servo control pin

// LCD pins: RS=12, E=11, D4=5, D5=4, D6=3, D7=2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo windowServo;

// Thresholds
const int gasThreshold = 400;      // Gas sensor threshold
const int tempHigh = 60;           // Temperature high threshold (°C)
const int tempLow = 40;            // Temperature low threshold (°C)

bool isOpen = false;               // Window state

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  windowServo.attach(SERVO_PIN);

  lcd.print("Smart Vent Sys");
  delay(1000);
  lcd.clear();

  windowServo.write(0);  // Start closed
  isOpen = false;
}

void loop() {
  int gasValue = analogRead(MQ_PIN);
  int tempRaw = analogRead(TEMP_PIN);

  // Convert analog reading to temperature in Celsius (assuming LM35, 10mV/°C, 5V ADC ref, 10-bit ADC)
  float voltage = tempRaw * (5.0 / 1023.0);
  int temperature = voltage * 100;  // LM35 output in °C

  // Display sensor values
  lcd.setCursor(0, 0);
  lcd.print("Gas:");
  lcd.print(gasValue);
  lcd.print("    ");

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.print("C ");

  // Control logic:
  // Priority 1: If gas detected above threshold, open window
  if (gasValue > gasThreshold) {
    if (!isOpen) {
      windowServo.write(90);  // Open window
      isOpen = true;
      Serial.println("OPEN - Gas detected");
    }
  } else {
    // Priority 2: Temperature control
    if (temperature > tempHigh && !isOpen) {
      windowServo.write(90);  // Open window
      isOpen = true;
      Serial.println("OPEN - High temp");
    } else if (temperature <= tempLow && isOpen) {
      windowServo.write(0);   // Close window
      isOpen = false;
      Serial.println("CLOSED - Temp normal");
    }
  }

  // Display window status
  lcd.setCursor(10, 1);
  if (isOpen) {
    lcd.print("OPEN ");
  } else {
    lcd.print("CLOSE");
  }

  delay(500);
}