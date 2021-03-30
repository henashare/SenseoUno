#include <SenseoUno.h>
CHRONO_ENABLE

/*
 * shield_settings.ino
 * Shows how to easily declare a SenseoUno instance, based on our shield.
 * This instance sets the following defaults configuration :
 * D9, D10, D11 as analog PWM | where D9 = Red, D10 = Green, D11 = Blue | All outputs
 * D5 as the heater, and D6 as the pump |All outputs
 * D7 as minimal water level detector for 1 cup, D8 as minimal water level detector for 2 cups |All inputs
 * D2 as push button for 1 cup | D4 as push button for 2 cups | D3 as the central push button | All inputs
 * A0 as temperature analog input sensor
 */

// Creation of our SenseoUno instance | 2 different ways to declare this instance | Virtually represents the Senseo coffee machine
SenseoUno Senseo; // This uncommented instance is the shortest and most evident way to create our machine.
//SenseoUno Senseo(SHIELD_INSTANCE); // This commented instance is another way to create our machine. SHIELD_INSTANCE may be replaced by true or by 1

void setup()
{
  // Initialisation of the serial monitor for Bluetooth
  Serial.begin(115200);
  Senseo.setRGB(9, 10, 11);
  Senseo.startChrono(2000);
  // The coffee machine is now configured with our shield. For a custom config, check the "custom_settings.ino" sketch
}

void loop()
{
  Serial.print("\n\n/***** CHRONOS *****/");
  Serial.print(chrono1);
  Serial.print(" | ");
  Serial.println(chrono2);
  delay(2000);
  Senseo.resetChrono2();
}
