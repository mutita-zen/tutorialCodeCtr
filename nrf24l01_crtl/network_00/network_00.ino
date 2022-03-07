/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
 == Example 01 - Servo Control / Node 00 - Potentiometer ==
  by Dejan, www.HowToMechatronics.com
  Libraries:
  nRF24/RF24, https://github.com/nRF24/RF24
  nRF24/RF24Network, https://github.com/nRF24/RF24Network
*/
#include <RF24.h>
#include <RF24Network.h>
#include "printf.h"
#include <SPI.h>

RF24 radio(7, 8);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 01;      

void setup() {
  SPI.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  
  if (!radio.begin()) {
     Serial.println(F("radio hardware is not responding!!"));
     //while(1){}
  } else {
     Serial.println(F("radio hardware is responsed"));
  }
  network.begin(90, this_node);  //(channel, node address)
     // For debugging info
  Serial.begin(115200);
  delay(5000);
  printf_begin();             // needed only once for printing details
  radio.printDetails();       // (smaller) function that prints raw register values
  radio.printPrettyDetails(); // (larger) function that prints human readable data
  delay(5000);
}

/* function  general */
void blinkPort(int port){
  digitalWrite(port, HIGH);
  delay(500);
  digitalWrite(port, LOW);
  delay(500);
}

void loop() {
  blinkPort(LED_BUILTIN);

  network.update();
  unsigned long potValue = analogRead(A0);  // Read the potentiometer value
  unsigned long angleValue = map(random(100), 0, 1023, 0, 180); // Convert the value to 0-180
  RF24NetworkHeader header(node01);     // (Address where the data is going)
  bool ok = network.write(header, &angleValue, sizeof(angleValue)); // Send the data
  //Serial.println(angleValue) ; 
}
