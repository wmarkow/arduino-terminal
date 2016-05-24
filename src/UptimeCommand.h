/*
 * UptimeCommand.h
 *
 *  Created on: 24 maj 2016
 *      Author: witek
 */

#ifndef UPTIMECOMMAND_H_
#define UPTIMECOMMAND_H_

#include <Arduino.h>
#include "AbstractCommand.h"

class UptimeCommand : public AbstractCommand
{
public:
	const __FlashStringHelper* getName();
	void process(CommandParams *params, HardwareSerial *serial);
	void processBackground(HardwareSerial *serial);
};

#endif /* UPTIMECOMMAND_H_ */
