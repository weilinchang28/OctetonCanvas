#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Network.h>

#define led 3

RF24 radio(9, 10); // CE, CSN
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t colorScanner01 = 01;      // Address of the other node in Octal format
const uint16_t colorScanner02 = 02;
const uint16_t colorScanner03 = 03;
const uint16_t colorScanner04 = 04;

// const byte address[6] = "00001"; // address 

void setup() 
{
  // while(!Serial); 
  SPI.begin();
  Serial.begin(115200);
  radio.begin();
  network.begin(90, this_node); // (Channel, Node Address)
  radio.setDataRate(RF24_2MBPS);

  pinMode(led, OUTPUT);
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
    //unsigned long incomingData;

    int text;
    
    int output1;
    int output2; 
    int output3;
    int output4;
    
    network.read(header, &text, sizeof(text));
    if(header.from_node == 1)
    {
      output1 = text;
    }
    if(header.from_node == 2)
    {
      output2 = text;
    }
    if(header.from_node == 3)
    {
      output3 = text;
    }
    if(header.from_node == 4)
    {
      output4 = text;
    }

    Serial.print (output1);
    Serial.print (" ");
    Serial.print (output2);
    Serial.print (" ");
    Serial.print (output3);
    Serial.print (" ");
    Serial.println (output4);
    
    // network.read(header, & text1, sizeof(text1));
    // network.read(header, & text2, sizeof(text2));
    // network.read(header, &incomingData, strlen(incomingData)); // Read the incoming data
    // analogWrite(led, incomingData);    // PWM output to LED 01 (dimming)
  }

  


  
   // Read the data if available in buffer
//  if(radio.available()) 
//  {
//    char text[32] = {0}; 
//    radio.read(&text, sizeof(text)); 
//
//    
//    
//    Serial.println(text);
//
//  } 
}
