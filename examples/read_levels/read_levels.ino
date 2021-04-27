#include <SenseoUno.h>

/*
 * read_levels.ino
 * Shows how to detect if the water levels are still high enough.
 * This sketch uses the shield-based configuration instance which internally declares 2 water levels on pins 7 and 8 on the 
 * Arduino Uno board. The first water level is on pin 7, the second is on pin 8. Note that there is possibility to use only
 * one of these two levels. If the user wants to use the Senseo.readLvl() method he should use it as Senseo.readLvl1(). Note
 * that in the SenseoUno library the unique water level is acts as the first water level (level 1 / Lvl1).
 * When a water level is not high enough a warning message is displayed.
 */

SenseoUno Senseo;

void setup(){
  // We first configure the serial communication on 115200 bauds.
  Serial.begin(115200);
}

void loop(){
  /* Then, there are 2 possibilities : */
  
  // First possibility : the first water level is not high enough.
  if(!Senseo.readLvl1()){ // if(!Senseo.readLvl1()) is like if(!Senseo.readLvl()) 
                          // and like if(Senseo.readLvl1() == 0) and like if(Senseo.readLvl() == 0)
    Serial.print("\n\nThe first water level is not high enough !\n\n");
    delay(1000); // This delay is here to prevent a too fast display of the warning message
  }
  // Second possibility : the second water level is not high enough.
  if(!Senseo.readLvl2()){ // if(!Senseo.readLvl2()) is like if(Senseo.readLv2() == 0) 
    Serial.print("\n\nThe second water level is not high enough !\n\n");
    delay(1000); // This delay is here to prevent a too fast display of the warning message
  }
}
