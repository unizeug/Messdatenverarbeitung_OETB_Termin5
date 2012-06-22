/**
 * \defgroup filter Digital Filtering
 * 
 * This module provides functions to digitally filter data
 * 
 * @{
 */

/**
 * \file filter.h
 * \author Jürgen Funck
 * \date 2010-03-23
 * \brief digital filter functions
 */

#ifndef FILTER_H
#define FILTER_H

#include <inttypes.h>

/// size (number of 16Bit values) of the input-buffer as a power to 2
#if defined (__AVR_ATmega1281__)
	#define FILTER_IN_BUF_POW	11
#elif defined (__AVR_ATmega2561__)
	#define FILTER_IN_BUF_POW	11
#elif defined (__AVR_ATmega1284P__)
	#define FILTER_IN_BUF_POW	12
#else
	#if !defined(__COMPILING_AVR_LIBC__)
		#warning "Program not specified for this cpu. Problems may occur"
	#endif
	#define FILTER_IN_BUF_POW	11
#endif

/// size (number of 16Bit values) of input-buffer in bytes
#define FILTER_IN_BUF_MASK (1<<FILTER_IN_BUF_POW)
/// order of the digital filter
#define FILTER_ORD 333
/// decimation Ratio (1 for DEC_RATIO)
#define DEC_RATIO 5
/// enumeration type for the decimation steering
typedef enum {ON=1, OFF=0} decimState_t;
/// switch to turn decimation on or off
extern decimState_t decimation;


/**
 * \brief initialises the digital filter
 * \author Jürgen Funck
 * \date 2010-03-23
 */
 void filterInit();

/**
 * \brief a simple filter that routes the input directly to the output
 * \author Jürgen Funck
 * \date 2010-03-23
 * \return n-th fitlered value
 */
 int16_t filterIdentity();

/**
 * \brief filters values using a FIR-filter
 * \author Jürgen Funck
 * \date 2010-03-23
 * \return n-th filtered value
 */
uint16_t filterFIR();

/**
 * \brief filters values using a FIR-filter and decimates them (1 from 5)
 * \author Ihr_Name
 * \date Tag_der_Bearbeitung
 * \return n-th filtered value
 */
uint16_t filterFIRDecim();

/**
 * \brief writes a value into the input buffer
 * \author Jürgen Funck
 * \date 2010-03-23
 * \param val value to be written
 */
 uint8_t filterWrite2Buf(int16_t val);

/**
 * \brief returns the number of values that still need to be processed
 * \author Jürgen Funck
 * \date 2010-03-23
 * \return number of values waiting to be processed
 */
 uint16_t filterWaitingVals();

/**
 * \brief resets the filter by clearing its input buffer
 * \author Jürgen Funck
 * \date 2011-05-19
 */
 void filterReset();

/** @} */
#endif
