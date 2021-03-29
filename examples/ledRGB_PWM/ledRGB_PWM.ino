#include <SenseoUno.h>

/*
 * ledRGB_PWM.ino
 * Shows how to use a Senseo instance in order to use the PWM outputs on an RGB led.
 * This sketch uses pins 3, 5 and 6 of the Arduino Uno for the PWM pins.
 * Pin 3 is for the green led of the RGB | Pin 5 is for the red led of the RGB |Pin 6 is for the blue led of the RGB.
 * This sketch also uses two functions of the Arduino libraries : random() and delay().
 */

// Let's create a instance based on the shield hardware configuration.
SenseoUno Senseo(EMPTY_INSTANCE);

// Let's declare 3 short / int variables.
short R; // This one is for the red led of the RGB.
short G; // This one is for the green led of the RGB.
short B; // This one is for the blue led of the RGB.

void setup()
{
  Serial.begin(9600);
  // Here we configure our RGB led as 3 analog outputs.
  Senseo.setAnalogRGB(D5, D3, D6);
}

void loop()
{
  /********** RANDOM COLOR **********/
  R = (short)random(0,255);
  G = (short)random(0,255);
  B = (short)random(0,255);
  Senseo.analogWriteRGB(R, G, B); // Here we write 8-bits values, so between 0 and 255. There are 3 values because there are 3 leds in the RGB.
  delay(1000);
  /********** FULL RED COLOR **********/
  R = 255;
  G = 0;
  B = 0;
  Senseo.analogWriteRGB(R, G, B);
  delay(1000);
  /********** RANDOM COLOR **********/
  R = (short)random(0,255);
  G = (short)random(0,255);
  B = (short)random(0,255);
  Senseo.analogWriteRGB(R, G, B);
  delay(1000);
  /********** FULL GREEN COLOR **********/
  R = 0;
  G = 255;
  B = 0;
  Senseo.analogWriteRGB(R, G, B);
  delay(1000);
  /********** RANDOM COLOR **********/
  R = (short)random(0,255);
  G = (short)random(0,255);
  B = (short)random(0,255);
  Senseo.analogWriteRGB(R, G, B);
  delay(1000);
  /********** FULL BLUE COLOR **********/
  R = 0;
  G = 0;
  B = 255;
  Senseo.analogWriteRGB(R, G, B);
  delay(1000);
}
