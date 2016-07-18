# arduino-terminal
Connect to Arduino from your favourit terminal application and start talking to your embedded application. It has a lot of limitations but it is good enough for a good start.

Follow the below instructions to see how it works:
* upload your Arduino with an **examples/Terminal/Terminal.ino** sketch
* connect to Arduino with your terminal application (minicom or Arduino IDE Serial Port Monitor or whatever)
  * set the following serial communication parameters: 9600 bps, 8N1
  * enable local echo in your terminal application
  * enable adding CR character at the end of every line sent from terminal application 
* after hiting the **enter** on the keyboard arduino will display a default command prompt **arduino$**
* type **help** and hit enter to get list of available commands (only **uptime** command is available by default)
* type **uptime** and hit enter to see your Arduino's uptime time in milliseconds
* type **uptime -f** and hit enter to print your Arduino's uptime every second
  * notice that the terminal seems to be locked when uptime command is executed
  * while terminal is locked only current command is being executed
  * to cancel current command type **break** in the terminal (while uptime result is still being printed to your terminal) and hit enter
* type **asd** wich is an unknown command to the terminal: Arduino will display an **asd: unknown command** warning message

Arduino terminal library is easily to extend. You can implement your own commands just take a look at:
* **src/UptimeCommand.h** which give the the clue how the command is declared
* **src/UptimeCommand.cpp** which give the the clue how the command is implemented
* **examples/Terminal/Terminal.ino**  which give the clue how tu construct a terminal class and how to hook the command to it

Remark: this library depends on the [arduino-array](https://github.com/wmarkow/arduino-array) library.



