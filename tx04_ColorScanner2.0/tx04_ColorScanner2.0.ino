#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Network.h>

RF24 radio(9, 10); // create an RF24 object, CE, CSN 
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 04;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t master00 = 00;    // Address of the other node in Octal format

// const byte address[6] = "00001"; // address

#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(5, 6); // RX, TX
//HUSKYLENS green line >> Pin 5; blue line >> Pin 6

void printResult(HUSKYLENSResult result);

void setup()
{
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);
  radio.setDataRate(RF24_2MBPS);
//  radio.openWritingPipe(address);  // set the address
//  radio.setPALevel(RF24_PA_MIN);
//  radio.stopListening();  // set module as transmitter
  
  Serial.begin(9600); // Suppose to be 115200

  mySerial.begin(9600);
  while (!huskylens.begin(mySerial))
  {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  
  while (!huskylens.customText("Ensemble 04", 190, 20)) // ProjectName + CodeVersion
  {
    Serial.println(F("custom text failed!"));
    delay(100);
  }

  // ColorNames - onScreen
  while (!huskylens.setCustomName("Blue", 1)) // ColorName 1
  {
    Serial.println(F("ID1 customName failed!"));
    delay(100);
  }
  while (!huskylens.setCustomName("Yellow", 2)) // ColorName 2
  {
    Serial.println(F("ID2 customName failed!"));
    delay(100);
  }
  while (!huskylens.setCustomName("Red", 3)) // ColorName 3
  {
    Serial.println(F("ID3 customName failed!"));
    delay(100);
  }
  while (!huskylens.setCustomName("Orange", 4)) // ColorName 4 | TBD
  {
    Serial.println(F("ID4 customName failed!"));
    delay(100);
  }
  while (!huskylens.setCustomName("Green", 5)) // ColorName 5 | TBD
  {
    Serial.println(F("ID5 customName failed!"));
    delay(100);
  }

}


void loop() 
{
    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if(!huskylens.available()) Serial.println(F("Blank")); // WHITE Canvas
    else
    {
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            printResult(result);
        }    
    }

}

void printResult(HUSKYLENSResult result)
{
  
    if (result.command == COMMAND_RETURN_BLOCK)
    {
      if (result.xCenter > 130 && result.xCenter < 220 && result.yCenter > 75 && result.yCenter < 175) // !!TBD!! Scanning Parameter
      {
        network.update();
        
        // ColorNames - inSystem
        if (result.ID == 1)
        {
          //===== Sending =====//
          Serial.println ("74"); // D 587.33 | Blue
          int text = 74;
          RF24NetworkHeader header(master00);   // (Address where the data is going)
          bool ok = network.write(header, &text, sizeof(text)); // Send the data
        }
        if (result.ID == 2)
        {
          Serial.println ("79"); // G 783.99 | Yellow
          //===== Sending =====//
          int text = 79;
          RF24NetworkHeader header(master00);   // (Address where the data is going)
          bool ok = network.write(header, &text, sizeof(text)); // Send the data
        }
        if (result.ID == 3)
        {
          Serial.println ("72"); // C 523.25 | Red
          //===== Sending =====//
          int text = 72;
          RF24NetworkHeader header(master00);   // (Address where the data is going)
          bool ok = network.write(header, &text, sizeof(text)); // Send the data
        }
        if (result.ID == 4)
        {
          Serial.println ("81"); // A 880 | Orange
          //===== Sending =====//
          int text = 81;
          RF24NetworkHeader header(master00);   // (Address where the data is going)
          bool ok = network.write(header, &text, sizeof(text)); // Send the data
        }
        if (result.ID == 5)
        {
          Serial.println ("76"); // E 659.25 | Green
          //===== Sending =====//
          int text = 76;
          RF24NetworkHeader header(master00);   // (Address where the data is going)
          bool ok = network.write(header, &text, sizeof(text)); // Send the data
        }      
      }
      
    }
    
    else
    {
        Serial.println("Object unknown!");
    }
    
}
