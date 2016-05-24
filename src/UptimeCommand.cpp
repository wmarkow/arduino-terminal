/*
 * UptimeCommand.cpp
 *
 *  Created on: 24 maj 2016
 *      Author: witek
 */

#include "UptimeCommand.h"

const __FlashStringHelper* UptimeCommand::getName()
{
	return F("uptime");
}

void UptimeCommand::process(CommandParams *params, HardwareSerial *serial)
{
	unsigned long uptimeInMillis = millis();
	serial->print(uptimeInMillis);
	serial->println(F(" ms up"));
}

void UptimeCommand::processBackground(HardwareSerial *serial)
{

}

