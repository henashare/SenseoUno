#include <SenseoUno.h>

/*
 * read_pushbuttons.ino
 * Shows how to detect a push on a pushbutton.
 * This sketch uses the shield-based configuration instance which internally declares the 3 pushbuttons on pins 2, 3 and 4 
 * on the Arduino Uno board. The 1-cup pushbutton is on pin 2, the 2-cups button is on pin 4, and the central button is on pin 3.
 * When a button is pushed a corresponding message is displayed on serial monitor.
 */

SenseoUno Senseo;

void setup() {
  // We first configure the serial communication on 115200 bauds.
  Serial.begin(115200);
}

void loop() {
  // Then, there are 3 possibilities :
  // First possibility : the 1-cup button is pushed.
  if(Senseo.readButton1C()){
    delay(50); // This delay is here to prevent a rebound effect when the button is pushed
    Serial.print("\n\n1-cup button is pushed\n\n");
    delay(1000);
  }
  // Second possibility : the main button is pushed.
  else if(Senseo.readButtonMain()){
    delay(50);
    Serial.print("\n\nMain button is pushed\n\n");
    delay(1000);
  }
  // Third possibility : the 2-cups button is pushed.
  else if(Senseo.readButton2C()){
    delay(50);
    Serial.print("\n\n2-cups button is pushed\n\n");
    delay(1000);
  }
}
