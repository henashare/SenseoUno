#include <SenseoUno.h>

/*
 * sleep_no_autoreset.ino
 * This sketch shows how to activate a sleep mode without automatic reset a SenseoUno instance.
 * Please note that the macro NO_RESET as third agument of the Senseo.sleep() method is never used as the default config is no reset
 */

// First let's create our empty SenseoUno instance
SenseoUno Senseo(EMPTY_INSTANCE);

SENSEO_SLEEP // The macro SENSEO_SLEEP_1 works the same way, it allows a sleep mode exit with D2 and D3
// SENSEO_SLEEP_2 // Allows to exit sleep mode only with D2
// SENSEO_SLEEP_3 // Allows to exit sleep mode only with D3

void setup()
{
	Serial.begin(115200); // Let's begin a serial communication
}

void loop()
{
	Serial.print(F("\n\nBEGINNING OF THE SLEEP MODE\n\n")); //
	delay(5); // A few delay to wait for the information to be displayed on the serial monitor
	Senseo.sleep(); // This line allows to enter in sleep mode with config number 1 : rising edge exit on D2 or D3
  // Senseo.sleep(SENSEO_FALLING); // This line allows to enter in sleep mode with the following config : falling edge exit on D2 or D3
  // Senseo.sleep(SENSEO_RISING, WAKE_UP_3); // This line allows to enter in sleep mode with the following config : rising edge exit only on D3
  // Senseo.sleep(SENSEO_RISING, WAKE_UP_3, NO_RESET); // This line allows to enter in sleep mode with the following config : rising edge exit only on D3 with no reset after exit
	Serial.begin(115200); // After leaving sleep mode we must restart the serial communication (and also other functionalities as analog to digital converter, chronos, etc)
	Serial.print(F("\n\nEND OF THE SLEEP MODE\n\n"));
	delay(1000);
}
