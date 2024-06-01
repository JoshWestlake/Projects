/************************************************

  MREN104Lab3MiniBotDeadZone

  by B. Surgenor, 2021
  updated by D. A. Ells, 2023

  This program is used to calibrate the stop 
  speed deadband of your MiniBot. 
  
  The Serial monitor needs to be opened to run 
  the program. 

  At the start, the robot will move at a speed of 
  140 (backwards). Pressing red button will 
  increment the speed by one. 
  
  Use the program to determine the motor dead zone.
  
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

int stopPulse = 150;   // stop pulse for motors (nominal = 150)
int delta = -10;        // pulse delta

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

  // Open serial monitor
  //do {
    //turnOnLED(YLW);
  //} while(!Serial);       // while the serial monitor is not open
  
  Serial.println("Program ready. Make sure power on and wheels off ground.");
  
  // Test the green LED
  Serial.println("Check GREEN LED is flashing. Press red button to advance...");
  do {
    toggleLED(GRN);
  } while(digitalRead(BUTTON)== LOW);
  delay(500);

  Serial.print("Speed pulse is ");
  Serial.print(stopPulse+delta);
  Serial.println(". Press button to increase speed by 1.");

  do {

    runMotors(delta,delta);
   
    if(digitalRead(BUTTON)== HIGH){
      delta = delta+1;
      Serial.print("Speed pulse is ");
      Serial.print(stopPulse+delta);
      Serial.println(". Press button to increase speed by 1.");
    }
    delay(500);
  
  } while(1);
  
} // end of program loop

// Subroutines

// Run the motors
void runMotors(int deltaL, int deltaR)
{
  int pulseL = (stopPulse + deltaL)*10;   // calculate length of pulse
  int pulseR = (stopPulse + deltaR)*10;   // calculate length of pulse
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
