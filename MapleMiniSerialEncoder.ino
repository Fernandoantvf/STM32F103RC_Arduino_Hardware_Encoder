/********************************************************************************************
File: MapleMiniSerialEncoder.cpp

Description:
  
  Activates a hardware quadrature encoder interface on the Maple Mini with the STM32F103RCBT6 CORTEX-M3 MCU
  Channel A and Channel B are read on ports 27 and 26 (PA8 and PA9 respectively) and are counted on TIM1.
  Uses no additional librarys witch is great for portability and use of many open source projects.
  Prints Channels A,B an counter every 100ms  
  
Sources used:

  Maple mini documentation:
    http://docs.leaflabs.com/static.leaflabs.com/pub/leaflabs/maple-docs/0.0.12/hardware/maple-mini.html#maple-mini-stdocs
  STM32F103RCBT6 MCU documentation
    Datasheet:
      http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00161566.pdf
    Reference manual:
      http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/REFERENCE_MANUAL/CD00171190.pdf

Notes: get the memory map from the datasheet and the offsets for each paramater word in the reference manual 

Author: Fernando Figueiredo
License: GNU GPL
Creation: 2017-09-03
Last modification: 2017-09-03
********************************************************************************************/

#include "src/EncoderLibrary/QuadEnc.h"

QuadEnc quadEnc;
void setup()
{
  Serial.begin();
  //Initiate counter and define if count inversion is required
  //Pins 26 and 27 get configured as inputs with pull ups
  quadEnc.init_encoder(true);
  //Load a specific value to counter (may be required for a homing or reset function
  quadEnc.load_counter(100);
  
}

void loop() {
  //Read out the position and print it to the USB serial port
  Serial.println("TIM1_CNT : " + String(quadEnc.pos()));
  Serial.println("D27,D26 : " + String(digitalRead(27)) + "," + String(digitalRead(26)));  
  delay(100);      
}



