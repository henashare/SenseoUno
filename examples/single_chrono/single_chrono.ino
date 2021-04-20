#include <SenseoUno.h>

/*
 * single_chrono.ino
 * Shows how to use one chrono of the SenseoUno instance.
 * This sketch uses the built-in led of the Arduino on digital pin 13.
 * With one counter incrementing every chrono countdown, we make a blinking led program for 10 cycles.
 * After 10 cycles, we shall stop the chrono and verify that the countdown condition is no longer fulfilled.
 */

// Macro at the beginning of the sketch to enable the chrono used in the sketch.
// This macro MUST be globally declared at the beginning of the sketch if we want to use the chrono.
// Note that the macro CHRONOS_ENABLE actually does exactly the same things as CHRONO_ENABLE.
CHRONO_ENABLE

// Let's create a SenseoUno empty instance.
SenseoUno Senseo(EMPTY_INSTANCE);
int counter = 0;

void setup()
{
  // Open a serial communication at 115200 bauds
  Serial.begin(115200);
  // Set the chrono countdown at 2 seconds
  Senseo.startChrono(2000);
  Senseo.setLed(D13);
}

void loop()
{
  // If the countdown of the chrono of the Senseo has been reached, increment the counter by 1 and display a message.
  if(Senseo.isCountdown()){
    // Either the counter is pair, in which case we shall activate the LED and increment the counter by 1.
    if(counter%2 == 0){
      counter +=1;
      Senseo.activateLed();
      // Then, display these actions on serial monitor.
      Serial.print(F("\nCounter : "));
      Serial.println(counter);
      Serial.println(F("LED ON"));
    }

    // Either the counter is pair, in which case we shall shutdown the LED and increment the counter by 1.
    else if(counter%2 == 1){
      counter +=1;
      Senseo.shutdownLed();
      // Then, display these actions on serial monitor.
      Serial.print(F("\nCounter: "));
      Serial.println(counter);
      Serial.println(F("LED OFF"));
    }
  }

  // If the counter is equal to 20, which means 10 ON and OFF cycles, we shall stop the chrono.
  if(counter == 20){
    Serial.println(F("\n/***** STOP CHRONO *****/"));
    Senseo.stopChrono(); // Note that the Senseo.stopChronos() method does the same.
    counter += 1; // The, increment one last time the counter so that we do not go anymore in this conditional code block.
  }
}
