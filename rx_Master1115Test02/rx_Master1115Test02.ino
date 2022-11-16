#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Network.h>

#define led 3

RF24 radio(7, 8); // CE, CSN
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t colorScanner01 = 01;      // Address of the other node in Octal format
const uint16_t colorScanner02 = 02;
const uint16_t colorScanner03 = 03;
const uint16_t colorScanner04 = 04;

// bool updatePrint = false;

// int previousValues[4] = {0,0,0,0};
int previousVal = 0;

int pedalVal1 = 1;
int pedalVal2 = 1;
int pedalVal3 = 1;
int pedalVal4 = 1;

void setup() 
{

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
    
   //// 01 //// 
    if(header.from_node == 1)
    {
      output1 = text;
    
      if (text != previousVal)
      {
        previousVal = text; 
        pedalVal1 = 0;
      }
      else
      {
        pedalVal1 = 1;
      }
    }

    //// 02 ////
    if(header.from_node == 2)
    {
      output2 = text;
    
      if (text != previousVal)
      {
        previousVal = text; 
        pedalVal2 = 0;
      }
      else
      {
        pedalVal2 = 1;
      }
      
    }


    //// 03 ////
    if(header.from_node == 3)
    {
      output3 = text;
    
      // if(text != previousValues[2])
      if (text != previousVal)
      {
        
        // previousValues[2] = text;
        // updatePrint =true;
        
        previousVal = text; 
        pedalVal3 = 0;

      }
      else
      {
        pedalVal3 = 1;
      }
      
    }


    //// 04 ////
    if(header.from_node == 4)
    {
      output4 = text;
      // if(text != previousValues[3])
      if (text != previousVal)
      { 
        // previousValues[3] = text;
        previousVal = text;
        //updatePrint =true;
        
        pedalVal4 = 0;
//        Serial.print ("Ped3 ");
//        Serial.print (pedalVal3);
//        Serial.print (" ");
      }
      else
      {
        pedalVal4 = 1;
      }
      
    }
//    if (updatePrint)
//    {
//
    
//    delay(100);
//    updatePrint = false;
//    }

    Serial.print (output1);
    Serial.print (" ");
    Serial.print (pedalVal1);
    Serial.print (" ");
    
    Serial.print (output2);
    Serial.print (" ");
    Serial.print (pedalVal2);
    Serial.print (" ");
    
    Serial.print (output3);
    Serial.print (" ");
    Serial.print (pedalVal3);
    Serial.print (" ");
    
    Serial.print (output4);
    Serial.print (" ");
    Serial.println (pedalVal4);
    
    analogWrite(led, text);    // PWM output to LED 01 (dimming)
  }

}
