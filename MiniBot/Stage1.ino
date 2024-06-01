/************************************************

  MREN104Lab5RangeSensor

  by B. Surgenor, 2021
  updated by D. A. Ells, 2023
  
  This program is intended to calibrate the sharp 
  range sensor on the MiniBot mobile robot.
  
  Place the robot facing target, at a known 
  distance. 
  
  Program prints sensor output in A2D (counts) 
  and millivolt values.
  
************************************************/
 #include <Servo.h>
 
 // Declare servo objects for the motors
Servo leftWheel;
Servo rightWheel;
 
// Pins assignments
int RED = 10;       // red LED pin
int GRN = 9;        // green LED pin
int YLW = 5;        // yellow LED pin
int BUTTON = 7;     // button pin

int SHARP = A3;     // sharp range sensor on analog pin 3
int LSENSOR = A2;   // left line sensor on analog pin 1
int RSENSOR = A1;   // right line sensor on analog pin 2

// Integers
int lSensor = 0;     // left sensor value
int rSensor = 0;     // right sensor value
int rangeSensor = 0;
int rangeSensorMv = 0;
int MOTORL = 4;    // left motor signal pin
int MOTORR = 3;    // right motor signal pin

float stopPulse = 145.5;   // stop pulse for motors (nominal = 150)
float Delta = 12;
float turndelta = 24;
int minDelta = 2;
float forOffset = 1.44;    // offset, slows right wheel

int THRESHOLD = 1500;

// Program setup
void setup() {
                
  // Set state of LED pins
  pinMode(GRN, OUTPUT);
  pinMode(YLW, OUTPUT);
  pinMode(RED, OUTPUT);

  // Set state of button pin
  pinMode(BUTTON, INPUT);

  // Set state of range sensor pin
  pinMode(SHARP, INPUT);

  // Set line following sensor pins as inputs
  pinMode(LSENSOR, INPUT);
  pinMode(RSENSOR, INPUT);

  //Attatch the motor pins to the servo objects
  leftWheel.attach(MOTORL);
  rightWheel.attach(MOTORR);
  runMotors(0,0);       // stop the motors
  
  // Start serial communication and set baud rate
  Serial.begin(9600);
  
} // end of setup

// Program loop starts here
void loop() {
  do{
  
  // Read the range sensor value
  rangeSensor = analogRead(SHARP);
  // Map the values into millivolts (assuming 3300 mV reference voltage)
  rangeSensorMv = map(rangeSensor,0,1023,0,3300);
       
  // Read the sensor value
  lSensor = analogRead(LSENSOR);
  rSensor = analogRead(RSENSOR);

  // Map the values into millivolts (assuming 3000 mV reference voltage)
  lSensor = map(lSensor,0,1023,0,3000);
  rSensor = map(rSensor,0,1023,0,3000);

  if (rangeSensorMv > 1300)
  {
        runMotors(0,0);
        delay(200);
        runMotors( Delta-turndelta-forOffset, Delta );
        delay(1700);
        runMotors(0,0);
        delay(500);
        
  }
  else if (lSensor > THRESHOLD && rSensor > THRESHOLD )
  {
    runMotors( Delta, Delta);
    delay(100);
    runMotors( Delta-turndelta, Delta );
    delay(900);
    runMotors(0,0);
    delay(500);
  }
  
  else if(lSensor > THRESHOLD  && rSensor < THRESHOLD )
  {
    turnOnLED(YLW);
    runMotors(Delta, minDelta);
  }

  else if(rSensor > THRESHOLD && lSensor < THRESHOLD)
  {
    turnOnLED(RED);
    runMotors(minDelta, Delta);
}
  else
  {
   // turnOnLED(GRN);
    runMotors(Delta, Delta+forOffset);
  }
  

  
}while(1);
   
  
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
void runMotors(float deltaL, float deltaR)
{
  float pulseL = (stopPulse + deltaL)*10;   // calculate length of pulse
  float pulseR = (stopPulse + deltaR)*10;   // calculate length of pulse
  leftWheel.writeMicroseconds(pulseR);    // send pulse in microseconds
  rightWheel.writeMicroseconds(pulseL);   // send pulse in microseconds
}
