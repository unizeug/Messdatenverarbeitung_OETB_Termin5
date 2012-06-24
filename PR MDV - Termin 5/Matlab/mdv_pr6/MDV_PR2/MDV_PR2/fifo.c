/**
 * \addtogroup fifo
 * 
 * \file fifo.c
 * \author Jürgen Funck
 * \date 2010-04-08
 * \brief functions to manage fifo-ring-buffers
 */

#include "fifo.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

/*** FUNCTIONS ***/

void fifoInit(volatile fifo_t* pFifo, uint8_t* pdata, uint16_t mask) {

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		pFifo->data		= pdata;
		pFifo->iStart	= 0;
		pFifo->iEnd		= 0;
		pFifo->bytes	= 0;
		pFifo->mask		= mask;
	}
}

void fifoClear(volatile fifo_t* pFifo) {

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		pFifo->iStart	= 0;
		pFifo->iEnd		= 0;
		pFifo->bytes	= 0;
	}
}

uint8_t fifoPushByte(volatile fifo_t* pFifo, uint8_t data) {
	uint8_t retCode = 0;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if(pFifo->bytes < pFifo->mask) {
			pFifo->data[pFifo->iEnd] = data;					// write data to buffer
			pFifo->iEnd = (pFifo->iEnd+1) & (pFifo->mask-1);	// increment buffer-end-index
			pFifo->bytes++; 									// increment number of bytes in buffer
			retCode = 0;
		}
		else {
			retCode = 1;
		}
	}

	return retCode;
}

uint8_t fifoPushWord(volatile fifo_t* pFifo, int16_t data) {
	uint8_t retCode = 0;
	uint8_t* pdata = (uint8_t*)&data;
	int i;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if(pFifo->bytes < (pFifo->mask-1)) {
			for(i=0; i<2; i++) {
				pFifo->data[pFifo->iEnd] = *pdata;					// write data to buffer
				pFifo->iEnd = (pFifo->iEnd+1) & (pFifo->mask-1);	// increment buffer end index
				pdata++;
			} 
			pFifo->bytes += 2;	// increment number of bytes in buffer
			retCode = 0;
		}
		else {
			retCode = 1;
		}
	}

	return retCode;
}

uint8_t fifoPopByte(volatile fifo_t* pFifo, uint8_t* pdata) {
	uint8_t retCode = 0;
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if(pFifo->bytes>0) {
			*pdata = pFifo->data[pFifo->iStart];					// read data from buffer
			pFifo->iStart = (pFifo->iStart+1) & (pFifo->mask-1);	// increment buffer start index
			pFifo->bytes--;											// decrement number of bytes in buffer
			retCode = 0;
		}
		else {
			retCode = 1;
		}
	}
	
	return retCode;
}

uint8_t fifoPopWord(volatile fifo_t* pFifo, int16_t* pdata) {
	uint8_t retCode = 0;
	uint8_t*  pd = (uint8_t*)pdata;
	int i;
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if(pFifo->bytes>1) {
			for(i=0; i<2; i++) {
				*pd = pFifo->data[pFifo->iStart];						// read data from buffer
				pFifo->iStart = (pFifo->iStart+1) & (pFifo->mask-1);	// increment buffer start index
				pd++;
			}
			pFifo->bytes -= 2;											// decrement number of bytes in buffer
			retCode = 0;
		}
		else {
			retCode = 1;
		}
	}

	return retCode;
}

uint8_t fifoReadWord(volatile fifo_t* pFifo, uint16_t n, int16_t* pdata) {
	uint8_t retCode = 0;
	uint8_t*  pd	= (uint8_t*)pdata;
	int i;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if(pFifo->bytes < (2*n)) {	// if no n elements are in the buffer
			retCode = 1;
		}
		else {
			for(i=0; i<2; i++) {
				*pd = pFifo->data[(pFifo->iStart+2*n+i) & (pFifo->mask-1)];	// read data
				pd++;
			}
			retCode = 0;
		}
	}

	return retCode;
}

uint16_t fifoBytes(volatile fifo_t* pFifo) {
	uint16_t val = 0;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		val = pFifo->bytes;
	}
	return val;
}
