#include <Servo.h>

// Define servo motor pins
const int SERVO1_PIN = 0;
const int SERVO2_PIN = 2;
const int SERVO3_PIN = 4;

// Define motor driver pins
const int PWMA = 27;
const int A12 = 26;
const int A11 = 22;
const int STBY = 16;
const int B11_PIN = 21; // Renamed from B11 to B11_PIN
const int B12 = 20;
const int PWMB = 19;

Servo servo1, servo2, servo3;

void setup() {
    Serial.begin(9600);

    // Attach servos
    servo1.attach(SERVO1_PIN);
    servo2.attach(SERVO2_PIN);
    servo3.attach(SERVO3_PIN);

    // Set motor driver pins as outputs
    pinMode(PWMA, OUTPUT);
    pinMode(A12, OUTPUT);
    pinMode(A11, OUTPUT);
    pinMode(STBY, OUTPUT);
    pinMode(B11_PIN, OUTPUT); // Updated name here
    pinMode(B12, OUTPUT);
    pinMode(PWMB, OUTPUT);

    digitalWrite(STBY, HIGH); // Ensure motors are enabled
}

void loop() {
    // Sweep each servo one after another
    sweepServo(servo1);
    delay(1000);
    
    sweepServo(servo2);
    delay(1000);
    
    sweepServo(servo3);
    delay(1000);

    // Run the motors forward
    runMotors(true);
    delay(2000);

    // Stop motors
    stopMotors();
    delay(1000);

    // Run the motors backward
    runMotors(false);
    delay(2000);

    // Stop motors
    stopMotors();
    delay(1000);
}

// Function to sweep a servo from 0 to 180 and back
void sweepServo(Servo &servo) {
    for (int i = 0; i <= 180; i++) {
        servo.write(i);
        delay(20);
    }

    delay(500);

    for (int i = 180; i >= 0; i--) {
        servo.write(i);
        delay(20);
    }
}

// Function to run motors forward or backward
void runMotors(bool forward) {
    digitalWrite(STBY, HIGH); // Ensure motors are enabled

    if (forward) {
        // Motor A forward
        digitalWrite(A11, LOW);
        digitalWrite(A12, HIGH);
        
        // Motor B forward
        digitalWrite(B11_PIN, HIGH);
        digitalWrite(B12, LOW);
    } else {
        // Motor A backward
        digitalWrite(A11, HIGH);
        digitalWrite(A12, LOW);
        
        // Motor B backward
        digitalWrite(B11_PIN, LOW);
        digitalWrite(B12, HIGH);
    }

    analogWrite(PWMA, 255);
    analogWrite(PWMB, 255);
}

// Function to stop motors
void stopMotors() {
    analogWrite(PWMA, 0);
    analogWrite(PWMB, 0);
}
