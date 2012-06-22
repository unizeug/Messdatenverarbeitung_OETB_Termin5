/**
 * \defgroup fifo FIFO-Buffer
 * 
 * This module provides functions to manage fifo-buffers
 *
 * @{
 */

/**
 * \file fifo.h
 * \author Jürgen Funck
 * \date 2010-04-08
 * \brief  functions to manage fifo-ring-buffers
 */

#ifndef FIFO_H
#define FIFO_H

#include <inttypes.h>

/// type for FIFO buffers
typedef struct fifo {
	uint8_t* data;		/// pointer to the buffer
	uint16_t iStart;	/// index of first element in the buffer
	uint16_t iEnd;		/// index of last element in the buffer
	uint16_t bytes;		/// number of bytes in the buffer
	uint16_t mask;		/// size of the buffer (must be a power of 2)
} fifo_t;

/**
 * \brief initializes a FIFO-buffer
 * \author Jürgen Funck
 * \date 2010-04-08
 * \param pFifo pointer to the FIFO-buffer structure
 * \param pdata pointer to the memory to be used
 * \param mask size of the buffer (must be a power of 2)
 */
void fifoInit(volatile fifo_t* pFifo, uint8_t* pdata, uint16_t mask);

/**
 * \brief clears a FIFO-buffer
 * \author Jürgen Funck
 * \date 2010-04-08
 * \param pFifo pointer to the FIFO-buffer structure
 */
 void fifoClear(volatile fifo_t* pFifo);

/**
 * \brief writes a byte to a FIFO-buffer
 * \author Jürgen Funck
 * \date 2010-04-08
 * \param pFifo pointer to the FIFO-buffer structure
 * \param data data to write
 * \return 0, if writing was successful, otherwise 1
 */
uint8_t fifoPushByte(volatile fifo_t* pFifo, uint8_t data);

/**
 * \brief writes a word (16 Bit) to a FIFO-buffer
 * \author Jürgen Funck
 * \date 2010-04-08
 * \param pFifo pointer to the FIFO-buffer structure
 * \param data data to write
 * \return 0, if writing was successful, otherwise 1
 */
uint8_t fifoPushWord(volatile fifo_t* pFifo, int16_t data);

/**
 * \brief reads a byte form a FIFO-buffer (byte is deletet from the buffer)
 * \author Jürgen Funck
 * \date 2010-04-08
 * \param pFifo pointer to the FIFO-buffer structure
 * \param pdata pointer to the memory where the byte read is to be stored
 * \return 0, if reading was successful, otherwise 1
 */
uint8_t fifoPopByte(volatile fifo_t* pFifo, uint8_t* pdata);

/**
 * \brief reads a word (16 Bit) form a FIFO-buffer (word is deletet from the buffer)
 * \author Jürgen Funck
 * \date 2010-04-08
 * \param pFifo pointer to the FIFO-buffer structure
 * \param pdata pointer to the memory where the word read is to be stored
 * \return 0, if reading was successful, otherwise 1
 */
uint8_t fifoPopWord(volatile fifo_t* pFifo, int16_t* pdata);

/**
 * \brief reads the n-th word from a FIFO-Buffer (word stays in the buffer)
 * \author Jürgen Funck
 * \date 2010-04-08
 * \param pFifo pointer to the FIFO-buffer structure
 * \param n the word's index in the buffer (counting from the beginning, starting at 0)
 * \param pdata pointer to the memory where the word read is to be stored
 * \return 0, if reading was successful, otherwise 1
 */
uint8_t fifoReadWord(volatile fifo_t* pFifo, uint16_t n, int16_t* pdata);

/**
 * \brief returns the number of bytes in a FIFO-buffer
 * \author Jürgen Funck
 * \date 2010-04-08
 * \param pFifo pointer to the FIFO-buffer structure
 * \return number of bytes in the buffer
 */
uint16_t fifoBytes(volatile fifo_t* pFifo);

/** @} */
#endif
