#include <Arduino.h>
#include <Array.h>
#include <FixedSizeArray.h>
#include <Terminal.h>
#include <UptimeCommand.h>

FixedSizeArray<AbstractCommand*, 5> commands;
Array<AbstractCommand*> *array = &commands;
UptimeCommand uptimeCommand;

Terminal terminal(&Serial, array);

void setup() {
	Serial.begin(9600);

	array->add(&uptimeCommand);
}

void loop() {
	terminal.loop();
}
