# esp_command_interpreter

Simple command interpreter that was developed for an ESP8266 using the Arduino/ESP8266 core.

Allows simple commands to be received over the UART to perform actions, and allows various configuration settings to be stored permanantly in eeprom.

Currently, there are 5 commands available.
1. help
2. reset
3. float1=
4. integer1=
5. char1=


```help```
 just prints the command list and the current stored values for 3,4, & 5.

```reset```
 sets the values stored for 3, 4, & 5 to default values.

```float1=```
Enter the command as;
float1=1.23456
 will store 1.23456 into the variable `configuration.float1`

```integer1=```
Enter the command as;
integer1=998877
 will store 998877 into the variable `configuration.integer1`

```char1=```
Enter the command as;
char1=MyCharArrayHere
This will store MyCharArray into the variable `configuration.char1`

### EEPROM storage

The settings are retained in EEPROM. The first two bytes of the eeprom are tested on power up to see if they match two specific values. If they don't match, the default values are written to the eeprom and the two bytes are set to match.
This allows a freshly programmed device to automatically write default values for your configuration.
The reason two bytes are tested, is that it's unlikely (but not impossible) that these will match on a new ESP8266. Also worth noting is that the eeprom values will survive a ESP8266 reprogram (if you upload a new sketch these values will still be in the eeprom).

### Notes:
No spaces are to be used before or after the space.
The maximum length of the received char array, and the command and value are set in various locations in the file.
