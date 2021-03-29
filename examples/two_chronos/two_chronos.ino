#include <SenseoUno.h>

/*
 * two_chronos.ino
 * Shows how to use the two chronos of the SenseoUno instance.
 * With two counters, let's verify that we can use two different chrono periods.
 * With these two chronos we can display informations on serial monitor, and increment each counter separately.
 * We can also decide to stop incrementing one counter, which is a way to discredit a chrono while the other one is still useful.
 * Finally, we shall stop the chronos and therefore verify that the counters do not increment anymore.
 */

// Macro at the beginning of the sketch to enable the chronos used in the sketch.
// This macro MUST be globally declared at the beginning of the sketch if we want to use the chronos.
// Note that the macro CHRONO_ENABLE actually does exactly the same things as CHRONOS_ENABLE.
CHRONOS_ENABLE

// Let's create a SenseoUno empty instance.
SenseoUno Senseo(EMPTY_INSTANCE);
int counter1 = 0;
int counter2 = 0;

void setup()
{
  // Open a serial communication at 115200 bauds
  Serial.begin(115200);
  // Set the first chrono countdown at 5 seconds
  Senseo.startChrono1(5000);
  // Set the second chrono countdown at 1 second
  Senseo.startChrono2(1000);
}

void loop()
{
  // If the countdown of the chrono 1 of the Senseo has been reached, increment the counter1 by 1 and display a message.
  if(Senseo.isCountdown1()){
    counter1 += 1;
    Serial.print("\n/***** CHRONO 1 *****/\nChrono 1 : 5 seconds elapsed | Counter of the chrono 1 : ");
    Serial.println(counter1);
  }
    
  // If counter2 is less than 26 and the countdown of the chrono 2 of the Senseo has been reached, increment the counter2 by 1 and display a message.
  // Note that the verification of the chrono must be the last verified condition or the verification may not work fine.
  else if((counter2 < 25) && Senseo.isCountdown2()){
    counter2 += 1;
    Serial.print("\nChrono 2 : 1 second elapsed | Counter of the chrono 2 : ");
    Serial.println(counter2);
  }

  // If counter1 is bigger or equal to 9 and the countdown of the chrono 2 of the Senseo has been reached.
  // Note that the verification of the chrono must be the last verified condition or the verification may not work fine.
  else if((counter1 >= 9) && Senseo.isCountdown2()){
    Serial.println("The chrono 2 is still enabled");
  }

  // If the counter1 is equal to 10, we shall stop the two chronos.
  if(counter1 == 10){
    Serial.println("\n/***** STOP CHRONO *****/");
    Senseo.stopChronos(); // Note that the Senseo.stopChrono() method does the same.
    counter1 += 1;
  }
}
