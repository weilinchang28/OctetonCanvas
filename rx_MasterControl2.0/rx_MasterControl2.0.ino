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

bool updatePrint = false;

int previousValues[4] = {0,0,0,0};


void setup() 
{
  // while(!Serial); 
  SPI.begin();
  Serial.begin(115200);
  radio.begin();
  network.begin(90, this_node); // (Channel, Node Address)
  radio.setDataRate(RF24_2MBPS);

  pinMode(led, OUTPUT);
}

void loop() 
{

  network.update();
  //===== Receiving =====//
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;

    int text;
    
    int output1;
    int output2; 
    int output3;
    int output4;
  
    
    network.read(header, &text, sizeof(text));
    if(header.from_node == 1)
    {
      if(text != previousValues[0])
      {
        output1 = text;
        previousValues[0] = text;
        updatePrint =true;
      }
      // output1 = text;
    }
    if(header.from_node == 2)
    {
      if(text != previousValues[1])
      {
        output2 = text;
        previousValues[1] = text;
        updatePrint =true;
      }
      
      //output2 = text;
    }
    if(header.from_node == 3)
    {
      if(text != previousValues[2])
      {
        output3 = text;
        previousValues[2] = text;
        updatePrint =true;
      }
    }
    if(header.from_node == 4)
    {
      if(text != previousValues[3])
      {
        output4 = text;
        previousValues[3] = text;
        updatePrint =true;
      }
      // output4 = text;
    }
    if (updatePrint)
    {

    Serial.print (output1);
    Serial.print (" ");
    Serial.print (output2);
    Serial.print (" ");
    Serial.print (output3);
    Serial.print (" ");
    Serial.println (output4);
    delay(100);
    updatePrint = false;
    }
    
    // analogWrite(led, text);    // PWM output to LED 01 (dimming)
  }

}
