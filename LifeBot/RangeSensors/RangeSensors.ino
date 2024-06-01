 int SHARP1 = A1;
  int SHARP2 = A2;
  int SHARP3 = A3;
  
 int rangeSensor1 = 0;
  int rangeSensor2 = 0;
  int rangeSensor3 = 0;
 int rangeSensor1MV = 0;
  int rangeSensor2MV = 0;
  int rangeSensor3MV = 0;
void setup() {
  // put your setup code here, to run once:
 pinMode(SHARP1, INPUT);
  pinMode(SHARP2, INPUT);
  pinMode(SHARP3, INPUT);

  Serial.begin(9600);
  
} 
void loop() {
// put your main code here, to run repeatedly:

rangeSensor1 = analogRead(SHARP1);
rangeSensor2 = analogRead(SHARP2);
rangeSensor3 = analogRead(SHARP3);

//need to fix these equations! not woroking at all
rangeSensor1 = -11.631*pow(rangeSensor1,2) + 131.96*rangeSensor1+299.31;
rangeSensor2 = -11.631*(rangeSensor2) + 810;
rangeSensor3 = -55.964*(rangeSensor3) + 725.64;


Serial.print(rangeSensor1);
Serial.print(" cm \n distance from left");
Serial.print(rangeSensor2);
Serial.print(" cm \n distance from right:");
Serial.print(rangeSensor3);
Serial.print(" cm distance from front");
Serial.print("\n");

delay(2000);

}

