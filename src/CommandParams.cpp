/*
 * CommandParams.cpp
 *
 *  Created on: 16 lut 2016
 *      Author: witek
 */

#include "CommandParams.h"

char* CommandParams::getParam(uint8_t index)
{
	return readBuffer[index];
}

void CommandParams::reset()
{
	readRowIndex = 0;
	readColumnIndex = 0;
	endOfWordDetected = false;
	commandDetected = false;
}

uint8_t CommandParams::getNumberOfParameters()
{
	return readRowIndex + 1;
}

bool CommandParams::appendChar(char byte)
{
	if(byte == ' ' && readColumnIndex == 0)
	{
		// skip extra spaces before any words
		return false;
	}

	if(byte == '\r')
	{
		// carrier return, just ignore this character
		return true;
	}

	if(byte == '\n')
	{
		// line feed, treat this as an end-of-line
		readBuffer[readRowIndex][readColumnIndex] = 0;
		commandDetected = true;
		return true;
	}

	if(byte == ' ' && readColumnIndex > 0)
	{
		// end of word in line
		endOfWordDetected = true;
		readBuffer[readRowIndex][readColumnIndex] = 0;
		return true;
	}

	if(byte != ' ' && endOfWordDetected)
	{
		// new word detected
		endOfWordDetected = false;

		readRowIndex++;
		readColumnIndex = 0;

		if(readRowIndex >= INCOMING_BUFFER_MAX_WORDS_IN_LINE)
		{
			// incoming buffer overflow
			reset();
			return false;
		}
	}

	// a regular character of the word
	readBuffer[readRowIndex][readColumnIndex] = byte;
	readColumnIndex ++;

	if(readColumnIndex > INCOMING_BUFFER_MAX_CHARACTERS_IN_WORD)
	{
		// incoming buffer overflow
		reset();
		return false;
	}

	return true;
}

bool CommandParams::isCommandDetected()
{
	return this->commandDetected;
}
