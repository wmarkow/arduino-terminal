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
	lastProcessTime = millis();
	serial->print(lastProcessTime);
	serial->println(F(" ms up"));

	if(params->getNumberOfParameters() == 2)
	{
		if(strcmp_P(params->getParam(1), (char*)F("-f")) == 0)
		{
			this->setBackground(true);
		}
	}
}

void UptimeCommand::processBackground(HardwareSerial *serial)
{
	unsigned long currentMillis = millis();
	if(currentMillis < lastProcessTime + 1000L)
	{
		return;
	}

	lastProcessTime = currentMillis;
	serial->print(lastProcessTime);
	serial->println(F(" ms up"));
}

