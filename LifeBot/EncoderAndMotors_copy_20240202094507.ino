


/**
 * @file read-wheel-encoder.ino
 * @author Joshua Marshall (joshua.marshall@queensu.ca)
 * @brief Arduino program to read from a digital quadrature encoder.
 * @version 2.0
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */

// Encoder Variables
const byte SIGNALEFT_A = 13;
const byte SIGNALEFT_B = 12;
const byte SIGNALRIGHT_A = 11;
const byte SIGNALRIGHT_B = 10;
// Counter to keep track of encoder ticks [integer]
volatile long encoder_ticksLEFT = 0;
// Counter to keep track of delta ticks [integer]
volatile long delta_ticksLEFT = 0;
// Counter to keep track of the last number of ticks [integer]
long encoder_ticks_lastLEFT = 0;
// Counter to keep track of encoder ticks [integer]
volatile long encoder_ticksRIGHT = 0;
// Counter to keep track of delta ticks [integer]
volatile long delta_ticksRIGHT = 0;
// Counter to keep track of the last number of ticks [integer]
long encoder_ticks_lastRIGHT = 0;
// This function is called when SIGNALEFT_A goes HIGH
//Encoder Variables


int EA = 3; // Wheel PWM pin (must be a PWM pin)
int I1 = 4; // Wheel direction digital pin 1
int I2 = 2; // Wheel direction digital pin 2
int EB = 5; // Wheel PWM pin (must be a PWM pin)
int I3 = 7; // Wheel direction digital pin 1
int I4 = 6; // Wheel direction digital pin 
const int u = 255; //Wheel spd

int leftSpeed = 0;
int rightSpeed = 0;
int baseSpeedLeft = 225;
int baseSpeedRight = 225;
double accError;


//This function changes whenever the left encoder changes
void decodeEncoderTicksLeft()
{
    if (digitalRead(SIGNALEFT_B) == LOW) {
        // SIGNALEFT_B is LOW, decrement left encoder ticks
        encoder_ticksLEFT--;
    } else {
        // SIGNALEFT_B is HIGH, increment left encoder ticks
        encoder_ticksLEFT++;
    }
}

//This function changes whenever the right encoder changes
void decodeEncoderTicksRight()
{
    if (digitalRead(SIGNALRIGHT_B) == LOW) {
        // SIGNALRIGHT_B is LOW, decrement right encoder ticks
        encoder_ticksRIGHT--;
    } else {
        // SIGNALRIGHT_B is HIGH, increment right encoder ticks
        encoder_ticksRIGHT++;
    }
}

int LeftWheelSpeed() {

    int deltaLeft = encoder_ticksLEFT - encoder_ticks_lastLEFT;
    encoder_ticks_lastLEFT = encoder_ticksLEFT; // Update the last tick count for the next calculation

    return deltaLeft; // Returns positive for forward, negative for backward
}

int RightWheelSpeed() {



    int deltaRight = -1*(encoder_ticksRIGHT - encoder_ticks_lastRIGHT);
    encoder_ticks_lastRIGHT = encoder_ticksRIGHT; // Update the last tick count for the next calculation

    return deltaRight; // Returns positive for forward, negative for backward
}


void leftwheeldrive(int spd, int drc){
  if (drc < 0)
    {
      digitalWrite(I3, HIGH);  
      digitalWrite(I4, LOW);
    }
  else
    {
      digitalWrite(I3, LOW);  
      digitalWrite(I4, HIGH);
    }
  analogWrite(EB, spd);
}

void rightwheeldrive(int spd, int drc) // speed btw 0 -255
{
  if (drc > 0)
    {
      digitalWrite(I1, HIGH);  
      digitalWrite(I2, LOW);
    }
  else
    {
      digitalWrite(I1, LOW);  
      digitalWrite(I2, HIGH);
    }
  analogWrite(EA, spd);
}

//Encoder stop
void Stop() {
    // Apply initial braking power
    leftwheeldrive(200, -1);
    rightwheeldrive(200, -1);

    // Continuously monitor wheel speed and adjust braking as necessary
    while (true) {
        int leftSpeed = LeftWheelSpeed();
        int rightSpeed = RightWheelSpeed();

        // Check if both wheels have approximately stopped
        if (abs(leftSpeed) <= 1 && abs(rightSpeed) <= 1) {
            break; // Exit the loop if both wheels are nearly stopped
        }
    }

    // Fully stop the motors
    leftwheeldrive(0, 0);
    rightwheeldrive(0, 0);

encoder_ticksLEFT = 0;
delta_ticksLEFT = 0;
encoder_ticks_lastLEFT = 0;
encoder_ticksRIGHT = 0;
delta_ticksRIGHT = 0;
encoder_ticks_lastRIGHT = 0;
}


//Encoder Forward
//Encoder Forward
void Forward() {

  leftSpeed = LeftWheelSpeed();
  rightSpeed = RightWheelSpeed();

/*
  Serial.println(leftSpeed);
  Serial.print("   ");
  Serial.print(rightSpeed);
  Serial.println();
  */

  
    float Kp = 0.5;     // Proportional gain for the controller
    double Kpi = 0.03;
    
    int speedDifference = leftSpeed - rightSpeed;


    Serial.print(leftSpeed);
    Serial.print(",");
    Serial.print(rightSpeed);
    Serial.print(",");
    Serial.print(speedDifference);
    Serial.println();
    

    accError = constrain(accError + speedDifference, -5, 5);
    

    double accErrorAdjustLeft = -Kpi*accError;
    double accErrorAdjustRight = Kpi*accError;


    // Calculate the adjustment factor for each motor
    double adjustLeft = -Kp * speedDifference;
    double adjustRight = Kp * speedDifference;
    

    // Calculate the new speeds ensuring they remain within 0-255 range
    int newLeftSpeed = constrain(baseSpeedLeft + adjustLeft + accErrorAdjustLeft, 150, 255);
    int newRightSpeed = constrain(baseSpeedRight + adjustRight + accErrorAdjustRight, 150, 255);

 

    // Apply the new speeds to the motors, in forward direction
    leftwheeldrive(newLeftSpeed, 1);  // Left wheel forward
    rightwheeldrive(newRightSpeed, 1); // Right wheel forward
    

    baseSpeedLeft = newLeftSpeed;
    baseSpeedRight = newRightSpeed;
}


//Encoder Reverse
void Reverse() {
    int baseSpeed = 200; // Base speed for the motors
    float Kp = 0.5;     // Proportional gain for the controller
    int leftSpeed = LeftWheelSpeed();
    int rightSpeed = RightWheelSpeed();
    int speedDifference = leftSpeed - rightSpeed;

    // Calculate the adjustment factor for each motor
    int adjustLeft = -Kp * speedDifference;
    int adjustRight = Kp * speedDifference;

    // Calculate the new speeds ensuring they remain within 0-255 range
    int newLeftSpeed = constrain(baseSpeed + adjustLeft, 0, 255);
    int newRightSpeed = constrain(baseSpeed + adjustRight, 0, 255);

    // Apply the new speeds to the motors, but in reverse
    //leftwheeldrive(newLeftSpeed, -1);
    leftwheeldrive(200, -1);  // Left wheel backward
    rightwheeldrive(newRightSpeed, -1);
}

//Turn left Encoder
void TurnLeft(int turnTicks) {
    long initialLeftTicks = encoder_ticksLEFT;
    long initialRightTicks = encoder_ticksRIGHT;

    leftwheeldrive(200, -1);  // Left wheel backward
    rightwheeldrive(200, 1);  // Right wheel forward

    while(abs(encoder_ticksLEFT - initialLeftTicks) < turnTicks && 
          abs(encoder_ticksRIGHT - initialRightTicks) < turnTicks) {
        // Wait for the wheels to reach the desired encoder ticks
    }

    Stop(); // Stop the wheels after turning
}

//Turn Right Encoder
void TurnRight(int turnTicks) {
    long initialLeftTicks = encoder_ticksLEFT;
    long initialRightTicks = encoder_ticksRIGHT;

    leftwheeldrive(200, 1);  // Left wheel forward
    rightwheeldrive(200, -1); // Right wheel backward

    while(abs(encoder_ticksLEFT - initialLeftTicks) < turnTicks && 
          abs(encoder_ticksRIGHT - initialRightTicks) < turnTicks) {
        // Wait for the wheels to reach the desired encoder ticks
    }

    Stop(); // Stop the wheels after turning
}


void setup()
{
    // Open the serial port at 9600 bps
    Serial.begin(9600);

//ENCODER
    // Set the pin modes for the Left wheel encoders
    pinMode(SIGNALEFT_A, INPUT);
    pinMode(SIGNALEFT_B, INPUT);
     // Set the pin modes for the right wheel encoders
    pinMode(SIGNALRIGHT_A, INPUT);
    pinMode(SIGNALRIGHT_B, INPUT);
    // Every time SIGNAL_A goes HIGH, this is a pulse
    attachInterrupt(digitalPinToInterrupt(SIGNALEFT_A), decodeEncoderTicksLeft, RISING);
    // Every time SIGNAL_A goes HIGH, this is a pulse
    attachInterrupt(digitalPinToInterrupt(SIGNALRIGHT_A), decodeEncoderTicksRight, RISING);
//ENCODER

//MOTOR CONFIGURE
  pinMode(EA, OUTPUT);
  pinMode(I1, OUTPUT); 
  pinMode(I2, OUTPUT);
  pinMode(EB, OUTPUT);
  pinMode(I3, OUTPUT); 
  pinMode(I4, OUTPUT);
  
//MOTOR CONFIGURE


 
}



void loop() {

  

  Forward();


}


/*
void loop() {
    if (Serial.available() > 0) {
        char command = Serial.read(); // Read the incoming command

        switch (command) {
            case 'F': // Forward
                Forward();
                delay 
                break;
            case 'B': // Backward
                Reverse();
                break;
            case 'L': // Turn Left
                TurnLeft(10000); // Adjust 100 to your specific turning requirement
                break;
            case 'R': // Turn Right
                TurnRight(10000); // Adjust 100 to your specific turning requirement
                break;
            case 'S': // Stop
                Stop();
                break;
            default:
                // Optional: Handle unknown commands
                break;
        }
    }

}

*/






