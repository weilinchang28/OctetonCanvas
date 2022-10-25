#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001"; // address 

void setup() 
{
  // while(!Serial); 
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address); // set the address
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();  // set module as receiver
}

void loop() 
{
   // Read the data if available in buffer
  if(radio.available()) 
  {
    char text[32] = {0}; 
    radio.read(&text, sizeof(text)); 
//
//    char text1[32] = {0};
//    radio.read(&text1, sizeof(text1));
//
//    char text2[32] = {0};
//    radio.read(&text2, sizeof(text2));
//    
//    char text3[32] = {0};
//    radio.read(&text3, sizeof(text3));
//
//    Serial.print(text); 
//    Serial.print(" ");
//    Serial.print(text1); 
//    Serial.print(" ");
//    Serial.print(text2); 
//    Serial.print(" ");
//    Serial.println(text3); 
    
    
    Serial.println(text);
  } 
}
