/*
 * AbstractCommand.h
 *
 *  Created on: 16 lut 2016
 *      Author: witek
 */

#ifndef TERMINAL_COMMANDS_ABSTRACTCOMMAND_H_
#define TERMINAL_COMMANDS_ABSTRACTCOMMAND_H_

#include <HardwareSerial.h>
#include "CommandParams.h"

class AbstractCommand
{
private:
	bool background;
protected:
	void setBackground(bool background);
public:
	AbstractCommand();
	bool isBackground();
	void cancelBackground();
	virtual char* getName() = 0;
	virtual void process(CommandParams *params, HardwareSerial *serial) = 0;
	virtual void processBackground(HardwareSerial *serial) = 0;
};

#endif /* TERMINAL_COMMANDS_ABSTRACTCOMMAND_H_ */
