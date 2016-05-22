#include <Terminal.h>

Terminal terminal;

void setup() {
	Serial.begin(9600);
}

void loop() {
	terminal.loop();
}
