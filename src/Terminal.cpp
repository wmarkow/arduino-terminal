/*
 * Terminal.cpp
 *
 *  Created on: 8 lut 2016
 *      Author: witek
 */
#include "Terminal.h"

#include <string.h>

Terminal::Terminal(HardwareSerial* serial)
{
	this->serial = serial;
}

void Terminal::println(char* message) {
	serial->println(message);
}

void Terminal::loop() {
	performBackgroundCommands();

	// check for incoming commands
	if(!readString())
	{
		return;
	}

	char* command = commandParams.getParam(0);
	if(strcmp(command, (char*)F("break")) == 0)
	{
		cancelBackgroundCommands();

		commandParams.reset();
		printTerminalReadyIfNeeded();

		return;
	}

	if(areBackgroundCommands())
	{
		commandParams.reset();
		serial->println(F("terminal busy"));

		return;
	}

	if(strcmp(command, (char*)F("")) == 0)
	{
		commandParams.reset();
		printTerminalReadyIfNeeded();
		return;
	}
/*
	if(command.equals(F("ifconfig")))
	{
		ifconfig.process(&commandParams);

		commandParams.reset();
		printTerminalReadyIfNeeded();
		return;
	}
	if(command.equals(F("ping")))
	{
		ping.process(&commandParams);
		commandParams.reset();
		printTerminalReadyIfNeeded();

		return;
	}
	if(command.equals(F("flooder")))
	{
		flooderCmd.process(&commandParams);

		commandParams.reset();
		printTerminalReadyIfNeeded();
		return;
	}
*/
	serial->print(command);
	serial->println(F(": unknown command"));

	commandParams.reset();
	printTerminalReady();
}

bool Terminal::readString()
{
	while(serial->available())
	{
		char byte = serial->read();

		if(!commandParams.appendChar(byte))
		{
			// some kind of error while apending char
			serial->flush();
			serial->println();
			serial->println(F("error: terminal buffer overflow"));
			serial->flush();
		}
	}

	return commandParams.isCommandDetected();
}

void Terminal::printTerminalReady()
{
	serial->print(F("arduino$"));
}

void Terminal::printTerminalReadyIfNeeded()
{
	if(areBackgroundCommands())
	{
		return;
	}

	printTerminalReady();
}

bool Terminal::areBackgroundCommands()
{
	/*
	if(ping.isBackground())
	{
		return true;
	}
*/
	return false;
}

void Terminal::performBackgroundCommands()
{
	//ping.loopBackgroundIfNeeded();
}

void Terminal::cancelBackgroundCommands()
{
	//ping.cancelBackground();
}
