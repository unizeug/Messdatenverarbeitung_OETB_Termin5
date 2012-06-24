/**
 * \file MDV_PR.c
 * \author Jürgen Funck
 * \date 2010-03-24
 * \brief the main programm
 */

#include <avr/sleep.h>
#include <util/delay.h>
#include <inttypes.h>

#include "main.h"
#include "serial.h"
#include "adc.h"
#include "command.h"
#include "filter.h"

/*** GLOBAL VARIABLES ***/
decimState_t decimation;	/// state of decimation unit

/**
 * \brief main function of the data acquisition system
 * \author Jürgen Funck
 * \date 2010-03-24
 */
int main(void) {
	cli();	// disable interrupts globally
 	
	// set clock prescaler
	CLKPR = (1<<CLKPCE);
	CLKPR = 0;
	_delay_ms(2);


	// initialisation
	DDRC |= (1<<PC2);
	progState_t state = IDLE;
	adcInit();					// adc
	filterInit();	 			// filter 
	serialInit(BAUD_115200); 	// serial port
	state = IDLE;				// state

	serialSendString("Hello World!\n");

	// set sleep-mode
	set_sleep_mode(SLEEP_MODE_IDLE);

	sei(); // enable interrupts globally

	// main-loop
	int16_t val = 0;

	while(1) {
// ACQUIRE		
		switch(state) {
			case ANA_MEAS:
				if(adcIsRunning() > 0) {
					state = ANA_MEAS;
				}
				else {
					state = FILT;
				}
				break;
// FILTER			
		        case FILT:
				if(filterWaitingVals() > FILTER_ORD) {
					if(decimation==OFF) {
						val = filterFIR();//Identity();
					}
					else {
						val = filterFIRDecim();
					}
					while(serialSendWord(val)){}
				}
				else {
					filterReset();
					state = IDLE;
				}
				break;
			case IDLE: 
			default:
// WAIT FOR COMMANDS
				// check incomming messages
				state = checkMessages();

				if(state == IDLE) {
					// sleep until the next interrupt
					sleep_enable();
					sleep_cpu();
					sleep_disable();
				}
		}

	}

	return 0;
 }
