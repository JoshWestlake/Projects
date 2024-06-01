#include <Servo.h>
 
 // Declare servo objects for the motors
Servo leftWheel;
Servo rightWheel;

// Declare servo objects for the motors
Servo myServoA;
Servo myServoB;
 
// Pins assignments
int RED = 10;       // red LED pin
int GRN = 9;        // green LED pin
int YLW = 5;        // yellow LED pin
int BUTTON = 7;     // button pin
int servoPinA = 11; //ServoA
int servoPinB = 12; //servoB

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
int lasterror = 0;
int button = 0;
int myAngleA1 = 180;    // servo angle 1
int myAngleA2 = 110;    // servo angle 2
int posA;

int bucketAngleA1 = 130; // Servo angle Max
int bucketAngleA2 = 110;   // Servo angle Min
int posB = bucketAngleA2; //position of servo
int state = 1; //status of loading


float stopPulse = 145.5;   // stop pulse for motors (nominal = 150)
float Delta = 13;
float turndelta = 26;
int minDelta = 2;
float forOffset = 0.8;    // offset, slows right wheel
float kp = 0.0047;
float kd = 0.004;
float ki = 0;
float integral;


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

   // Set state of button pin
  pinMode(BUTTON, INPUT);

  // Setup servo motor
  myServoA.write(110);         // servo A starting position
  myServoA.attach(servoPinA);   // attaches the servo to the servo object
  myServoB.write(posB);
  myServoB.attach(servoPinB);
  
  // Start serial communication and set baud rate
  Serial.begin(9600);
  
} // end of setup
void loop() {
do{
  flashLED(GRN);
 }while(digitalRead(BUTTON)== LOW);
  do{
    // Read the sensor value
  lSensor = analogRead(LSENSOR);
  rSensor = analogRead(RSENSOR);

  // Read the range sensor value
  rangeSensor = analogRead(SHARP);
  // Map the values into millivolts (assuming 3300 mV reference voltage)
  rangeSensorMv = map(rangeSensor,0,1023,0,3300);

  // Map the values into millivolts (assuming 3000 mV reference voltage)
  lSensor = map(lSensor,0,1023,0,3000);
  rSensor = map(rSensor,0,1023,0,3000);
  
  
  float deltaR;
  float deltaL;
  float error = lSensor -rSensor;
  integral += error;
  float offset = error*kp+integral*ki+(error-lasterror)*kd;
  Serial.println(posA);
  
  
if (-100<error<100)
  {
    integral = 0;
  }
if (rangeSensorMv > 1200 && state == 1)
  {
    runMotors(0,0);
    runMotors( Delta-turndelta-forOffset, Delta );
    delay(1100);
    runMotors(0,0);
    delay(100);
    
  
    for( posA = myServoA.read() ; posA <= myAngleA1; posA ++){
    myServoA.write(posA);
    delay(50);
    }

    runMotors(-13+forOffset, -13);
    delay(1200);
    runMotors(0,0);

    for (posB = myServoB.read(); posB >= 70; posB --) {
    myServoB.write(posB);
    delay(10);
     }
    
    for (posA = myAngleA1; posA >= myAngleA2; posA --) {
    myServoA.write(posA);
    delay(50);
    Serial.println(posA);
        }
  state = 0;
  }
  else if(rangeSensorMv > 1250 && state == 0)
  {
    runMotors(0,0);
    runMotors( Delta-turndelta-forOffset, Delta );
    delay(1100);
    runMotors(0,0);

    runMotors(-13+forOffset, -13);
    delay(600);
    runMotors(0,0);
    delay(100);
    for (posB = 95; posB <= bucketAngleA1; posB ++) {
    myServoB.write(posB);
    delay(5);
  }
  
  delay(100);
  for (posB = bucketAngleA1; posB >= bucketAngleA2; posB --) {
    myServoB.write(posB);
    delay(5);
 
    }
    state = 1;
  }
  
  if(error > 0){
  
  deltaR = Delta;
  deltaL = Delta + offset - forOffset;

  runMotors(deltaL, deltaR);

  }
  else if (error < 0)
  {
  deltaR = Delta - offset;
  deltaL = Delta - forOffset;

  runMotors(deltaL, deltaR);
  }

  if(lSensor > THRESHOLD  && rSensor < THRESHOLD )
  {
    turnOnLED(YLW);
    runMotors(Delta, minDelta);
  }

  else if(rSensor > THRESHOLD && lSensor < THRESHOLD)
  {
    turnOnLED(RED);
    runMotors(minDelta, Delta);
}
  lasterror = error;

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
