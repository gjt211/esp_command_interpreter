# esp_command_interpreter

Simple command interpreter that was developed for an ESP8266 using the Arduino/ESP8266 core.

Allows simple commands to be received over the UART to perform actions.

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

### Notes:
No spaces are to be used before or after the space
The maximum length of the received char array, and the command and value are set in various locations in the file.
