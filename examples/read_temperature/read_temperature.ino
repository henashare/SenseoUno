#include <SenseoUno.h>

/*
 * read_temperature.ino
 * Shows how to read a temperature from a temperature sensor with the SenseoUno.
 * This sketch uses the shield-based configuration instance which internally declares the analog input as A0 on the Arduino Uno board.
 * The shield-based instance also sets the NTC attributes as 10k resistor for both the 25 °C resistor and the serial resistor. The Beta is 4300.
 * PAY ATTENTION that these attributes may vary between two NTC resistors. It is possible to change the default attributes of the shield-based
 * instance. To do so the user can use the Senseo.setNTCvalues(NTCInitialResistor, serialResistor, Beta). Note that this method can be used on
 * the shield-based SenseoUno instance and on the SenseoUno empty instance. It can set and / or replace the NTC attributes.
 * 
 * In the sketch the user will see the two possibilities to read the value from the sensor with a SenseoUno instance. These two possibilities
 * use the same method. In each case there is a possibility to read the temperature as an int value or as a float value.
 * 
 * This sketch also uses the chronos of the SenseoUno library. There are two examples "single_chrono.ino" and "two_chronos.ino" if necessary.
 * There are two methods to read the temperature. We can also put the result in two different types : int and float.
 * In this sketch we will see how to use these two methods and display the four result possibilities on serial monitor.
 */

// Macro at the beginning of the sketch to enable the chrono used in the sketch.
// This macro MUST be globally declared at the beginning of the sketch if we want to use the chrono.
// Note that the macro CHRONOS_ENABLE actually does exactly the same things as CHRONO_ENABLE.
CHRONOS_ENABLE

// 3 variables : a float temp and an int temperature. Both will receive the analog value of the methods used.
float temp = 0;
int temperature = 0;
// Also an int counter to increment after reading the analog values.
int counter = 0;

// Let's declare our shield-based Senseo instance.
SenseoUno Senseo;

void setup() {
  // Let's configure the serial monitor and the two chronos.
  Serial.begin(115200);
  Senseo.startChrono1(2000);
  Senseo.startChrono2(2000);
  //Senseo.setNTCvalues(10000.0, 10000.0, 4300.0);  // This line is made to set or change the NTC resistor attributes.
                                                    // These attributes may vary between two NTC resistors.
                                                    // These attributes can be found in the datasheet of the component.
                                                    // Here these are the shield-based attributes (already set internally).
                                                    // There is also a fourth argument set to 25 per default. This argument
                                                    // is not obligatory as you can see. It must be an int value.
}

void loop() {
  // If there is a countdown achieved on chrono 1, we will read the 10-bits analog value as int and float with the first method, and display it on serial monitor.
  if((counter%2 == 0) && Senseo.isCountdown1()){
    Serial.println(F("\n/***** FIRST METHOD *****/"));
    Senseo.readTemp(temp);
    Serial.println(temp);
    Senseo.readTemp(temperature);
    Serial.println(temperature);
    // We also increment the counter by 1
    counter += 1;
  }

  // If there is a countdown achieved on chrono 1, we will read the 10-bits analog value as int and float with the second method, and display it on serial monitor.
  else if((counter%2 == 1) && Senseo.isCountdown2()){
    Serial.println(F("\n/***** SECOND METHOD *****/"));
    temperature = Senseo.readTemp();
    Serial.println(temperature);
    temp = Senseo.readTemp();
    Serial.println(temp);
    // We also increment the counter by 1
    counter += 1;
  }
  
  // Once the counter is equal to 20 (and there is no more countdown), we shall stop the chronos and therefore the reading.
  else if(counter == 20) Senseo.stopChronos();
}
