/************************************************

  MREN104Lab3MiniBotForwardBack

  by B. Surgenor, 2021
  updated by D. A. Ells, 2023

  This program is used to calibrate the motors 
  and speed of your MiniBot. 
  The robot goes forward for 2 seconds, pauses, 
  then reverses for 2 sec.
  Change delta to change the speed of your robot.
  
************************************************/

// Include servo library
#include <Servo.h>

// Declare servo objects for the motors
Servo leftWheel;
Servo rightWheel;

// Pins assignments
int RED = 10;       // red LED pin
int GRN = 9;        // green LED pin
int YLW = 5;        // yellow LED pin
int BUTTON = 7;     // button pin

int MOTORL = 4;    // left motor signal pin
int MOTORR = 3;    // right motor signal pin

float stopPulse = 145.5;    // stop pulse for motors (nominal = 150)
float delta = 15;         // pulse delta
float forOffset = 1.4;   // offset, slows right wheel
float turnDelta = 30;

// Program setup
void setup() {
                
  // Set state of LED pins
  pinMode(GRN, OUTPUT);
  pinMode(YLW, OUTPUT);
  pinMode(RED, OUTPUT);

  // Set state of button pin
  pinMode(BUTTON, INPUT);

  // Attach the motor pins to the servo objects
  leftWheel.attach(MOTORL);
  rightWheel.attach(MOTORR);
  runMotors(0,0);       // stop the motors

  // Initialize serial communication
  Serial.begin(9600);

} // end of setup

// Program loop starts here
void loop() {
  
  // Press button to start
  do {
    toggleLED(GRN);
  } while(digitalRead(BUTTON)== LOW);
  delay(500);
  
  // Drive forward
  turnOnLED(RED);
  runMotors(delta, delta-forOffset);
  delay(3500);
  
  // Stop
  turnOnLED(YLW);
  runMotors(0,0);
  delay(1000); 

  //Rotate
  runMotors(delta, delta-turnDelta);
  delay(830);
// Stop
  turnOnLED(YLW);
  runMotors(0,0);
  delay(5000); 
  // Drive forward
  turnOnLED(RED);
  runMotors(delta, delta-forOffset);
  delay(3500);
  
  // Stop
  turnOnLED(YLW);
  runMotors(0,0);
  delay(1000); 

  //Rotate
  runMotors(delta, delta-turnDelta);
  delay(830);
  
  // Stop
  turnOnLED(YLW);
  runMotors(0,0);
  delay(1000); 
  
} // end of program loop

// Subroutines

// Run the motors
void runMotors(float deltaL, float deltaR)
{
  float pulseL = (stopPulse + deltaL)*10;   // calculate length of pulse
  float pulseR = (stopPulse + deltaR)*10;   // calculate length of pulse
  leftWheel.writeMicroseconds(pulseL);    // send pulse in microseconds
  rightWheel.writeMicroseconds(pulseR);   // send pulse in microseconds
}

// Turn on a single LED and turn others off
void turnOnLED(int COLOUR)
{
  digitalWrite(GRN, LOW);
  digitalWrite(YLW, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(COLOUR, HIGH);
}

// Flash an LED on and off
void toggleLED(int colour){
  digitalWrite(GRN, LOW);
  digitalWrite(YLW, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(colour, HIGH);
  delay(250);
  digitalWrite(colour, LOW);
  delay(250); 
}
