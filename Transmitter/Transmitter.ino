#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // create an RF24 object, CE, CSN 
const byte address[6] = "00001"; // address

void setup() 
{
   radio.begin();
   radio.openWritingPipe(address);  // set the address
   radio.setPALevel(RF24_PA_MIN);
   radio.stopListening();  // set module as transmitter
}

void loop() 
{
   const char text[] = "Hello World";  // message
   radio.write(&text, sizeof(text));  // send message
   delay(100);
}
