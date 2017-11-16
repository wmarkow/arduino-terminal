/*
 * Terminal.h
 *
 *  Created on: 8 lut 2016
 *      Author: witek
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <HardwareSerial.h>
#include <Array.h>
#include "CommandParams.h"
#include "AbstractCommand.h"

class Terminal {

private:
	CommandParams commandParams;
	HardwareSerial* serial;

	/* commands */
	Array<AbstractCommand*> *commands;
	AbstractCommand* backgroundCommand = 0;

	void printTerminalReady();
	void printTerminalReadyIfNeeded();
	bool areBackgroundCommands();
	void performBackgroundCommands();
	void cancelBackgroundCommands();
	AbstractCommand* getCommandByName(char* name);
	void processHelp();
public:
	Terminal(HardwareSerial* serial, Array<AbstractCommand*> *commands);
	void println(char* message);
	void loop();
	bool readString();
};

#endif /* TERMINAL_H_ */
