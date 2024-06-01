/**

 */

int EA = 2; // Wheel PWM pin (must be a PWM pin)
int I1 = 4; // Wheel direction digital pin 1
int I2 = 3; // Wheel direction digital pin 2
int EB = 5; // Wheel PWM pin (must be a PWM pin)
int I3 = 7; // Wheel direction digital pin 1
int I4 = 6; // Wheel direction digital pin 


void leftwheeldrive(int spd, int drc) // speed btw 0 -255
{
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

void setup()
{
    // Configure digital pins for output
    pinMode(EA, OUTPUT);
    pinMode(I1, OUTPUT); 
    pinMode(I2, OUTPUT);
    pinMode(EB, OUTPUT);
    pinMode(I3, OUTPUT); 
    pinMode(I4, OUTPUT);
}




void loop()
{
    int u; // A variable for the motor PWM command [0-255]

    // Play with this code to write open loop commands to a wheel motor

    while (true){
      //stage 1
      u = 255;
      leftwheeldrive(u, 1);
      rightwheeldrive(u, -1);
      // Brief delay (perhaps not necessary)
      delay(2000);

      //stage2
      u = 255;
      leftwheeldrive(u, -1);
      rightwheeldrive(u, 1);
      // Brief delay (perhaps not necessary)
      delay(2000);

    }

}
    