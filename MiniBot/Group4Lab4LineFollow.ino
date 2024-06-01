/************************************************

  MREN104Lab4LineSensorCheck

  by B. Surgenor, 2021
  updated by D. A. Ells, 2023
  
  This code is to help calibrate the line sensor 
  for your setup. Place the robot on the a white 
  surface or black tape and run the program. 
  
  Obtain the analog values for black tape and 
  white surface using the readings provided in 
  the serial monitor.
  
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

int LSENSOR = A2;   // left line sensor on analog pin 1
int RSENSOR = A1;   // right line sensor on analog pin 2

// Integers
int lSensor = 0;     // left sensor value
int rSensor = 0;     // right sensor value

int MOTORL = 4;    // left motor signal pin
int MOTORR = 3;    // right motor signal pin

float stopPulse = 145.5;   // stop pulse for motors (nominal = 150)
float Delta = 12;
int minDelta = 2;
float forOffset = 1.46;    // offset, slows right wheel

int THRESHOLD = 1500;

// Program setup
void setup() {
                
  // Set state of LED pins
  pinMode(GRN, OUTPUT);
  pinMode(YLW, OUTPUT);
  pinMode(RED, OUTPUT);

  // Set state of button pin
  pinMode(BUTTON, INPUT);

  // Set line following sensor pins as inputs
  pinMode(LSENSOR, INPUT);
  pinMode(RSENSOR, INPUT);

  //Attatch the motor pins to the servo objects
  leftWheel.attach(MOTORL);
  rightWheel.attach(MOTORR);
  runMotors(0,0);       // stop the motors
 
  //serial communication
  Serial.begin(9600);
  
} // end of setup

// Program loop starts here
void loop() {
      do{
        digitalWrite(GRN, HIGH);
        delay(125);
        digitalWrite(GRN, LOW);
        delay(125);
      }while(digitalRead(BUTTON) == LOW);
  
do{
  // Read the sensor value
  lSensor = analogRead(LSENSOR);
  rSensor = analogRead(RSENSOR);

  // Map the values into millivolts (assuming 3000 mV reference voltage)
  lSensor = map(lSensor,0,1023,0,3000);
  rSensor = map(rSensor,0,1023,0,3000);

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

  else
  {
    turnOnLED(GRN);
    runMotors(Delta, Delta+forOffset);
  }
  
  Serial.write("drive");
  
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
// Run the motors
void runMotors(float deltaL, float deltaR)
{
  float pulseL = (stopPulse + deltaL)*10;   // calculate length of pulse
  float pulseR = (stopPulse + deltaR)*10;   // calculate length of pulse
  leftWheel.writeMicroseconds(pulseR);    // send pulse in microseconds
  rightWheel.writeMicroseconds(pulseL);   // send pulse in microseconds
}
