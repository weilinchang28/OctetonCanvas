#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // create an RF24 object, CE, CSN 
const byte address[6] = "00001"; // address

#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(5, 6); // RX, TX
//HUSKYLENS green line >> Pin 5; blue line >> Pin 6

void printResult(HUSKYLENSResult result);

void setup()
{
  radio.begin();
  radio.openWritingPipe(address);  // set the address
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();  // set module as transmitter
  
  Serial.begin(9600); // Suppose to be 115200

  mySerial.begin(9600);
  while (!huskylens.begin(mySerial))
  {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  
  while (!huskylens.customText("EnsembleTest", 175, 20)) // ProjectName + CodeVersion
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
        // ColorNames - inSystem
        if (result.ID == 1)
        {
          Serial.println ("74"); // D 587.33 | Blue
          const char text1[] = "74";
          radio.write(&text1, sizeof(text1));
        }
        if (result.ID == 2)
        {
          Serial.println ("79"); // G 783.99 | Yellow
          const char text1[] = "79";
          radio.write(&text1, sizeof(text1));
        }
        if (result.ID == 3)
        {
          Serial.println ("72"); // C 523.25 | Red
          const char text1[] = "72";
          radio.write(&text1, sizeof(text1));
        }
        if (result.ID == 4)
        {
          Serial.println ("81"); // A 880 | Orange
          const char text1[] = "81";
          radio.write(&text1, sizeof(text1));
        }
        if (result.ID == 5)
        {
          Serial.println ("76"); // E 659.25 | Green
          const char text1[] = "76";
          radio.write(&text1, sizeof(text1));
        }      
      }
      
    }
    
    else
    {
        Serial.println("Object unknown!");
    }

    
   // delay(100);

}
