/**
 * \addtogroup command
 *
 * \file command.c
 * \author Jürgen Funck
 * \date 2010-03-23
 * ------------------------------------------------------
 * \brief a very simple command interpreter
 */

#include <string.h>
#include <stdlib.h>

#include "command.h"
#include "serial.h"
#include "adc.h"
#include "filter.h"

progState_t checkMessages() {
	progState_t newState = IDLE;
	char msg[MAX_COMMAND_LINE_LENGTH+1];

	if(serialReadLine(msg,MAX_COMMAND_LINE_LENGTH) == 0) {

		if(strncmp("ANA",msg,3)==0) {
			// parse parameters
			char* p_param = strtok(msg," ");
			uint16_t sRate      = 0;
			uint32_t sCount     = 0;
			trigger_t tMode     = NONE;
			int16_t tLevel      = 0;

			p_param = strtok(NULL," ");
			if(p_param != NULL) {
				sRate = atoi(p_param);
			}

			p_param = strtok(NULL," ");
			if(p_param != NULL) {
				sCount = atol(p_param);
			}

			p_param = strtok(NULL," ");
			if(p_param != NULL) {
				tMode = atoi(p_param);
			}

			p_param = strtok(NULL," ");
			if(p_param != NULL) {
				tLevel = atoi(p_param);
			}
			p_param = strtok(NULL," ");
			if(p_param != NULL) {
				decimation = atoi(p_param);
			}

			if((sRate != 0) && (sCount != 0)) {
				if(decimation==ON) {
					adcStart(sRate,DEC_RATIO*sCount+FILTER_ORD,tMode,tLevel);
				}
				else {
					adcStart(sRate,sCount+FILTER_ORD,tMode,tLevel);
				}
				newState = ANA_MEAS;
			}
			else {
				serialSendString("invalid parameters");
				serialSendByte('\'');
				serialSendString(msg);
				serialSendByte('\'');
				newState = IDLE;
			}
		}
		else {
			serialSendString("unknown command");
			serialSendByte('\'');
			serialSendString(msg);
			serialSendByte('\'');	
			newState = IDLE;
		}
	}	

	return newState;
}
