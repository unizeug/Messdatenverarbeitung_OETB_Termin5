/**
 * \file MDV_PR.c
 * \author Jürgen Funck
 * \date 2011-04-08
 * \brief zentrale Definitionen für das Programm
 */

#ifndef MAIN_H
#define MAIN_H

/// Definition CPU_Frequency in Hz
// #define F_CPU 7372800
// #define F_CPU 14745600

/// enumeration type for the program state
typedef enum {IDLE, ANA_MEAS, FILT} progState_t;

#endif
