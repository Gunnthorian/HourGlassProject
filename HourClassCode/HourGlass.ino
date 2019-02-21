/*
The Houe Glass Project
Created by: Dexter Dixon
 ***************************************************************
 Two MAX72XX 8x8 LED Matrixs
 pin 8 is connected to the DataIn
 pin 10 is connected to the CLK
 pin 9 is connected to LOAD
 ***************************************************************
 */
#include "LedControl.h"
#include "HourGlass.h"
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

/*
  Initialize Matrix and Gyro
*/




void setup() 
{
/* 
  Set up the Gyro and Matrix
*/
  startGyro();
  resetLed();
}

void loop() 
{
/* 
   Switch statment that ets the connditions for the orientation of the device
*/

  switch (gyro.getOrientation()) 
  {
    case 0: 
      Serial.println("Portrait Up Front");
      break;
    case 1: 
      Serial.println("Portrait Up Back");
      break;    
    case 2: 
      Serial.println("Portrait Down Front");
      break;
    case 3: 
      Serial.println("Portrait Down Back");
      break;
    case 4: 
      Serial.println("Landscape Right Front");
      break;
    case 5: 
      Serial.println("Landscape Right Back");
      break;
    case 6: 
      Serial.println("Landscape Left Front");
      break;
    case 7: 
      Serial.println("Landscape Left Back");
      break;

 }
 delay(500);
}


