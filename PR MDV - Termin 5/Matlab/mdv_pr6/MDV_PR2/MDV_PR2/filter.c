/**
 * \addtogroup filter
 *
 * \file filter.c
 * \author Jürgen Funck
 * \date 23-03-2010
 * \brief functions to digitally filter data
 */

#include <avr/interrupt.h>
#include "filter.h"
#include "filter_coeff.h"
#include "fifo.h"
#include <avr/delay.h>

/*** GLOBAL VARIABLES ***/
/// buffer for input values (FIFO)
volatile static fifo_t filtInBuf;
/// memory of the input-buffer
volatile static uint8_t filtInBufMem[2*(FILTER_IN_BUF_MASK)];

/// array with coefficients of a FIR-Filter
//static int16_t FIRkoeff[FILTER_ORD] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,0,0,1,2,2,2,1,0,-1,-2,-3,-3,-3,-2,0,2,4,5,5,4,2,-1,-3,-6,-7,-7,-6,-2,2,6,9,11,10,7,2,-4,-9,-14,-16,-14,-9,-2,7,14,20,21,18,11,1,-11,-21,-28,-29,-23,-12,2,18,30,38,37,29,13,-7,-27,-42,-50,-48,-35,-13,13,39,58,66,60,40,11,-24,-55,-77,-84,-73,-46,-6,38,77,102,107,89,50,-3,-58,-105,-133,-134,-106,-52,16,86,143,173,167,125,52,-38,-126,-194,-224,-209,-147,-47,71,183,265,296,265,173,35,-123,-270,-372,-402,-347,-209,-10,215,419,556,587,491,270,-47,-407,-740,-968,-1022,-848,-426,233,1077,2024,2971,3807,4430,4763,4764,4432,3809,2974,2026,1078,233,-427,-851,-1025,-971,-742,-408,-47,271,493,590,559,421,216,-10,-211,-349,-405,-374,-272,-124,36,175,267,298,267,185,71,-48,-148,-211,-227,-196,-127,-38,53,126,169,175,145,88,16,-53,-107,-136,-135,-107,-59,-3,51,90,109,104,78,39,-6,-47,-75,-86,-79,-56,-24,11,41,61,67,59,40,14,-13,-36,-49,-52,-44,-27,-7,14,30,39,39,31,18,2,-13,-24,-30,-29,-22,-11,1,11,19,22,21,15,7,-2,-10,-15,-16,-14,-10,-4,2,8,11,11,10,6,2,-2,-6,-8,-8,-6,-4,-1,2,4,5,5,4,2,0,-2,-3,-3,-3,-2,-1,0,1,2,2,2,1,0,0,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static int16_t FIRkoeff[FILTER_ORD] = {FILTER_COEFF};

decimState_t decimation;

/*** FUNCTIONS ***/
void filterInit() {
	//initialise In- and Outputbuffer
	fifoInit(&filtInBuf,  (uint8_t*)filtInBufMem,2*(FILTER_IN_BUF_MASK));
}

int16_t filterIdentity() {
	int16_t val;
	
	decimation 		  = OFF;
	while(fifoPopWord(&filtInBuf, &val));
	return val;
}

uint16_t filterFIR() {
	uint16_t i;
	int16_t accum = 0;
	int16_t val;

	// calculate output values of the filter
	for(i=0; i<FILTER_ORD; i++) {
		if(fifoReadWord(&filtInBuf, FILTER_ORD-(i+1), &val)==0) {
			val = (val << 6);
			accum += (((int32_t)FIRkoeff[i]) * val)>>16;
		}
	}
	// delete the oldest value from the buffer
	fifoPopWord(&filtInBuf, &val);

	// convert to integer values
	return (accum >> 5);	
}

uint16_t filterFIRDecim() {

	PORTC |= (1<<PC2);
	int16_t val;
	uint16_t a = filterFIR();
	fifoPopWord(&filtInBuf, &val);
    fifoPopWord(&filtInBuf, &val);
	fifoPopWord(&filtInBuf, &val);
	fifoPopWord(&filtInBuf, &val);
	PORTC &= ~(1<<PC2);
	//_delay_ms(20);
	return a;
}

inline uint8_t filterWrite2Buf(int16_t val) {
	return fifoPushWord(&filtInBuf, val);
}

inline uint16_t filterWaitingVals() {
	return fifoBytes(&filtInBuf)/2;
}

void filterReset() {
	fifoClear(&filtInBuf);
}
