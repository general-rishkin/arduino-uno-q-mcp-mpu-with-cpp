#include <Arduino.h>

const auto LED = LED3_G; // Use the built-in red LED on the Arduino board

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  pinMode(LED, OUTPUT);
}

void loop() {
  // Your main code here
  delay(1000);
  digitalWrite(LED, HIGH);
  Serial.println("High!");
  delay(1000);
  digitalWrite(LED, LOW);
  Serial.println("Low!");
}