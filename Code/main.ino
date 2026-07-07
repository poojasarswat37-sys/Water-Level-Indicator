/*
 * Project: Water Level Indicator System
 * Author: Pooja Saraswat & Team
 * Description: Monitors water levels using an analog resistive sensor module.
 * Displays levels via Red, Yellow, and Green LEDs, and triggers 
 * a buzzer alarm when the tank reaches maximum capacity.
 */

// Define Hardware Pin Connections
const int SENSOR_PIN = A0;   // Water level sensor signal pin
const int LED_RED = 13;      // Low level indicator
const int LED_YELLOW = 12;   // Half full indicator
const int LED_GREEN = 11;    // Full tank indicator
const int BUZZER_PIN = 10;   // Alarm buzzer (Add to Pin 10)

// Sensor Calibration Thresholds (Adjust based on testing)
const int THRESHOLD_LOW = 100;    // Red LED turns on above this value
const int THRESHOLD_HALF = 350;   // Yellow LED turns on above this value
const int THRESHOLD_FULL = 600;   // Green LED & Buzzer turn on above this value

void setup() {
  // Initialize Serial Communication for debugging/monitoring
  Serial.begin(9600);
  
  // Configure LED pins as OUTPUT
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  // Configure Buzzer pin as OUTPUT
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Ensure all indicators are OFF initially
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  // Read the analog value from the water level sensor
  int sensorValue = analogRead(SENSOR_PIN);
  
  // Print value to Serial Monitor for testing and calibration
  Serial.print("Sensor Analog Reading: ");
  Serial.println(sensorValue);
  
  // Project Logic: Evaluate water levels based on thresholds
  if (sensorValue < THRESHOLD_LOW) {
    // Condition 1: Tank is completely empty
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  } 
  else if (sensorValue >= THRESHOLD_LOW && sensorValue < THRESHOLD_HALF) {
    // Condition 2: Low water level detected (Red LED Only)
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  } 
  else if (sensorValue >= THRESHOLD_HALF && sensorValue < THRESHOLD_FULL) {
    // Condition 3: Half tank level detected (Red & Yellow LEDs)
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  } 
  else if (sensorValue >= THRESHOLD_FULL) {
    // Condition 4: Tank is Full (All LEDs ON + Buzzer Alarm active)
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH); 
  }
  
  delay(500); // 500ms delay between readings for stability
}
