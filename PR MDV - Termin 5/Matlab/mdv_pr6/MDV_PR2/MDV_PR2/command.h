/**
 * \defgroup command Command Interpreter
 * 
 * This module provides a very simple command interpreter
 * for the serial interface
 *
 * @{
 */

/**
 * \file command.h
 * \author Jürgen Funck
 * \date 23.03.2010
 * \brief a very simple command interpreter
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "main.h"

/// maximum number of characters in one command line
#define MAX_COMMAND_LINE_LENGTH 32

/**
 * \brief checks whether commands have been received and if so executes him
 * \author Jürgen Funck
 * \date 2010-03-23
 * \return next state of the program
 */
 progState_t checkMessages();

/** @} */
#endif
