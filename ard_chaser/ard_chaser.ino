// IF you are unable to upload the file to Arduino then uncomment the "Adafruit_SSD1306.h"
// and "SimpleDHT.h" 
//#include <Adafruit_SSD1306.h>
//#include <SimpleDHT.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <Servo.h> 
#define PIN 7
#define NUMPIXELS 23

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 100
int servoPin = 13; 
Servo Servo1;

int flag;
String data;

void setup()
{
  Serial.begin(9600);
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
  Servo1.attach(servoPin);
}

void loop()
{
  while( Serial.available() > 0)
  {
    data = Serial.readString();
    Serial.println(data);

    if (data == "ON")
    {
      flag = 1;
    }
    else if(data == "OFF")
    {
      flag = 0;
    }
  }
  if(flag == 1)
    {
      for(int i=0; i<NUMPIXELS; i++) {

        pixels.setPixelColor(i, pixels.Color(255, 50, 0));
        pixels.show();
        delay(DELAYVAL);
      }
      // Make servo go to 0 degrees 
      Servo1.write(0);
    }
     else if (flag == 0)
    {
      pixels.clear();
      delay(500); 
    }
}
