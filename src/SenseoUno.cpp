#include "SenseoUno.h"

/*BOOLEAN CONSTRUCTOR*/

SenseoUno::SenseoUno(bool shieldOrNot): PWM0(0), PWM1(0), PWM2(0)
{
	if(shieldOrNot == SHIELD_INSTANCE){
		ledR = D9; ledG = D10; ledB = D11; pump = D6; heater = D5; lvl1 = D7; lvl2 = D8; Button1 = D2; Button2 = D4; ButtonC = D3; anaTemp = A0;
		this->setAnalogRGB(ledR, ledG, ledB);
		this->setPower(pump, heater);
		this->setLevels(lvl1, lvl2);
		this->set3Buttons(Button1, Button2, ButtonC);
		this->setTempSensor(anaTemp);
	}
	else if(shieldOrNot == EMPTY_INSTANCE){
		this->configPWM1(&PWM1);
	}
}

/*SHIELD ARGUMENTLESS CONSTRUCTOR*/

SenseoUno::SenseoUno() : ledR(D9), ledG(D10), ledB(D11), pump(D6), heater(D5), lvl1(D7), lvl2(D8), Button1(D2), Button2(D4), ButtonC(D3), anaTemp(A0), PWM0(0), PWM1(0), PWM2(0)
{
	this->setAnalogRGB(ledR, ledG, ledB);
	this->setPower(pump, heater);
	this->setLevels(lvl1, lvl2);
	this->set3Buttons(Button1, Button2, ButtonC);
	this->setTempSensor(anaTemp);
}

/************************************************** SET FUNCTIONS **************************************************/

void SenseoUno::setRGB(short pinR, short pinG, short pinB){
	ledR = pinR; ledG = pinG; ledB = pinB;
	//End the analog PWM configuration established in the constructor
	this->analogShutdownRGB();
	//Determine the port of the pin of the Red LED and set it as an output
	short port = whichPort(&pinR);
	if(port > 0) setOutput(&port, &pinR);
	//Determine the port of the pin of the Green LED and set it as an output
	port = whichPort(&pinG);
	if(port > 0) setOutput(&port, &pinG);
	//Determine the port of the pin of the Blue LED and set it as an output
	port = whichPort(&pinB);
	if(port > 0) setOutput(&port, &pinB);
}

void SenseoUno::setAnalogRGB(short pinR, short pinG, short pinB){
	ledR = pinR; ledG = pinG; ledB = pinB;
	//If every LED pin is different of the others...
	if(pinR != pinG && pinG != pinB && pinB!= pinR){
		//... Let's decide which of the PWM available pins will be activated. To do this...
		//... let's create a list of the 3 pin numbers...
		short tab[3] = {pinR, pinG, pinB};
		//... and a port variable in which we will store the port number of the pin selected
		short port;
		for(int i = 0; i < 3; i++){
			
			if(tab[i] == pinR){
				if(pinR == 3) PWM2 += 2;
				else if(pinR == 5) PWM0 += 2;
				else if(pinR == 6) PWM0 += 1;
				else if(pinR == 9) PWM1 += 1;
				else if(pinR == 10) PWM1 += 2;
				else if(pinR == 11) PWM2 += 1;
				//If the pin of the red led is not a PWM one, no PWM will be activated
				else {PWM0 = 0; PWM2 = 0; PWM1 = 0;}
			}
			else if(tab[i] == pinG){
				if(pinG == 3) PWM2 += 2;
				else if(pinG == 5) PWM0 += 2;
				else if(pinG == 6) PWM0 += 1;
				else if(pinG == 9) PWM1 += 1;
				else if(pinG == 10) PWM1 += 2;
				else if(pinG == 11) PWM2 += 1;
				//If the pin of the green led is not a PWM one, no PWM will be activated
				else {PWM0 = 0; PWM2 = 0; PWM1 = 0;}
			}
			else if(tab[i] == pinB){
				if(pinB == 3) PWM2 += 2;
				else if(pinB == 5) PWM0 += 2;
				else if(pinB == 6) PWM0 += 1;
				else if(pinB == 9) PWM1 += 1;
				else if(pinB == 10) PWM1 += 2;
				else if(pinB == 11) PWM2 += 1;
				//If the pin of the blue led is not a PWM one, no PWM will be activated
				else {PWM0 = 0; PWM2 = 0; PWM1 = 0;}
			}
			//Let's set the pin corresponding to the i element of the list as an output
			port = whichPort(tab+i);
			setOutput(&port, (tab+i));
		}
	}
	//If any led pin is the same than the other one, no PWM will be activated
	else {PWM0 = 0; PWM2 = 0; PWM1 = 0;}
	//One it's decided, let's activate (or not) the PWM pins with the nice configuration
	configPWM0(&PWM0);
	configPWM1(&PWM1);
	configPWM2(&PWM2);
}

void SenseoUno::setLed(short LED_pin){
	ledR = LED_pin; ledG = 0; ledB = 0;
	//Determine the port of the pin of the Red LED and set it as an output
	short port = whichPort(&LED_pin);
	if(port > 0) setOutput(&port, &LED_pin);
}

void SenseoUno::set3Buttons(short pin1T, short pin2T, short middlePin){
	Button1 = pin1T; Button2 = pin2T; ButtonC = middlePin;
	short port = whichPort(&pin1T);
	if(port > 0) setInput(&port, &pin1T);
	port = whichPort(&pin2T);
	if(port > 0) setInput(&port, &pin2T);
	port = whichPort(&middlePin);
	if(port > 0) setInput(&port, &middlePin);
}

void SenseoUno::setPower(short pinPump, short pinHeat){
	pump = pinPump; heater = pinHeat;
	short port = whichPort(&pinPump);
	if(port > 0) setOutput(&port, &pinPump);
	port = whichPort(&pinHeat);
	if(port > 0) setOutput(&port, &pinHeat);
}

void SenseoUno::setPump(short pinPump){
	pump = pinPump;
	short port = whichPort(&pinPump);
	if(port > 0) setOutput(&port, &pinPump);
}

void SenseoUno::setHeat(short pinHeat){
	heater = pinHeat;
	short port = whichPort(&pinHeat);
	if(port > 0) setOutput(&port, &pinHeat);
}

void SenseoUno::setLevels(short pinLvl1, short pinLvl2){
	lvl1 = pinLvl1; lvl2 = pinLvl2;
	short port = whichPort(&pinLvl1);
	if(port > 0) setInput(&port, &pinLvl1);
	port = whichPort(&pinLvl2);
	if(port > 0) setInput(&port, &pinLvl2);
}

void SenseoUno::setLevel(short pinLvl){
	lvl1 = pinLvl; lvl2 = 0;
	short port = whichPort(&pinLvl);
	if(port > 0) setInput(&port, &pinLvl);
}

void SenseoUno::setTempSensor(short tempSens){
	anaTemp = tempSens;
	short port = whichPort(&tempSens);
	if(port == 2 && tempSens == 0) ADMUX &= ~(1<<MUX0) | ~(1<<MUX1) | ~(1<<MUX2) | ~(1<<MUX3);
	else if(port == 2 && tempSens == 1) {ADMUX &= ~(1<<MUX1) | ~(1<<MUX2) | ~(1<<MUX3); ADMUX |= (1<<MUX0);}
	else if(port == 2 && tempSens == 2) {ADMUX &= ~(1<<MUX0) | ~(1<<MUX2) | ~(1<<MUX3); ADMUX |= (1<<MUX1);}
	else if(port == 2 && tempSens == 3) {ADMUX &= ~(1<<MUX2) | ~(1<<MUX3); ADMUX |= (1<<MUX0) | (1<<MUX1);}
	else if(port == 2 && tempSens == 4) {ADMUX &= ~(1<<MUX0) | ~(1<<MUX1) | ~(1<<MUX3); ADMUX |= (1<<MUX2);}
	else if(port == 2 && tempSens == 5) {ADMUX &= ~(1<<MUX1) | ~(1<<MUX3); ADMUX |= (1<<MUX0) | (1<<MUX2);}
	else ; // If there is no analog pin, leave the function without configuring the analog converter
	ADMUX &= ~(1<<REFS1) | ~(1<<ADLAR);
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<< ADPS1) | (1<< ADPS2);
	ADCSRA &= ~(1<<ADATE) | ~(1<<ADIF) | ~(1<<ADIE);
	/* ADMUX :
	      MUX0, MUX1, MUX2, MUX3 to choose the analog pin
		  ADLAR to 0 in order to get a 10 bits value
	      Reference voltage = internal 5V. To do so, REFS1 = 0 and REFS0 = 1
	   ADCSRA :
	      No interrupt vector or else : ADATE, ADIF, et ADIE are set to 0
		  Conversion frequency for 10 bits must be between 50kHz et 200kHz | For Arduino Uno, 16MHz / 128 = 125kHz, so ADPS0, ADPS1, ADPS2 are set to 1
	      Conversion enabled (enabled does not mean launched / started, it is like powering a Senseo without pushing on start button) : ADEN = 1
		  When we will want to read the value of our sensor, we will set the ADSC bit to 1 in the program
	 */
}

/************************************************** READ FUNCTIONS **************************************************/

bool SenseoUno::readButton1C(){
	short pin = Button1;
	short port = whichPort(&pin);
	bool result = readDig(&port, &pin);
	return result;
}

bool SenseoUno::readButton2C(){
	short pin = Button2;
	short port = whichPort(&pin);
	bool result = readDig(&port, &pin);
	return result;
}

bool SenseoUno::readButtonMain(){
	short pin = ButtonC;
	short port = whichPort(&pin);
	bool result = readDig(&port, &pin);
	return result;
}

bool SenseoUno::readLvl(){
	short pin = lvl1;
	short port = whichPort(&pin);
	bool result = readDig(&port, &pin);
	return result;
}

bool SenseoUno::readLvl1(){
	short pin = lvl1;
	short port = whichPort(&pin);
	bool result = readDig(&port, &pin);
	return result;
}

bool SenseoUno::readLvl2(){
	short pin = lvl1;
	short port = whichPort(&pin);
	bool result = readDig(&port, &pin);
	return result;
}

float SenseoUno::readAnalogTemp(){
	ADCSRA |= (1<<ADSC); // We set the ADSC bit to 1 in order to begin the conversion
	while(ADCSRA & (1<<ADSC)); // While the conversion is not finished, nothing happens
	float tempValue = ADCL | (ADCH<<8); // Once the conversion is done, we read the two analog data registers ADCL and ADCH that are together a 10-bits value
	// Note : the ADCH is shifted 8 bits on the left, because the first 8 bits are reserved to the ADCL bits
	return tempValue; // We return the 10 bits value
}

void SenseoUno::readAnalogTemp(int &tempValue){
	ADCSRA |= (1<<ADSC); // We set the ADSC bit to 1 in order to begin the conversion
	while(ADCSRA & (1<<ADSC)); // While the conversion is not finished, nothing happens
	float temp = ADCL | (ADCH<<8); // Once the conversion is done, we read the two analog data registers ADCL and ADCH that are together a 10-bits value
	// Note : the ADCH is shifted 8 bits on the left, because the first 8 bits are reserved to the ADCL bits
	tempValue = (int) temp;
}

void SenseoUno::readAnalogTemp(float &tempValue){
	ADCSRA |= (1<<ADSC); // We set the ADSC bit to 1 in order to begin the conversion
	while(ADCSRA & (1<<ADSC)); // While the conversion is not finished, nothing happens
	tempValue = ADCL | (ADCH<<8); // Once the conversion is done, we read the two analog data registers ADCL and ADCH that are together a 10-bits value
	// Note : the ADCH is shifted 8 bits on the left, because the first 8 bits are reserved to the ADCL bits
}

/************************************************** ACTIVATE / SHUTDOWN FUNCTIONS **************************************************/
/***** PUMP *****/
void SenseoUno::activatePump(){
	short pin = pump;
	short port = whichPort(&pin);
	activate(&port, &pin);
}

void SenseoUno::shutdownPump(){
	short pin = pump;
	short port = whichPort(&pin);
	shutdown(&port, &pin);
}

/***** HEATER *****/
void SenseoUno::activateHeat(){
	short pin = heater;
	short port = whichPort(&pin);
	activate(&port, &pin);
}

void SenseoUno::shutdownHeat(){
	short pin = heater;
	short port = whichPort(&pin);
	shutdown(&port, &pin);
}

/***** SIMPLE LED *****/
void SenseoUno::activateLed(){
	short pin = ledR;
	short port = whichPort(&pin);
	activate(&port, &pin);
}

void SenseoUno::shutdownLed(){
	short pin = ledR;
	short port = whichPort(&pin);
	shutdown(&port, &pin);
}

/***** LED RGB *****/
void SenseoUno::activateRGB(bool R, bool G, bool B){
	bool tab[3] = {R, G, B};
	for(int i = 0; i<3; i++){
		if((i==0) && (tab[i] == 1)) activateR();
		else if((i==0) && (tab[i] == 0)) shutdownR();
		else if((i==1) && (tab[i] == 1)) activateG();
		else if((i==1) && (tab[i] == 0)) shutdownG();
		else if((i==2) && (tab[i] == 1)) activateB();
		else if((i==2) && (tab[i] == 0)) shutdownB();
	}
}

void SenseoUno::shutdownRGB(){
	shutdownR(); shutdownG(); shutdownB();
}

/***** LED R *****/
void SenseoUno::activateR(){
	short pin = ledR;
	short port = whichPort(&pin);
	activate(&port, &pin);
}

void SenseoUno::shutdownR(){
	short pin = ledR;
	short port = whichPort(&pin);
	shutdown(&port, &pin);
}

/***** LED G *****/
void SenseoUno::activateG(){
	short pin = ledG;
	short port = whichPort(&pin);
	activate(&port, &pin);
}

void SenseoUno::shutdownG(){
	short pin = ledG;
	short port = whichPort(&pin);
	shutdown(&port, &pin);
}

/***** LED B *****/
void SenseoUno::activateB(){
	short pin = ledB;
	short port = whichPort(&pin);
	activate(&port, &pin);
}

void SenseoUno::shutdownB(){
	short pin = ledB;
	short port = whichPort(&pin);
	shutdown(&port, &pin);
}

/***** ANALOG RGB LED *****/
void SenseoUno::analogWriteRGB(short R, short G, short B){
	// Before all, if R, G and B are 0, let's shutdown the RGB.
	if((R==0) && (G==0) && (B==0)) analogShutdownRGB();
	//First, let's reset all the compare values of the registers
	resetPWM0(); resetPWM1(); resetPWM2();	
	//Then, declare a list of 6 elements : the first 3 elements are the PWM 8-bits values, the last 3 elements are the associated pin number of the led.
	short tab[6] {R, G, B, ledR, ledG, ledB};
	for(int i = 0; i < 3; i++){
		//If the analog PWM value element is bigger than 255, reassign its value to 255.
		if(tab[i] > 255) tab[i] = 255;
		//If the analog PWM value element is lower than 0, reassign its value to 0.
		else if(tab[i] < 0) tab[i] = 0;
		//Let's write the analog PWM value to its corresponding register. To do so, we need to provide the led number.
		activatePWM((tab+(i+3)), (tab+i));
	}
}

void SenseoUno::analogShutdownRGB(){
	if(PWM0 == 1) TCCR0A &= ~(1<<COM0A1);
	else if(PWM0 == 2) TCCR0A &= ~(1<<COM0B1);
	else if(PWM0 == 3) TCCR0A &= ~((1<<COM0A1) | (1<<COM0B1));
	
	if(PWM1 == 1) TCCR1A &= ~(1<<COM1A1);
	else if(PWM1 == 2) TCCR1A &= ~(1<<COM1B1);
	else if(PWM1 == 3) TCCR1A &= ~((1<<COM1A1) | (1<<COM1B1));
	
	if(PWM2 == 1) TCCR2A &= ~(1<<COM2A1);
	else if(PWM2 == 2) TCCR2A &= ~(1<<COM2B1);
	else if(PWM2 == 3) TCCR2A &= ~((1<<COM2A1) | (1<<COM2B1));
}

/***** CHRONO WITH 1 OR 2 COUNTERS *****/
void SenseoUno::startChrono(long countdown_value){
	// Maximum one minute / 60 seconds for the chrono countdown value
	if(countdown_value > 60000) countdown_value == 60000;
	float f_time = (float)(countdown_value * 1000);
	//  2040 = [(2*255*64)*1000000]/16000000 | 255 = 8-bits, 64 = prescaler, 2 = phase-correct mode PWM, 16000000 = frequency, 1000000 to convert seconds to microseconds
	float f_res = (f_time / 2040.0);
	if(((int)(f_res+0.5)) > f_res) f_res +=1; // Line of code made to round the float value to its nearest integer value
	counter1 = (int)f_res;
	configChrono();
}

bool SenseoUno::isElapsedChrono1(volatile int *val){
	if(*val>=counter1){
		*val = 0;
		return 1;
	}
	return 0;
}

bool SenseoUno::isElapsedChrono2(volatile int *val){
	if(*val>=counter2){
		*val = 0;
		return 1;
	}
	return 0;
}

void SenseoUno::rebootChrono(volatile int *val){
	*val = 0;
}

void SenseoUno::rebootChronos(volatile int *val1, volatile int *val2){
	*val1 = 0; *val2 = 0;
}

void SenseoUno::startChrono1(long countdown_value){
	// Maximum one minute / 60 seconds for the chrono countdown value
	if(countdown_value > 60000) countdown_value == 60000;
	float f_time = (float)(countdown_value * 1000);
	//  2040 = [(2*255*64)*1000000]/16000000 | 255 = 8-bits, 64 = prescaler, 2 = phase-correct mode PWM, 16000000 = frequency, 1000000 to convert seconds to microseconds
	float f_res = (f_time / 2040.0);
	if(((int)(f_res+0.5)) > f_res) f_res +=1; // Line of code made to round the float value to its nearest integer value
	counter1 = (int)f_res;
	configChrono();
}

void SenseoUno::startChrono2(long countdown_value){
	// Maximum one minute / 60 seconds for the chrono countdown value
	if(countdown_value > 60000) countdown_value == 60000;
	float f_time = (float)(countdown_value * 1000);
	//  2040 = [(2*255*64)*1000000]/16000000 | 255 = 8-bits, 64 = prescaler, 2 = phase-correct mode PWM, 16000000 = frequency, 1000000 to convert seconds to microseconds
	float f_res = (f_time / 2040.0);
	if(((int)(f_res+0.5)) > f_res) f_res +=1; // Line of code made to round the float value to its nearest integer value
	counter2 = (int)f_res;
	configChrono();
}

void SenseoUno::stopChrono(){
	// Put a high value in counter1 and counter2 to be sure that chrono1 and chrono2 will never be higher than counter1 and counter2 before timer1 interruption is disabled
	counter1 = 30000;
	counter2 = 30000;
	TIMSK1 &= ~(1<<TOIE1);
}

/************************************************** PRIVATE FUNCTIONS **************************************************/

short SenseoUno::whichPort(short *num){
	if (*num>=2 && *num<8) return 3;
	else if(*num>=8 && *num<14){
		toRegisterB(num);
		return 1;
		}
	else if(*num>=14 && *num<=19){
		toRegisterC(num);
		return 2;
		}
	else return 0;
}

void SenseoUno::toRegisterB(short *pin){
	if(*pin == 8) (*pin) = 0;
	else if(*pin == 9) (*pin) = 1;
	else if(*pin == 10) (*pin) = 2;
	else if(*pin == 11) (*pin) = 3;
	else if(*pin == 12) (*pin) = 4;
	else (*pin) = 5;
}

void SenseoUno::toRegisterC(short *pin){
	if(*pin == 14) (*pin) = 0;
	else if(*pin == 15) (*pin) = 1;
	else if(*pin == 16) (*pin) = 2;
	else if(*pin == 17) (*pin) = 3;
	else if(*pin == 18) (*pin) = 4;
	else (*pin) = 5;
}

void SenseoUno::setOutput(short *portnum, short *pin){
	if ((*portnum) == 1) DDRB |= (1<<(*pin));
	else if ((*portnum) == 2) DDRC |= (1<<(*pin));
	else if ((*portnum) == 3) DDRD |= (1<<(*pin));
}

void SenseoUno::setInput(short *portnum, short *pin){
	if ((*portnum) == 1) DDRB &= ~(1<<(*pin));
	else if ((*portnum) == 2) DDRC &= ~(1<<(*pin));
	else if ((*portnum) == 3) DDRD &= ~(1<<(*pin));
}

bool SenseoUno::readDig(short *portnum, short *pin){
	if((*portnum) == 1){
		if(PINB & (1<<(*pin)) != 0) return 1;
		else return 0;
	}
	else if((*portnum) == 2){
		if(PINC & (1<<(*pin)) != 0) return 1;
		else return 0;
	}
	else if((*portnum) == 3){
		if(PIND & (1<<(*pin)) != 0) return 1;
		else return 0;
	}
}

void SenseoUno::activate(short *portnum, short *pin){
	if((*portnum) == 1) PORTB |= (1<<(*pin));
	else if((*portnum) == 2) PORTC |= (1<<(*pin));
	else if((*portnum) == 3) PORTD |= (1<<(*pin));
}

void SenseoUno::shutdown(short *portnum, short *pin){
	if((*portnum) == 1) PORTB &= ~(1<<(*pin));
	else if((*portnum) == 2) PORTC &= ~(1<<(*pin));
	else if((*portnum) == 3) PORTD &= ~(1<<(*pin));
}

void SenseoUno::configPWM0(short *val){
	/* 
	COM0A1 = 1 and/or COM0B1 = 1 | with COM0A0 = 0 and COM0B0 = 0, allows to clear OC2A and OC2B on compare match 
	WGM00 = 1, with WGM01 = 0 and WGM02 = 0, allows to get an 8-bit phase correct PWM
	CS00 = 1 and CS01 = 0 to select a /64 prescaler
	Note : This config sets the PWM but as OCR0A = 0 and OCR0B = 0, nothing happens.
	       However, the PWM mode is active and you can't use the PWM pins of timer 0
		   as normal digital pins. To do so, use the stopRGB() function.
	*/
	TCCR0A &= ~((1<<COM0A1) | (1<<COM0B1));
	if(*val == 1) TCCR0A |= (1<<COM0A1);
	else if(*val == 2) TCCR0A |= (1<<COM0B1);
	else if(*val == 3) TCCR0A |= (1<<COM0A1) | (1<<COM0B1);
	TCCR0A |= (1<<WGM00);
	TCCR0B |= (1<<CS00) |(1<<CS01);
	resetPWM0();
}

void SenseoUno::resetPWM0(){
	OCR0A = 0;
	OCR0B = 0;
}

void SenseoUno::configPWM1(short *val){
	/* 
	COM1A1 = 1 and/or COM1B1 = 1 | with COM1A0 = 0 and COM1B0 = 0, allows to clear OC1A and OC1B on compare match 
	WGM10 = 1, with WGM11 = 0, WGM12 = 0 and WGM13 = 0, allows to get an 8-bit phase correct PWM
	CS10 = 1 and CS11 = 1, to select a /64 prescaler
	Note : This config sets the PWM but as OCR1A = 0 and OCR1B = 0, nothing happens.
	       However, the PWM mode is active and you can't user the PWM pins of timer 1
		   as normal digital pins. To do so, use the stopRGB() function.
	*/
	TCCR1A &= ~((1<<COM1A1) | (1<<COM1B1) | (1<<COM1A0) | (1<<COM1B0));
	if(*val == 1) TCCR1A |= (1<<COM1A1);
	else if(*val == 2) TCCR1A |= (1<<COM1B1);
	else if(*val == 3) TCCR1A |= (1<<COM1A1) | (1<<COM1B1);
	TCCR1A |= (1<<WGM10);
	TCCR1B |= (1<<CS10) | (1<<CS11);
	resetPWM1();
}

void SenseoUno::resetPWM1(){
	OCR1A = 0;
	OCR1B = 0;
}

void SenseoUno::configPWM2(short *val){
	/* 
	COM2A1 = 1 and/or COM2B1 = 1 | with COM2A0 = 0 and COM2B0 = 0, allows to clear OC2A and OC2B on compare match 
	WGM20 = 1, with WGM21 = 0 and WGM22 = 0, allows to get an 8-bit phase correct PWM
	CS22 = 1 to select a /64 prescaler
	Note : This config sets the PWM but as OCR2A = 0 and OCR2B = 0, nothing happens.
	       However, the PWM mode is active and you can't user the PWM pins of timer 2
		   as normal digital pins. To do so, use the stopRGB() function.
	*/
	TCCR2A &= ~((1<<COM2A1) | (1<<COM2B1));
	if(*val == 1) TCCR2A |= (1<<COM2A1);
	else if(*val == 2) TCCR2A |= (1<<COM2B1);
	else if(*val == 3) TCCR2A |= (1<<COM2A1) | (1<<COM2B1);
	TCCR2A |= (1<<WGM20);
	TCCR2B |= (1<<CS22);
	resetPWM2();
}

void SenseoUno::resetPWM2(){
	OCR2A = 0;
	OCR2B = 0;
}

void SenseoUno::activatePWM(short *LED, short *num){
	if(*LED == 3) OCR2B = (unsigned short)*num;
	else if(*LED == 5) OCR0B = (unsigned short)*num;
	else if(*LED == 6) OCR0A = (unsigned short)*num;
	else if(*LED == 9) OCR1A = (unsigned short)*num;
	else if(*LED == 10) OCR1B = (unsigned short)*num;
	else if(*LED == 11) OCR2A = (unsigned short)*num;
}


void SenseoUno::configChrono(){
	// Disable all interrupts
	cli();
	// In the TIMSK1 register, enable the overflow interrupt
	TIMSK1 |= (1<<TOIE1);
	// Enable global interrupts
	sei();
}
