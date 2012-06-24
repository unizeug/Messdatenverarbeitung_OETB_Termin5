/**
 * \addtogroup adc
 *
 * \file adc.c
 * \author Juergen Funck <juergen.funck@tu-berlin.de>
 * \date 2011-03-25
 * ------------------------------------------------------
 * \brief functions to access the adc
 */

#include "adc.h"
#include "filter.h"

/*** GLOBAL VARIABLES ***/
volatile static uint32_t toSample;	/// number of samples to be acquired
volatile static trigger_t trigMode; 	/// tirgger-mode
volatile static uint8_t waitingForTrig;	/// signals-whether to Programm is waiting for a trigger
volatile static int16_t trigLev;	/// trigger-Level
volatile static int16_t prevVal;	/// value acquired previously


/*** INTERRUPT ROUTINES ***/
ISR(TIMER1_COMPA_vect) {
}

ISR(TIMER1_COMPB_vect) { 
}

/**
 * \fn ISR(ADC_vect)
 * \author Juergen Funck <juergen.funck@tu-berlin.de>
 * \date 2011-03-25
 * \brief Interrupt-Routine for the ADC-Interrupt. 
 *		  Gets called when an analog-to-digital conversion is complete
 */
ISR(ADC_vect) {
	int16_t wert = ADC-ADC_OFFSET;	/// substract offset

	if(waitingForTrig==1) {         /// check for trigger condition
		switch(trigMode) {
			case RISING: 
				if((wert >= trigLev) && (prevVal < trigLev)) {
					waitingForTrig = 0;
				}
				break;
			case FALLING:
				if((wert <= trigLev) && (prevVal > trigLev)) {
					waitingForTrig = 0;
				}
				break;
			case NONE:
			default:
				waitingForTrig = 0;
		}
	}
	else {
		filterWrite2Buf((int16_t)wert);

		toSample--; // decrement the number of samples to be recorded
		if(toSample == 0) {
			TCCR1B  = 0; 			// turn timer off
			ADCSRA  &= ~(1<<ADIE);	// disable ADC-Interrupt
		}
	}
	prevVal = wert;
}

/*** FUNCTIONS ***/
void adcInit() {
	toSample = 0;

	// use internal 2,56 V reference, Input=Single_Ended, Channel=ADC0
	#if defined (__AVR_ATmega1281__)
		ADMUX   = (1<<REFS1) | (1<<REFS0); 	
	#elif defined (__AVR_ATmega2561__)
		ADMUX   = (1<<REFS1) | (1<<REFS0);
	#endif

	#if F_CPU==14745600UL
		ADCSRA  = (1<<ADATE) | (1<<ADPS2) | (1<<ADPS1);
		// turn on Auto-Trigger and ADC-Interrupt, F_ADC = F_CPU/64;
	#elif F_CPU==7372800UL
		ADCSRA  = (1<<ADATE) | (1<<ADPS2) | (1<<ADPS0);
		// turn on Auto-Trigger and ADC-Interrupt, F_ADC = F_CPU/32;
	#else
		#warning "Program not specified for this frequency. Problems may occur"
	#endif
	ADCSRB  = (1<<ADTS2) | (1<<ADTS0); 	// Conversion is triggered by Compare-Match B of Timer1
	DIDR0   = (1<<ADC0D);			  	// disable digital Buffer of ADC0
	ADCSRA |= (1<<ADEN);				// enable ADC

	// turn on Timer1 
	TCCR1B = 0;	
}

void adcStart(uint16_t sampleRateCode, uint32_t sampleCount, trigger_t triggerMode, int16_t triggerLevel) {
	cli();	// disable Interrupts globally

	// save number of samples
	toSample = sampleCount;

	// initialize trigger logic
	trigMode = triggerMode;
	trigLev  = triggerLevel;

	switch(trigMode) {
		case RISING:
			waitingForTrig = 1;
			prevVal = INT16_MAX;
			break;
		case FALLING:
			waitingForTrig = 1;
			prevVal = INT16_MIN;
			break;
		case NONE:
		default:
			waitingForTrig = 0;
			prevVal = 0;
	}

	// initialize Timer1
	OCR1A	 = sampleRateCode;
	OCR1B  	 = sampleRateCode>>2;
	TCNT1  	 = 0;
	TIMSK1   = (1<<OCIE1A) | (1<<OCIE1B); // enable Timer-Output-Compare-Interrupt
	TCCR1A   = 0; 						 
	TCCR1B   = (1<<WGM12) | (1<<CS10); 	  // disable Input/Capture, CTC-Mode, Timer-Clock = F_CPU

	// enable ADC-Interrupt
	ADCSRA  |= (1<<ADIE);

	// enable Interrupts globally
	sei();
}

uint8_t adcIsRunning() {
	uint8_t isRunning = 0;

	if(toSample > 0)
		isRunning = 1;
	else
		isRunning = 0;

	return isRunning;
}
