/*
 * Terminal.h
 *
 *  Created on: 8 lut 2016
 *      Author: witek
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <Arduino.h>
#include "CommandParams.h"

class Terminal {

private:
	CommandParams commandParams;

	/* commands */

	void printTerminalReady();
	void printTerminalReadyIfNeeded();
	bool areBackgroundCommands();
	void performBackgroundCommands();
	void cancelBackgroundCommands();
public:
	void println(char* message);
	void loop();
	bool readString();
};

#endif /* TERMINAL_H_ */
