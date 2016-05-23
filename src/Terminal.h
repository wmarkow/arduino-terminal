/*
 * Terminal.h
 *
 *  Created on: 8 lut 2016
 *      Author: witek
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <HardwareSerial.h>
#include "CommandParams.h"

class Terminal {

private:
	CommandParams commandParams;
	HardwareSerial* serial;

	/* commands */

	void printTerminalReady();
	void printTerminalReadyIfNeeded();
	bool areBackgroundCommands();
	void performBackgroundCommands();
	void cancelBackgroundCommands();
public:
	Terminal(HardwareSerial* serial);
	void println(char* message);
	void loop();
	bool readString();
};

#endif /* TERMINAL_H_ */
