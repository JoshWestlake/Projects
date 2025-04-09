// MREN 303 Pico W Wifi Gamepad Read
// Written For MREN 303

#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>

#ifndef STASSID
#define STASSID "JoshWestlake"
#define STAPSK "12345678"
#endif

unsigned int localPort = 8888;  // local port to listen on

WiFiUDP Udp;
byte mac[6];                     // the MAC address of your Wifi shield

void setup() { //This handles network function and runs on core 1
  Serial.begin(115200);
  WiFi.begin(STASSID, STAPSK);

  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[0],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.println(mac[5],HEX);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);

}
void setup1(){ //This handles all inputs and outputs and runs on core 2
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,1);

}

void loop() { //This loop executes on Core 1 of the Pico, handles networking and recieves commands
  // if there's data available, read a packet

}

void loop1(){ //This Runs on Core 2 and performs all inputs and outputs
}
