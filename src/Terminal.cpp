/*
 * Terminal.cpp
 *
 *  Created on: 8 lut 2016
 *      Author: witek
 */
#include "Terminal.h"

#include <string.h>

Terminal::Terminal(HardwareSerial* serial, Array<AbstractCommand>* commands)
{
	this->serial = serial;
	this->commands = commands;
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
	if(strcmp_P(command, (char*)F("break")) == 0)
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

	if(strcmp_P(command, (char*)F("")) == 0)
	{
		commandParams.reset();
		printTerminalReadyIfNeeded();
		return;
	}

	if(strcmp_P(command, (char*)F("help")) == 0)
	{
		processHelp();

		commandParams.reset();
		printTerminalReadyIfNeeded();
		return;
	}

	AbstractCommand* commandToExecute = getCommandByName(command);
	if(commandToExecute != 0)
	{
		commandToExecute->process(&commandParams, this->serial);
		commandParams.reset();

		printTerminalReadyIfNeeded();
		return;
	}

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

AbstractCommand* Terminal::getCommandByName(char* commandName)
{
	for(uint8_t q = 0 ; q < commands->getSize() ; q ++)
	{
		AbstractCommand* command = commands->get(q);
		if(strcmp(command->getName(), commandName) == 0)
		{
			return command;
		}
	}

	return 0;
}

void Terminal::processHelp()
{
	if(commands->getSize() == 0)
	{
		serial->println(F("No commands available."));
		return;
	}

	for(uint8_t q = 0 ; q < commands->getSize() ; q ++)
	{
		AbstractCommand* command = commands->get(q);
		serial->println(command->getName());
	}
}
