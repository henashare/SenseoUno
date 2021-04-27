#include <SenseoUno.h>

/*
 * read_analog_analogTemperature.ino
 * Shows how to read an analog input 10-bits value from a analogTemperature sensor.
 * This sketch uses the shield-based configuration instance which internally declares the analog input as A0 on the Arduino Uno board.
 * This sketch also uses the chronos of the SenseoUno library. There are two examples "single_chrono.ino" and "two_chronos.ino" if necessary.
 * There are two methods to read the analogTemperature. We can also put the result in two different types : int and float.
 * In this sketch we will see how to use these two methods and display the four result possibilities on serial monitor.
 */

// Macro at the beginning of the sketch to enable the chrono used in the sketch.
// This macro MUST be globally declared at the beginning of the sketch if we want to use the chrono.
// Note that the macro CHRONOS_ENABLE actually does exactly the same things as CHRONO_ENABLE.
CHRONOS_ENABLE

// 3 variables : a float analogTemp and an int analogTemperature. Both will receive the analog value of the methods used.
float analogTemp = 0;
int analogTemperature = 0;
// Also an int counter to increment after reading the analog values.
int counter = 0;

// Let's declare our shield-based Senseo instance.
SenseoUno Senseo;

void setup() {
  // Let's configure the serial monitor and the two chronos.
  Serial.begin(115200);
  Senseo.startChrono1(2000);
  Senseo.startChrono2(2000);
}

void loop() {
  // If there is a countdown achieved on chrono 1, we will read the 10-bits analog value as int and float with the first method, and display it on serial monitor.
  if((counter%2 == 0) && Senseo.isCountdown1()){
    Serial.println(F("\n/***** FIRST METHOD *****/"));
    Senseo.readAnalogTemp(analogTemp);
    Serial.println(analogTemp);
    Senseo.readAnalogTemp(analogTemperature);
    Serial.println(analogTemperature);
    // We also increment the counter by 1
    counter += 1;
  }

  // If there is a countdown achieved on chrono 1, we will read the 10-bits analog value as int and float with the second method, and display it on serial monitor.
  else if((counter%2 == 1) && Senseo.isCountdown2()){
    Serial.println(F("\n/***** SECOND METHOD *****/"));
    analogTemperature = Senseo.readAnalogTemp();
    Serial.println(analogTemperature);
    analogTemp = Senseo.readAnalogTemp();
    Serial.println(analogTemp);
    // We also increment the counter by 1
    counter += 1;
  }
  
  // Once the counter is equal to 20 (and there is no more countdown), we shall stop the chronos and therefore the reading.
  else if(counter == 20) Senseo.stopChronos();
}
