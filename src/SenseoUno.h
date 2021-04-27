// Library Senseo.h
/*
  This library is made in order to configure and drive a Senseo coffee machine with an Arduino UNO.
  This library is configured to run on AtMega 328P / 168 / 328 micro controllers, so for the Arduino UNO.
  To do so, this library defines specific macros and functions, which are used ONLY for the UNO !!!
  This library will not work on a Arduino Mega or else.
  Other libraries may follow, either for specific board architectures (Arduino Mega, Nano, etc), or for general purpose.
  A library for general purpose will necessarily be less efficient and precise (and less funny to code).
  As this library is based on the UNO Senseo shield, that's why we decided to focus on a specific architecture.
*/

#ifndef __SENSEO_UNO_H__
#define __SENSEO_UNO_H__

#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <math.h>

// Pin mapping for Arduino UNO
#ifndef D0
#define D0 0
#endif

#ifndef D1
#define D1 1
#endif

#ifndef D2
#define D2 2
#endif

#ifndef D3
#define D3 3
#endif

#ifndef D4
#define D4 4
#endif

#ifndef D5
#define D5 5
#endif

#ifndef D6
#define D6 6
#endif

#ifndef D7
#define D7 7
#endif

#ifndef D8
#define D8 8
#endif

#ifndef D9
#define D9 9
#endif

#ifndef D10
#define D10 10
#endif

#ifndef D11
#define D11 11
#endif

#ifndef D12
#define D12 12
#endif

#ifndef D13
#define D13 13
#endif

#ifndef A0
#define A0 14
#endif

#ifndef A1
#define A1 15
#endif

#ifndef A2
#define A2 16
#endif

#ifndef A3
#define A3 17
#endif

#ifndef A4
#define A4 18
#endif

#ifndef A5
#define A5 19
#endif

// Macros for boolean states | true and false terms can also be used just as 1 and 0

#ifndef HIGH
#define HIGH 1
#endif

#ifndef LOW
#define LOW 0
#endif

/*	Macros for the boolean argument of one constructor | EMPTY_INSTANCE is used if the user does not want to have any custom instance | SHIELD_INSTANCE can be used if the user wants the shield-based configuration.
	Note there is another constructor with no boolean argument. This constructor is equivalent to a boolean constructor declared with the SHIELD_INSTANCE macro.	*/
 
#define EMPTY_INSTANCE 0
#define SHIELD_INSTANCE 1

/*	Macros for the chrono of the Senseo instance. One of the macros CHRONO_ENABLE or CHRONOS_ENABLE must be written as a global macro at the beginning of the .ino sketch. Note that only one of these must be written.
	The two macros do the same thing. They both insert two variables of type volatile int : chrono1 and chrono2. These two macros also define an interrupt service routine based on the timer1 overflow interruption.
	The macro isCountdown() is a simplified writing for a SenseoUno boolean method that checks if the value set in the startChrono() method has been reached. This macro can be used as a common method in the .ino sketch.
	The macro isCountdown1() is a simplified writing for a SenseoUno boolean method that checks if the value set in the startChrono1() method has been reached. This macro can be used as a common method in the .ino sketch.
	The macro isCountdown2() is a simplified writing for a SenseoUno boolean method that checks if the value set in the startChrono2() method has been reached. This macro can be used as a common method in the .ino sketch.	*/
#define CHRONO_ENABLE volatile int chrono1 = 0; volatile int chrono2 = 0; ISR(TIMER1_OVF_vect){chrono1 += 1; chrono2 += 1; if(chrono1 > 32500) chrono1 = 0; else if(chrono2 > 32500) chrono2 = 0;}
#define CHRONOS_ENABLE CHRONO_ENABLE
#define isCountdown() isElapsedChrono1(&chrono1)
#define isCountdown1() isElapsedChrono1(&chrono1)
#define isCountdown2() isElapsedChrono2(&chrono2)
#define resetChrono() rebootChrono(&chrono1)
#define resetChronos() rebootChronos(&chrono1, &chrono2)
#define resetChrono1() rebootChrono(&chrono1)
#define resetChrono2() rebootChrono(&chrono2)
#define stopChronos() stopChrono()

/*	Macros for the sleep mode of the SenseoUno instance	*/
#define SENSEO_SLEEP ISR(INT0_vect){power_all_enable();} ISR(INT1_vect, ISR_ALIASOF(INT0_vect));
#define SENSEO_SLEEP_1 SENSEO_SLEEP
#define SENSEO_SLEEP_2 ISR(INT0_vect){power_all_enable();}
#define SENSEO_SLEEP_3 ISR(INT1_vect){power_all_enable();}
#define SENSEO_RISING	0
#define SENSEO_FALLING	1
#define SENSEO_CHANGE	2
#define SENSEO_LOW	3
#define WAKE_UP	0
#define WAKE_UP_1	0
#define WAKE_UP_2	1
#define WAKE_UP_3	2
#define NO_RESET 0
#define AUTO_RESET 1

class SenseoUno{
	public:
		
		// Constructor of the Senseo instance with asking a boolean argument. Through this argument the user decides whether he wants a shield-based configuration or an empty instance to configure with set___ public methods.
		SenseoUno(bool shieldOrNot);
		// Constructor of the Senseo instance with default values (in the .cpp file) corresponding to the shield. It is possible to change its values with the following set___ public methods.
		SenseoUno();

		// Public function made to be used in the .ino sketch --> made to set the different pins of a Led RGB as output pins.
		void setRGB(short pinR, short pinG, short pinB);
		// Public function made to be used in the .ino sketch --> made to set the different pins of a Led RGB as PWM output pins.
		void setAnalogRGB(short pinR, short pinG, short pinB);
		// Public function made to be used in the .ino sketch --> made to set the pin of a Led as output pin.
		void setLed(short LED_pin);
		
		// Public function made to be used in the .ino sketch --> made to set the pins of the 3 pushbuttons as input pins.
		void set3Buttons(short pin1T, short pin2T, short middlePin);
		
		// Public function made to be used in the .ino sketch --> made to set the pins of the 2 power devices - pump and heat resistor - as output pins.
		void setPower(short pinPump, short pinHeatRes);
		// Public function made to be used in the .ino sketch --> made to set the pin of the pump as an output pin.
		void setPump(short pinPump);
		// Public function made to be used in the .ino sketch --> made to set the pin of the heat resistor as an output pin.
		void setHeat(short pinHeat);
		
		// Public function made to be used in the .ino sketch --> made to set two pins for two Hall effect level sensors as input pins.
		void setLevels(short pinLvl1, short pinLvl2);
		// Public function made to be used in the .ino sketch --> made to set one pin for one Hall effect level sensor as input pin.
		void setLevel(short pinLvl);
		
		// Public function made to be used in the .ino sketch --> made to configure one analog pin as an analog input.
		void setTempSensor(short tempSens);
		// Public function made to be used in the .ino sketch --> made to set the values of the NTC resistor
		void setNTCvalues(float sensor_initial_resistor, float serial_resistor, float Beta, int initial_NTC_temperature=25);
		
		// Public functions made to be used in the .ino sketch --> made to read the digital input state of one of the button
		bool readButton1C();
		bool readButton2C();
		bool readButtonMain();
		
		// Public functions made to be used in the .ino sketch --> made to read the digital input state of (one of) the levels
		bool readLvl();
		bool readLvl1();
		bool readLvl2();
		
		// Public functions made to be used in the .ino sketch --> made to read the analog input value of the temperature NTC sensor
		/* Note : this function is overload, which means there are multiple ways to call this function and multiple types */
		float readAnalogTemp();
		void readAnalogTemp(float &tempValue);
		void readAnalogTemp(int &tempValue);
		
		// Public function made to be used in the .ino sketch --> made to read the value of the temperature from the NTC sensor
		/* Note : this function is overload, which means there are multiple ways to call this function and multiple types */
		float readTemp();
		void readTemp(float &tempValue);
		void readTemp(int &tempValue);
		
		// Public function made to be used in the .ino sketch --> made to activate the pump
		void activatePump();
		// Public function made to be used in the .ino sketch --> made to shutdown the pump
		void shutdownPump();
		
		// Public function made to be used in the .ino sketch --> made to activate the heat resistor
		void activateHeat();
		// Public function made to be used in the .ino sketch --> made to shutdown the heat resistor
		void shutdownHeat();
		
		// Public function made to be used in the .ino sketch --> made to activate the Led
		void activateLed();
		// Public function made to be used in the .ino sketch --> made to shutdown the Led
		void shutdownLed();
		
		// Public function made to be used in the .ino sketch --> made to activate the RGB Led
		void activateRGB(bool R, bool G, bool B);
		// Public function made to be used in the .ino sketch --> made to shutdown the RGB Led
		void shutdownRGB();
		
		// Public function made to be used in the .ino sketch --> made to activate the red Led
		void activateR();
		// Public function made to be used in the .ino sketch --> made to shutdown the red Led
		void shutdownR();
		
		// Public function made to be used in the .ino sketch --> made to activate the green Led
		void activateG();
		// Public function made to be used in the .ino sketch --> made to shutdown the green Led
		void shutdownG();
		
		// Public function made to be used in the .ino sketch --> made to activate the blue Led
		void activateB();
		// Public function made to be used in the .ino sketch --> made to shutdown the blue Led
		void shutdownB();
		
		// Public function made to be used in the .ino sketch --> made to drive the RGB with a specific color choice | Note : values go from 0 to 255
		void analogWriteRGB(short R, short G, short B);
		// Public function made to be used in the .ino sketch --> made to close the PWM outputs of the RGB
		void analogShutdownRGB();

		// Public function made to be used in the .ino sketch --> made to start the chrono with a milliseconds countdown value
		void startChrono(long countdown_value);
		// !!! Public function !!!NOT!!! made to be used in the .ino sketch. Use the macro isCountdown() or isCountdown1() instead --> made to check if the countdown value has been reached !!!
		bool isElapsedChrono1(volatile int *val);
		// !!! Public function !!!NOT!!! made to be used in the .ino sketch. Use the macro isCountdown2() instead --> made to check if the countdown value has been reached !!!
		bool isElapsedChrono2(volatile int *val);
		// !!! Public function !!!NOT!!! made to be used in the .ino sketch. Use the macro resetChrono(), resetChrono1() or resetChrono2() instead --> made to reset the chrono1 or / and the chrono2 to 0 !!!
		void rebootChrono(volatile int *val);
		 // !!! Public function !!!NOT!!! made to be used in the .ino sketch. Use the macro resetChronos() instead --> made to reset the chrono1 or / and the chrono2 to 0 !!!
		void rebootChronos(volatile int *val1, volatile int *val2);
		// Public function made to be used in the .ino sketch --> made to start the chrono1 with a milliseconds countdown value
		void startChrono1(long countdown_value);
		// Public function made to be used in the .ino sketch --> made to start the chrono2 with a milliseconds countdown value
		void startChrono2(long countdown_value);
		// Public function made to be used in the .ino sketch --> made to stop the chrono
		void stopChrono();
		
		// Public function made to be used in the .ino sketch --> made to specify the address in the EEPROM memory corresponding to the data we want to get
		void set_memory_address(int address);
		// Public function made to be used in the .ino sketch --> made to get the current reading/writing address in the EEPROM memory
		int get_memory_address();
		// Public function made to be used in the .ino sketch --> made to write a value between 0 and 255 in the EEPROM memory, value corresponding to the number of cups made since last descaling
		void save_cups(unsigned int num);
		// Public function made to be used in the .ino sketch --> made to read a value in the EEPROM memory corresponding to the number of cups made since last descaling
		int get_cups();
		
		// Public function made to be used in the .ino sketch --> made to activate / start the sleep mode of the SenseoUno. Its configuration is determined by the upper defined macros
		void sleep(int num1=0, int num2=0, bool autoreset=0);
		// Public function made to be used in the .ino sketch --> made to activate an internal reset within the SenseoUno instance. It allows to restart the whole program
		void internal_reset();
		
		// Public function to be used in the .ino sketch --> made to init the UART communication to the specified baudrate
		void begin(int baudrate, long freq=16000000);
		
	private:
		short ledR, ledG, ledB, pump, heater, lvl1, lvl2, Button1, Button2, ButtonC, anaTemp, PWM0, PWM1, PWM2;
		int counter1, counter2, EEPROM_value;
		unsigned int EEPROM_address;
		float RT0, R0, B, T0;

		// Private function linked to two other private functions : toRegisterB() and toRegisterC() --> This function is made to determine the right port and therefore the right registers to call for digital use.
		short whichPort(short *num);
		// Private function linked to two other functions : whichPort() and toRegisterC() --> This function is made to determine the right port and therefore the right registers to call
		void toRegisterB(short *pin);
		// Private function linked to two other functions : whichPort() and toRegisterB() --> This function is made to determine the right port and therefore the right registers to call
		void toRegisterC(short *pin);

		// Private function to set a pin as an output --> Similar to pinMode(X, OUTPUT); but more efficient, made for the UNO hardware, it is an internal function that cannot be called by the user.
		void setOutput(short *portnum, short *pin);
		// Private function to set a pin as an input --> Similar to pinMode(X, INPUT); but more efficient, made for the UNO hardware, it is an internal function that cannot be called by the user.
		void setInput(short *portnum, short *pin);

		// Private function to read the state of a digital input --> Similar to digitalRead(X); but more efficient, made for the UNO hardware, it is an internal function that cannot be called by the user.
		bool readDig(short *portnum, short *pin);
		// Private function to activate an output pin --> Similar to digitalWrite(X, HIGH); but more efficient, made for the UNO hardware, it is an internal function that cannot be called by the user.
		void activate(short *portnum, short *pin);
		// Private function to activate an output pin --> Similar to digitalWrite(X, LOW); but more efficient, made for the UNO hardware, it is an internal function that cannot be called by the user.
		void shutdown(short *portnum, short *pin);
		
		// Private function to configure the PWM outputs of the timer0.
		void configPWM0(short *val);
		// Private function to write a 0 value to the OCR0A and OCR0B registers.
		void resetPWM0();
		// Private function to configure the PWM outputs of the timer1.
		void configPWM1(short *val);
		// Private function to write a 0 value to the OCR1A and OCR1B registers.
		void resetPWM1();
		// Private function to configure the PWM outputs of the timer2.
		void configPWM2(short *val);
		// Private function to write a 0 value to the OCR2A and OCR2B registers.
		void resetPWM2();
		
		// Private function to activate a specific PWM output.
		void activatePWM(short *PWM, short *num);
		
		// Private function made to be used in the .ino sketch --> made to configure an 8-bits chrono on timer 1, based on the PWM phase-correct configuration. This config allows tu use the timer and the PWM outputs.
		void configChrono();
	};

#endif
