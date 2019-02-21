/*
The Houe Glass Project
Created by: Dexter Dixon
 */

#include "LedControl.h"
#include "HourGlass.h"
#include "RTClib.h"
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#define HAUT 0
#define BAS 1
#define ON 1
#define OFF 0
#define SHAKE 12 // Vibration sensor pin
#define MODE 2
// 1 = normal - random length loop
// 2 = 1 minute per loop.
int wait = 20; // In milliseconds
int ln = 5; // Filling level of the globe
int pinCS = 10;
// One second between each marble drop :
int htimeout = 1000;
RTC_Millis rtc;
// Timer for benchmarking
unsigned long startms = millis();
// Variable for the timing :
unsigned long timer = 0;
//  Timeout for a next-grain drop
int next_grain = 0;
//Array of pixels (2 matrices of 8x8)
int pixels[8][16];

int devices = 2;
LedControl led=LedControl(8,10,9,devices);
Adafruit_MMA8451 gyro = Adafruit_MMA8451();
/************ The Hour Glass functions ***********************/

/*
  Clears matrix display and 
 */
void resetLed() 
{
    for(int i = 0; i<devices; i++)
  {
    led.shutdown(i,false);
    led.setIntensity(i,8);
    led.clearDisplay(i); 
  }
}

/*
  Sets up the gyro
 */
void startGyro()
{
  Serial.begin(9600);
  gyro.begin();
  gyro.setRange(MMA8451_RANGE_2_G);
}



/*
  Emptying led array
 */
void cleanup_pixels() 
{
  for (int i = 0; i < 8 ; i++) 
  {
    for (int j = 0; j < 16; j++) 
    {
      pixels[i][j] = 0;
    }
  }
}

// Routine to get the led's state :
int get_pixel(int x, int y, int globe) 
{
  if ((x > 7) || (y > 7)) 
  {
    return (255); // Outcote scope... sorry !
  }

  if (globe == BAS) 
  { // Adding ofset for the lower matrix :
    y += 8;
  }
  return ( pixels[x][y] );
}

// Setting led to selected state :
// X,Y,HAUT/BAS,ON/OFF
void set_pixel(int x, int y, int globe, const int allume)
{
  if ((x > 7) || (y > 7)) 
  {
    return;
  }
  if ((x < 0) || (y < 0)) 
  {
    return;
  }
  if (globe == BAS) 
  {
    y += 8; // Offset for the lower matrix
  }
  pixels[x][y] = allume;
}

// Routine to print the led array on the matrix
void draw_hourglass() 
{
  for (int i = 0; i < 8; i++) 
  {
    for (int j = 0; j < 16; j++) 
    {
      matrix.drawPixel(i, j, pixels[i][j]);
    }
  }
  matrix.write();
}
/*
  Filling the Upper glass with some sand 
 */

void fill_hourglass(int niv = 5, int globe = HAUT) 
{
  cleanup_pixels();
  byte minu = 0;
  niv = 0;

#if MODE==1

  for (int y = 0; y < 8; y++) 
  {
    for (int x = 0; x < 8; x++) 
    {
      if ((x + y) > niv) 
      {
        set_pixel(x, y, globe, ON);
        draw_hourglass();
        minu++;
        delay(10);
      }
    }
  }

# else
  while (minu <= 48) 
  {
    int x = random(8);
    int y = random(8);
    
    if (get_pixel(x, y, HAUT) == OFF) 
    {
      set_pixel(x, y, HAUT, ON);
      minu++;
      draw_hourglass();
      delay(10);
    }
  }



# endif
  Serial.println("====");
  Serial.println((millis() - timer) / 1000);
  timer = millis();
}



