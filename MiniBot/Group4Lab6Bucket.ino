/************************************************

  MREN104Lab6Bucket

  by D. A. Ells 2023

  Press red button to start. Program lifts and 
  then lowers the bucket once.

************************************************/

// Include servo library
#include <Servo.h>

// Declare servo objects for the motors
Servo myServoA;
Servo myServoB;

// Pins assignments
int RED = 10;       // red LED pin
int GRN = 9;        // green LED pin
int YLW = 5;        // yellow LED pin
int BUTTON = 7;     // button pin

int servoPinA = 11;     // bucket servomotor pin
int servoPinB = 12;     // bucket curl servomotor pin


// Integers

int myAngleA1 = 180;    // servo angle 1
int myAngleA2 = 110;    // servo angle 2
int posA = myAngleA1;   // position of servo 

int bucketAngleA1 = 135; // Servo angle Max
int bucketAngleA2 = 98;   // Servo angle Min
int posB = bucketAngleA2; //position of servo


// Program setup
void setup() {
  
  

  // Set state of LED pins
  pinMode(GRN, OUTPUT);
  pinMode(YLW, OUTPUT);
  pinMode(RED, OUTPUT);

  // Set state of button pin
  pinMode(BUTTON, INPUT);

  // Setup servo motor
  myServoA.write(posA);         // servo A starting position
  myServoA.attach(servoPinA);   // attaches the servo to the servo object
  myServoB.write(posB);
  myServoB.attach(servoPinB);
  
} // end of setup

// Program loop starts here
void loop() {
  
  // Flash green LED while button is not pressed
  do{
    flashLED(GRN);
  }while(digitalRead(BUTTON) == LOW);

  turnOnLED(YLW);   // yellow LED on

  delay (2000);   // delay

  for (posA = myAngleA1; posA >= myAngleA2; posA --) {
    myServoA.write(posA);
    delay(20);
  }
  delay(100);
  for (posB = bucketAngleA2; posB <= bucketAngleA1; posB ++) {
    myServoB.write(posB);
    delay(5);
  }
  delay(1000);
  for (posB = bucketAngleA1; posB >= bucketAngleA2; posB --) {
    myServoB.write(posB);
    delay(5);
  }
  delay(500);

  for (posA = myAngleA2; posA <= myAngleA1; posA ++) {
    myServoA.write(posA);
    delay(20);
  }
  

  delay(1000);   // delay
  
  
} // end of program loop

// Subroutines

// Turn on a single LED and turn others off
void turnOnLED(int COLOUR)
{
  digitalWrite(GRN, LOW);
  digitalWrite(YLW, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(COLOUR, HIGH);
}

// Flash a single LED and turn others off
void flashLED(int COLOUR)
{
  digitalWrite(COLOUR, HIGH);
  delay(125);
  digitalWrite(GRN, LOW);
  digitalWrite(YLW, LOW);
  digitalWrite(RED, LOW);
  delay(125);
}
