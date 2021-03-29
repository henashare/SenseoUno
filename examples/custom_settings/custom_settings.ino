#include <SenseoUno.h>

/*
 * custom_settings.ino
 * Shows how to easily declare an empty SenseoUno instance.
 * This instance has to be declared with a EMPTY_INSTANCE macro.
 * Then, let's configure our Senseo machine with its most common features in the setup function.
 */

// Creation of our SenseoUno instance | Virtually represents the Senseo coffee machine | EMPTY_INSTANCE may be replaced by false or by 0
SenseoUno Senseo(EMPTY_INSTANCE);

void setup()
{
  /***************************************************************************************************************************************************************************/
  // 3 functions to configure the LEDs | Senseo.setRGB() is used | Senseo.setAnalogRGB() and Senseo.setLed() can be used by being uncommented
  Senseo.setRGB(D7, D8, D9); // Sets D7, D8 and D9 as digital outputs | D7 = Red, D8 = Green, D9 = Blue
  // Senseo.setAnalogRGB(D5, D6, D3) // Sets D5, D6 and D3 as analog PWM outputs for 3 LEDs or or one RGB Led | D5 = Red, D6 = Green, D3 = Blue
  // Senseo.setLed(2) // Sets D2 as digital output for one Led

  /***************************************************************************************************************************************************************************/
  // 1 function to configure 3 pushbuttons | There is no function made to configure only one push button, because a Senseo machine always comes with 3 buttons
  Senseo.set3Buttons(10, 11, 12); // Sets D10, D11 and D12 as digital outputs | D10 = push button for 1 cup, D11 = push button for 2 cups, D12 = push button for central button of Senseo
  // PAY ATTENTION : impossible to use deep sleep modes of the library if none of the 3 BPs are D2 or D3

  /***************************************************************************************************************************************************************************/
  // 3 functions to configure the power outputs of the Senseo, which are the 230V pump and the 230V heater
  Senseo.setPower(D13, D4); // Sets D13 and D4 as digital outputs | D13 = pump, D4 = heater
  //Senseo.setPump(13); // Sets D13 as digital output for the pump
  //Senseo.setHeat(3); // Sets D3 as digital output for the heater

  /***************************************************************************************************************************************************************************/
  // 2 functions to configure the water level inputs of the Senseo | Either 2 water levels, either 1 water level
  Senseo.setLevels(D5, D6); // Sets D5 and D6 as digital inputs | D5 = minimal level for 1 cup, D6 = minimal level for 2 cups
  // Senseo.setLevel(D9); // Sets D9 as digital input | D9 = minimal water level

  /***************************************************************************************************************************************************************************/
  // 1 function to configure the temperature sensor analog input
  Senseo.setTempSensor(15); // Sets A1 as analog input
  // Senseo.setCaptTemp(A1); // Sets A1 as analog input
  
  /***************************************************************************************************************************************************************************/
  // Initialisation of the serial monitor for debugging and verifications.
  Serial.begin(9600);
  
  
  // The coffee machine is now configured with our shield. For a defaults config (based on our shield), check the "shield_settings.ino" sketch
}

void loop()
{
  
}
