#include <Servo.h> // Include the Servo library

Servo myservo; // Create a servo object to control the servo

void setup() {
  int servoPin = 1; // Use a valid GPIO pin for PWM (e.g., GPIO15)
  int minPulse = 500;  // Minimum pulse width in microseconds
  int maxPulse = 2400; // Maximum pulse width in microseconds

  myservo.attach(servoPin, minPulse, maxPulse); // Attach servo to pin with min and max pulses
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  for (int i = 0; i <= 180; i++) { // Sweep from 0 to 180 degrees
    myservo.write(i); // Move the servo to the current angle
    delay(20);        // Small delay for the servo to move
  }

  delay(1000); // Wait before sweeping back

  for (int i = 180; i >= 0; i--) { // Sweep back from 180 to 0 degrees
    myservo.write(i); // Move the servo to the current angle
    delay(20);        // Small delay for the servo to move
  }

  delay(1000); // Wait before repeating
}
