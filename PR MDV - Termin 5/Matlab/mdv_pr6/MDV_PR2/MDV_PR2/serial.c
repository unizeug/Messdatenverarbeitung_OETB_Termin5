/**
 * \addtogroup serial
 * 
 * \file serial.c
 * \author Jürgen Funck
 * \date 2010-03-13
 * \brief functions to access the serial port
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#include "serial.h"
#include "fifo.h"

/*** GLOBAL VARIABLES ***/

/// send-buffer (FIFO)
volatile static fifo_t txBuf;
/// memory of the send buffer
volatile static uint8_t txBufMem[TX_BUFFER_MASK]; 	


/// receive-buffer (FIFO)
volatile static fifo_t rxBuf;
/// memory of the receive buffer
volatile static uint8_t rxBufMem[RX_BUFFER_MASK];	
/// number of complete lines (i.e. terminated with '\n') in the receive-buffer
volatile static uint16_t lines;

/*** INTERRUPT-ROUTINES ***/

/**
 * \fn ISR(UDRE_vect)
 * \author Jürgen Funck
 * \date 2010-03-13
 * \brief interrupt-routine for the Usart-Data-Register-Empty-Interrupt.
 *		  is called when a byte has been send
 */
ISR(UDRE_vect) {
	uint8_t byte;

	if(fifoPopByte(&txBuf, &byte) == 0) {// if data is in the send-buffer
		UDR = byte;					  // send byte
	}
	else {
		UCSRB &= ~(1<<UDRIE);		// disable Data-Register-Empty-Interrupt
	}	
}

/**
 * \fn ISR(RX_vect)
 * \author Jürgen Funck
 * \date 2010-03-13
 * \brief interrupt-routine for the Usart-Receive-Complete-Interrupt.
 *		  is called when a byte has been send
 */
ISR(RX_vect) {
	uint8_t byte = UDR;

	if(byte == '\n'){
		lines++;
	}

	fifoPushByte((fifo_t*)&rxBuf, byte);
}

/*** FUNCTIONS ***/

void serialInit(uint16_t baudrate) {
	lines = 0;

	// initialise send- and receive buffer
	fifoInit(&txBuf, (uint8_t*)txBufMem, TX_BUFFER_MASK);
	fifoInit(&rxBuf, (uint8_t*)rxBufMem, RX_BUFFER_MASK);
	
	// initialise usart
	UCSRB = (1<<RXCIE)| (1<<RXEN) | (1<<TXEN); 	// enable send/receive
	UCSRC = (0x03<<1); 							// asynchronous mode, no Parity, 8 DataBits, 1 Stop-Bit, no Parity
	UBRR  = baudrate;
}

uint8_t serialSendByte(uint8_t b) {
	uint8_t retCode = fifoPushByte((fifo_t*)&txBuf, b);

	if(retCode == 0) {
		UCSRB |= (1<<UDRIE);		// enable Data-Register-Empty-Interrupt
	}

	return retCode;
}

uint8_t serialSendWord(int16_t w) {
	uint8_t retCode = fifoPushWord(&txBuf, w);

	if(retCode == 0) {
		UCSRB |= (1<<UDRIE);		// enable Data-Register-Empty-Interrupt
	}

	return retCode;
}

void serialSendString(const char* str) {
	uint16_t i=0;
	
	while(str[i] != '\0') {	// send string character by character
		serialSendByte((uint8_t)str[i]);	// send character
		i++;								// next character
	}
}

int bytesInRcvBuf() {
	return fifoBytes((fifo_t*)&rxBuf);
}

uint8_t serialReadByte() {
	uint8_t byte;
	while(fifoPopByte(&rxBuf, &byte)){}
	
	return byte;
}

uint8_t serialReadLine(char* str, uint16_t length) {
	uint8_t retCode = 0;

	if(lines > 0) {
		for(uint16_t i=0; i<length; i++) {
			char c = (char)serialReadByte();
			str[i] = c;
			if(c == '\n') {
				str[i+1] = '\0';
				lines--;
				break;
			}
		}
		retCode = 0;
	}
	else {
		retCode = 1;
	}

	return retCode;
}

uint16_t serialNewLines() {
	return lines;
}
