#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Network.h>

RF24 radio(9, 10); // CE, CSN
RF24Network network(radio);      // Include the radio in the network
const uint16_t masterControl = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t colorScanner01 = 01;      // Address of the other node in Octal format
const uint16_t colorScanner02 = 02;
const uint16_t colorScanner03 = 03;
const uint16_t colorScanner04 = 04;

// const byte address[6] = "00001"; // address 

void setup() 
{
  // while(!Serial); 
  Serial.begin(9600);
  radio.begin();
  network.begin(90, masterControl); // (Channel, Node Address)
  radio.setDataRate(RF24_2MBPS);
//  radio.openReadingPipe(0, address); // set the address
//  radio.setPALevel(RF24_PA_MIN);
//  radio.startListening();  // set module as receiver
}

void loop() 
{

  network.update();
  //===== Receiving =====//
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    unsigned long incomingData;
    network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
    analogWrite(led, incomingData);    // PWM output to LED 01 (dimming)
  }


  
   // Read the data if available in buffer
  if(radio.available()) 
  {
    char text[32] = {0}; 
    radio.read(&text, sizeof(text)); 

    
    
    Serial.println(text);

  } 
}
