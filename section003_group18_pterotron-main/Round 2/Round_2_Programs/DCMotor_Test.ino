// Pin Definitions
const int STDBY_PIN = 16; // Standby pin
const int AI1_PIN = 17;   // Motor direction pin 1
const int AI2_PIN = 18;   // Motor direction pin 2
const int PWMA_PIN = 15;  // PWM pin for motor speed

void setup() {
  // Initialize pins
  pinMode(STDBY_PIN, OUTPUT);
  pinMode(AI1_PIN, OUTPUT);
  pinMode(AI2_PIN, OUTPUT);
  pinMode(PWMA_PIN, OUTPUT);

  // Ensure motor is in standby mode initially
  digitalWrite(STDBY_PIN, LOW);
}

void loop() {
  // Example: Run the motor forward at 50% speed for 2 seconds, then reverse
  motorControl(255, true); // Forward, speed 128 (50% of 255)
  delay(2000);

  motorControl(255, false); // Reverse, speed 128
  delay(2000);

  
}

// Function to control motor
void motorControl(int speed, bool forward) {
  digitalWrite(STDBY_PIN, HIGH); // Enable motor controller

  if (forward) {
    digitalWrite(AI1_PIN, HIGH);
    digitalWrite(AI2_PIN, LOW);
  } else {
    digitalWrite(AI1_PIN, LOW);
    digitalWrite(AI2_PIN, HIGH);
  }

  analogWrite(PWMA_PIN, speed); // Set motor speed (0-255)
}

// Function to stop the motor
void motorStop() {
  digitalWrite(STDBY_PIN, LOW); // Disable motor controller
  digitalWrite(AI1_PIN, LOW);
  digitalWrite(AI2_PIN, LOW);
  analogWrite(PWMA_PIN, 0); // Stop motor
}
