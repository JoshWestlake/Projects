/**
 * @file motor-angular-rate.ino
 * @author Joshua Marshall (joshua.marshall@queensu.ca)
 * @brief Arduino program to estimate motor speed from encoder.
 * @version 2.1
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2021-2022
 *
 */

int EA = 2; // Wheel PWM pin (must be a PWM pin)
int I1 = 4; // Wheel direction digital pin 1
int I2 = 3; // Wheel direction digital pin 2
int EB = 5; // Wheel PWM pin (must be a PWM pin)
int I3 = 7; // Wheel direction digital pin 1
int I4 = 6; // Wheel direction digital pin 

// Motor PWM command variable [0-255]
byte uL = 220;
byte uR = 220;

// Left wheel encoder digital pins
const byte L_SIGNAL_A = 13;
const byte L_SIGNAL_B = 12;
const byte R_SIGNAL_A = 11;
const byte R_SIGNAL_B = 10;
// Encoder ticks per (motor) revolution (TPR)
const int TPR = 3000;

// Wheel radius [m]
const double RHO = 0.0625;
const double LL = 0.2775;

// Counter to keep track of encoder ticks [integer]
volatile long L_encoder_ticks = 0;
volatile long R_encoder_ticks = 0;

// Variable to store estimated angular rate of left wheel [rad/s]
double omega_L = 0.0;
double omega_R = 0.0;
double velocity_L = 0.0;
double velocity_R = 0.0;

double avg_omega = 0.0;
double avg_v = 0.0;
// Sampling interval for measurements in milliseconds
const int T = 1000;

// Counters for milliseconds during interval
long t_now = 0;
long t_last = 0;

// This function is called when SIGNAL_A goes HIGH
void L_decodeEncoderTicks()
{
    if (digitalRead(L_SIGNAL_B) == LOW)
    {
        // SIGNAL_A leads SIGNAL_B, so count one way
        L_encoder_ticks--;
    }
    else
    {
        // SIGNAL_B leads SIGNAL_A, so count the other way
        L_encoder_ticks++;
    }
}
void R_decodeEncoderTicks()
{
    if (digitalRead(R_SIGNAL_A) == LOW)
    {
        // SIGNAL_A leads SIGNAL_B, so count one way
        R_encoder_ticks--;
    }
    else
    {
        // SIGNAL_B leads SIGNAL_A, so count the other way
        R_encoder_ticks++;
    }
}

void setup()
{
    // Open the serial port at 9600 bps
    Serial.begin(9600);

    // Set the pin modes for the motor driver
    pinMode(EA, OUTPUT);
    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
    pinMode(EB, OUTPUT);
    pinMode(I3, OUTPUT); 
    pinMode(I4, OUTPUT);

    // Set the pin modes for the encoders
    pinMode(L_SIGNAL_A, INPUT);
    pinMode(L_SIGNAL_B, INPUT);
    pinMode(R_SIGNAL_A, INPUT);
    pinMode(R_SIGNAL_B, INPUT);

    // Every time the pin goes high, this is a pulse
    attachInterrupt(digitalPinToInterrupt(L_SIGNAL_A), L_decodeEncoderTicks, RISING);
    attachInterrupt(digitalPinToInterrupt(R_SIGNAL_A), R_decodeEncoderTicks, RISING);

    // Print a message
    Serial.print("Program initialized.");
    Serial.print("\n");
}

// Compute vehicle speed [m/s]
double compute_vehicle_speed(double v_L, double v_R)
{
double v;
v = 0.5 * (v_L + v_R);
return v;
}
// Compute vehicle turning rate [rad/s]
double compute_vehicle_rate(double v_L, double v_R)
{
double omega;
omega = 1.0 / LL * (v_R - v_L);
return omega;
}



void loop()
{
    // Get the elapsed time [ms]
    t_now = millis();

    if (t_now - t_last >= T)
    {
        // Estimate the rotational speed [rad/s]
        omega_L = 2.0 * PI * ((double)L_encoder_ticks / (double)TPR) * 1000.0 / (double)(t_now - t_last);
        omega_R = 2.0 * PI * ((double)R_encoder_ticks / (double)TPR) * 1000.0 / (double)(t_now - t_last);
        
        
        

        velocity_L = RHO * omega_L;
        velocity_R = RHO * omega_R;

        avg_v = compute_vehicle_speed(velocity_L, velocity_R);
      
        avg_omega = compute_vehicle_rate(omega_L, omega_R);
        

        // Print some stuff to the serial monitor
        Serial.print("Left Encoder ticks: ");
        Serial.print(L_encoder_ticks);
        Serial.print("Right Encoder ticks: ");
        Serial.print(R_encoder_ticks);
        Serial.print("\t");
        Serial.print("Estimated left wheel speed: ");
        Serial.print(omega_L);
        Serial.print(" rad/s");
        Serial.print("Estimated right wheel speed: ");
        Serial.print(omega_R);
        Serial.print(" rad/s");
        Serial.print("\n");

        // Record the current time [ms]
        t_last = t_now;

        // Reset the encoder ticks counter
        L_encoder_ticks = 0;
        R_encoder_ticks = 0;
    }

    // Set the wheel motor PWM command [0-255]
    if (velocity_L < velocity_R){
      uR -= 1;
    }
    else{
      uR += 1;
    }
        Serial.print("uR = ");
        Serial.print(uR);
        Serial.print("  average ratio =");
        Serial.print(uR/velocity_R);

    // Select a direction
    digitalWrite(I1, LOW);
    digitalWrite(I2, HIGH);
    digitalWrite(I3, HIGH);
    digitalWrite(I4, LOW); 
}

void runMotors(byte uL, byte uR)
    // PWM command to the motor driver
    {
    analogWrite(EA, uL);
    analogWrite(EB, uR);
   
    }