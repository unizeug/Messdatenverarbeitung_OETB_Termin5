/**
 * \defgroup serial Serial Port Communication
 * 
 * This module provides functions for accessing the serial port 
 * 
 * @{
 */

/**
 * \file serial.h
 * \author Jürgen Funck
 * \date 24.02.2010
 * \brief functions to access the serial port
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <inttypes.h>

/// UBRR-value for 9600baud
#define BAUD_9600	((uint16_t)(F_CPU/(16*9600L))  -1)
/// UBRR-value for 19200baud 
#define BAUD_19200	((uint16_t)(F_CPU/(16*9600L))  -1) 
/// UBRR-value for 56700baud
#define BAUD_56700	((uint16_t)(F_CPU/(16*56700L)) -1)
/// UBRR-value for 115200baud 
#define BAUD_115200	((uint16_t)(F_CPU/(16*115200L))-1)
/// UBRR-value for 230400baud 
#define BAUD_230400 ((uint16_t)(F_CPU/(16*230400L))-1) 

/// size [bytes] of the send-buffer as power to 2, size = 2^TX_BUFFER_POW
#define TX_BUFFER_POW 	6
/// size of the send-buffer in bytes 					
#define TX_BUFFER_MASK (1<<TX_BUFFER_POW)
/// size [bytes] of the receive-buffer as power to 2, size = 2^RX_BUFFER_POW
#define RX_BUFFER_POW 	6
/// size of the send-buffer in bytes 
#define RX_BUFFER_MASK (1<<RX_BUFFER_POW)

// Device dependent definitions
#if defined (__AVR_ATmega1281__)
	// Register
	#define UDR 	UDR1
	#define UCSRB 	UCSR1B
	#define UCSRC 	UCSR1C
	#define UCSRC	UCSR1C
	#define UBRR 	UBRR1
	// Bits
	#define RXCIE	RXCIE1
	#define RXEN	RXEN1
	#define TXEN	TXEN1
	#define	UDRIE	UDRIE1
	// Interrupt_vectors
	#define UDRE_vect 	USART1_UDRE_vect
	#define RX_vect 	USART1_RX_vect
#elif defined (__AVR_ATmega2561__)
	// Register
	#define UDR 	UDR1
	#define UCSRB 	UCSR1B
	#define UCSRC 	UCSR1C
	#define UCSRC	UCSR1C
	#define UBRR 	UBRR1
	// Bits
	#define RXCIE	RXCIE1
	#define RXEN	RXEN1
	#define TXEN	TXEN1
	#define	UDRIE	UDRIE1
	// Interrupt_vectors
	#define UDRE_vect 	USART1_UDRE_vect
	#define RX_vect 	USART1_RX_vect
#elif defined (__AVR_ATmega1284P__)
	// Register
	#define UDR 	UDR1
	#define UCSRB 	UCSR1B
	#define UCSRC 	UCSR1C
	#define UCSRC	UCSR1C
	#define UBRR 	UBRR1
	// Bits
	#define RXCIE	RXCIE1
	#define RXEN	RXEN1
	#define TXEN	TXEN1
	#define	UDRIE	UDRIE1
	// Interrupt_vectors
	#define UDRE_vect 	USART1_UDRE_vect
	#define RX_vect 	USART1_RX_vect
#else
	#if !defined(__COMPILING_AVR_LIBC__)
		#warning "Program not specified for this cpu. Problems may occur"
	#endif
#endif

/**
 * \brief initialises the serial port
 * \author Jürgen Funck
 * \date 2010-03-12
 * \param baudrate - baudrate to be used
 */
void serialInit(uint16_t baudrate);

/**
 * \brief writes a byte (8 Bit) the send-buffer
 * \author Jürgen Funck
 * \date 2010-03-15
 * \param b byte to be written
 * \return 0 if writing was successful, owtherwise >0
 */
uint8_t serialSendByte(uint8_t b);

/**
 * \brief writes a word (16 Bit) to the send-buffer
 * \author Jürgen Funck
 * \date 2010-03-15
 * \param w word to be written
 * \return 0 if writing was successful, otherwise > 0
 */
uint8_t serialSendWord(int16_t w);

/**
 * \brief writes a schreibt einen null-terminated string to the send-buffer
 * \author Jürgen Funck
 * \date 2010-03-15
 * \param str pointer to the string to write
 */
void serialSendString(const char* str);

/**
 * \brief returns the number of bytes in the receive buffer
 * \author Jürgen Funck
 * \date 2010-03-17
 * \return number of bytes in buffer
 */
 int bytesInRcvBuf();

/**
 * \brief returns the first byte from the receive buffer. Blocks if no data is in the buffer.
 * \author Jürgen Funck
 * \date 2010-03-17
 * \return first byte from the receive buffer
 */
uint8_t serialReadByte();

/**
 * \brief reads a line of the maximum length 'length' from the receive buffer
 * \author Jürgen Funck
 * \date 2010-03-17
 * \param str pointer to the memory where the string is to be written
 * \param length maximum number of characters to be read
 * \return 0, of reading is successful, 1 otherwise
 */
uint8_t serialReadLine(char* str, uint16_t length);

/**
 * \brief returns the number of lines in the receive buffer
 * \author Jürgen Funck
 * \date 2010-03-17
 * \return number of lines in the receive buffer
 */
uint16_t serialNewLines();

/** @} */
#endif
