/*
 * AbstractCommand.cpp
 *
 *  Created on: 18 lut 2016
 *      Author: witek
 */

#include "AbstractCommand.h"

AbstractCommand::AbstractCommand()
{
	this->background = false;
}

bool AbstractCommand::isBackground()
{
	return background;
}

void AbstractCommand::cancelBackground()
{
	setBackground(false);
}

void AbstractCommand::setBackground(bool background)
{
	this->background = background;
}
