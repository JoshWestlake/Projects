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
 
// Pins assignments
int RED = 10;       // red LED pin
int GRN = 9;        // green LED pin
int YLW = 5;        // yellow LED pin
int BUTTON = 7;     // button pin

int SHARP = A3;     // sharp range sensor on analog pin 3

// Integers
int rangeSensor = 0;
int rangeSensorMv = 0;
    
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
  
  // Start serial communication and set baud rate
  Serial.begin(9600);
  
} // end of setup

// Program loop starts here
void loop() {

  // Open serial monitor
  do {
    turnOnLED(YLW);
  } while(!Serial);   // while the serial monitor is not open

  Serial.println();
  Serial.println("Press button to take a reading...");
  do{
    flashLED(GRN);
  }while(digitalRead(BUTTON) == LOW); 
  
  // Read the range sensor value
  rangeSensor = analogRead(SHARP);
  // Map the values into millivolts (assuming 3300 mV reference voltage)
  rangeSensorMv = map(rangeSensor,0,1023,0,3300);

  // Print the values
  Serial.print("ADC output:\t");
  Serial.print(rangeSensor);
  Serial.print("\t millivolts:\t");
  Serial.println(rangeSensorMv);
      
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
