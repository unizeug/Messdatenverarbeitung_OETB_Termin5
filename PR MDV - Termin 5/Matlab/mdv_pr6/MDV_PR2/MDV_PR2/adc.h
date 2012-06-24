/**
 * \defgroup adc Analog to Digital Conversion
 * 
 * This module provides functions to access the 
 * internal adc and to acquire analog data
 *
 * @{
 */

/**
 * \file adc.h
 * \author Jürgen Funck
 * \date 2010-03-13
 * \brief functions to access the adc
 */

#ifndef ADC_H
#define ADC_H

#include <inttypes.h>
#include <avr/interrupt.h>

/// ADC-Offset
#define ADC_OFFSET	512

/// type to store the trigger-mode
typedef enum trigger {NONE=0, RISING=1, FALLING=2} trigger_t;

/**
 * \brief initializes the ADC
 * \author your_name
 * \date day_of_implementation
 */
void adcInit();

/**
 * \brief initializes the adc
 * \author your_name
 * \date day_of_implementation
 * \param sampleRateCode compare match value that determines the sample rate
 *        SAMPLE_RATE = F_CPU / (RATE_CODE + 1)
 * \param sampleCount number of sample to be acquired
 * \param triggerMode trigger mode:
 *						NONE - trigger is disabled
 *						RISING - trigger at rising edge
 * 						FALLING - trigger at falling edge
 * \param triggerLevel trigger level in quantization steps (-512...511) 
 */
void adcStart(uint16_t sampleRateCode, uint32_t sampleCount, trigger_t triggerMode, int16_t triggerLevel);

/**
 * \brief signifies whether the ADC is currently acquiring data
 * \author your_name
 * \date day_of_implementation
 * \return > 0 if the ADC is acquiring data, 0 otherwise
 */
uint8_t adcIsRunning();

/** @} */
#endif
