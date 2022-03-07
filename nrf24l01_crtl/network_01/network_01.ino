/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
  == Example 01 - Servo Control / Node 01 - Servo motor ==
*/
#include <RF24.h>
#include <RF24Network.h>
#include "printf.h"
#include <SPI.h>
#include <Servo.h>

RF24 radio(7, 8);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)


#define relayA 22
#define relayB 24
#define relayC 26
#define relayD 28
#define relayE 30
#define relayF 32
#define relayG 34
#define relayH 36

void setup() {
  SPI.begin();
  if (!radio.begin()) {
     Serial.println(F("radio hardware is not responding!!"));
     //while(1){}
  } else {
     Serial.println(F("radio hardware is responsed"));
  }
  network.begin(90, this_node); //(channel, node address)
  initRelay();   // (servo pin)
   // For debugging info
  Serial.begin(115200);
  printf_begin();             // needed only once for printing details
  radio.printDetails();       // (smaller) function that prints raw register values
  radio.printPrettyDetails(); // (larger) function that prints human readable data
  
}


void initRelay(){
  pinMode(relayA, OUTPUT);
  pinMode(relayB, OUTPUT);
  pinMode(relayC, OUTPUT);
  pinMode(relayD, OUTPUT);
  pinMode(relayE, OUTPUT);
  pinMode(relayF, OUTPUT);
  pinMode(relayG, OUTPUT);
  pinMode(relayH, OUTPUT);

//
  /* LOW */
  digitalWrite(relayA, LOW);
  delay(100);
  digitalWrite(relayB, LOW);
  delay(100);
  digitalWrite(relayC, LOW);
  delay(100);
  digitalWrite(relayD, LOW);
  delay(100);
  digitalWrite(relayE, LOW);
  delay(100);
  digitalWrite(relayF, LOW);
  delay(100);
  digitalWrite(relayG, LOW);
  delay(100);
  digitalWrite(relayH, LOW);
  delay(100);
  /* HIGHT */
  digitalWrite(relayA, HIGH);
  delay(100);
  digitalWrite(relayB, HIGH);
  delay(100);
  digitalWrite(relayC, HIGH);
  delay(100);
  digitalWrite(relayD, HIGH);
  delay(100);
  digitalWrite(relayE, HIGH);
  delay(100);
  digitalWrite(relayF, HIGH);
  delay(100);
  digitalWrite(relayG, HIGH);
  delay(100);
  digitalWrite(relayH, HIGH);
  delay(100);
}
void loop() {
 network.update();
  //===== Receiving =====//
  //Serial.println(network.available()) ; 
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    unsigned long potValue;
    network.read(header, &potValue, sizeof(potValue)); // Read the incoming data
    // Turn on the LEDs as depending on the incoming value from the potentiometer
    Serial.println(potValue) ; 
    if (potValue > 240) {
      digitalWrite(relayA, HIGH);
    } else {
      digitalWrite(relayB, LOW);
    }
    if (potValue > 480) {
      digitalWrite(relayC, HIGH);
    } else {
      digitalWrite(relayD, LOW);
    }
    if (potValue > 720) {
      digitalWrite(relayE, HIGH);
    } else {
      digitalWrite(relayF, LOW);
    }
    if (potValue > 960) {
      digitalWrite(relayG, HIGH);
    } else {
      digitalWrite(relayH, LOW);
    }
  }
}
