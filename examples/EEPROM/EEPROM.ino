#include <SenseoUno.h>

/*
 * EEPROM.ino
 * This sketch shows how to easily write, read and get a value in the EEPROM thanks the SenseoUno class and instance.
 * When a SenseoUno instance is created, the EEPROM address is set to 0. Max value for AtMega328P : 1023. Max value for AtMega168 : 511.
 * This sketch offers the possibility (1) to set another address than the default address, (2) to get and print the data at the EEPROM address memory, (3) write another value to this address.
 * To do so, we must select either we want to read the current or write another one instead. To read, insert the character "R" in the serial monitor. To write, insert the character "W" in the serial monitor.
 */

// First we create our empty SenseoUno instance
SenseoUno Senseo(EMPTY_INSTANCE);

// We shall create 3 global variables used for the EEPROM
unsigned int coffees = 0;
int read_coffee_value = 0;
int val;

// Then we create 2 global variables for the serial conversion from the keyboard
int int_msg;
char message[2];

void setup()
{
	Serial.begin(115200); // Let's open a serial communication
	//Senseo.set_memory_address(15); // There is also the possibility to set antother address for reading/writing in the EEPROM
	read_coffee_value = Senseo.get_cups(); // We first get the value at the address (default address is 0) | Note that if the EEPROM has never been written at this address, the value should be 255
	Serial.print("\n\nWHAT IS IN THE MEMORY AT THE BEGINNING OF THE SKETCH : "); // Then we print the value to the serial monitor
	Serial.println(read_coffee_value);
}

void loop()
{
	if(Serial.available() > 0){ // If we receive at least one character from the serial monitor
		delay(1); // We wait a few time so that every character sent (it should be maximum one character) arrives in the serial buffer
		int_msg = Serial.read(); // We receive in an integer the byte written in the serial communication
		reset_Serial(); // We will reset the serial communication, so that we destroy the unnecessary characters remaining
		message[0] = (char)int_msg; // Then let's convert the byte to a character
		
		// If the character sent is "W" for Write...
		if(strcmp(message, "W") == 0){
		  coffees += 1; // ...Then we increment the coffees number by 1...
		  Senseo.save_cups(coffees); // ... And we save this value to the EEPROM
		}
		// Or if the character sent is "R" for Read...
		else if(strcmp(message, "R") == 0){
			read_coffee_value = Senseo.get_cups(); // ... We will read the value from the EEPROM memory...
			Serial.print("\n\nVALUE TAKEN FROM THE EEPROM :\n");
			Serial.print(read_coffee_value); // ... And print this value to the serial monitor
			Serial.print(" | ");
			Serial.print(coffees); // Then print the last value written in the EEPROM
			Serial.print(" | ");
			Serial.println(Senseo.get_memory_address()); // Finally, we will print the address of the EEPROM memory data
		}
	}
}

void reset_Serial(){
	Serial.end();
	Serial.begin(115200);
}
