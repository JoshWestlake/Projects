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

// Encoder digital pins
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

// This function is called when SIGNALRIGHT_A goes HIGH
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

void setup()
{
    // Open the serial port at 9600 bps
    Serial.begin(9600);

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

    // Print a message
    Serial.print("Program initialized.");
    Serial.print("\n");
}

void loop()
{
    // Do this if the encoder has moved
    if (encoder_ticksLEFT != encoder_ticks_lastLEFT || encoder_ticksRIGHT != encoder_ticks_lastRIGHT){

        // Print some stuff to the serial monitor
        Serial.print("Encoder ticks left: ");
        Serial.print(encoder_ticksLEFT);

         // Print some stuff to the serial monitor
        Serial.print(" | Encoder ticks right: ");
        Serial.print(encoder_ticksRIGHT);


        if(encoder_ticksLEFT != encoder_ticks_lastLEFT){

        delta_ticksLEFT = encoder_ticksLEFT - encoder_ticks_lastLEFT;

        if (delta_ticksLEFT < 0){
          delta_ticksLEFT = - delta_ticksLEFT;
        }

        Serial.print("  | delta ticks left : ");
        Serial.print(delta_ticksLEFT);
        Serial.print("  | delta ticks right : ");
        Serial.print(delta_ticksRIGHT);
        

         // Record the current number of encoder ticks
        encoder_ticks_lastLEFT = encoder_ticksLEFT;
    }

     if(encoder_ticksRIGHT != encoder_ticks_lastRIGHT){

        delta_ticksRIGHT = encoder_ticksRIGHT - encoder_ticks_lastRIGHT;

        if (delta_ticksRIGHT < 0){
          delta_ticksRIGHT = - delta_ticksRIGHT;
        }

        Serial.print("  | delta ticks right : ");
        Serial.print(delta_ticksRIGHT);
        

         // Record the current number of encoder ticks
        encoder_ticks_lastRIGHT = encoder_ticksRIGHT;
    }

    Serial.print("\n");
    // Short delay [ms]
    delay(100);
}

}