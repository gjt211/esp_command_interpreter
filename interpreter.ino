#include <EEPROM.h>


const byte numChars = 48;       // Max qty of bytes we can receive
char receivedChars[numChars];   // an array to store the received data
boolean newData = false;



struct config_t {
  float float1 = 1.0;
  char char1[32] = "";
  unsigned long integer1 = 300;    // 5 minutes
} configuration;

//##############################################################
void setup() {
  Serial.begin(115200);
  Serial.print(F("\n\n***\r\n\r\n"));
  Serial.println(ESP.getResetReason());
  Serial.print(F("\n\n***\n\n"));

  Serial.print(F("Read EEPROM..."));
  EEPROM.begin(512);    //Allocate 512 bytes for EEPROM storage
  //Check if the configuration has been stored in EEPROM
  byte e1 = EEPROM.read(0);
  byte e2 = EEPROM.read(1);
  if ((e1 != 214) && (e2 != 26)){
    Serial.println(F("Not configured!"));
    EEPROM.write(0,214);
    EEPROM.write(1,26);
    EEPROM.commit();
    Serial.print(F("Write defaults.."));
    store_config();
    } else {
    EEPROM.get(2,configuration);
    Serial.println(F("Done."));
    }
}

//##############################################################
void loop() {
  recvWithEndMarker();    // Check for serial RX data
  HaveNewData();          // Process any received serial data
  delay(1);
  
}




//==============================================================
void store_config(){
  Serial.print(F("Writing config..."));
  EEPROM.put(2,configuration);
  EEPROM.commit();
  Serial.println(F("Done."));
  yield();
}
// =============================================================
// Received command must be terminated with a carriage return
void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\r';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}
void HaveNewData() {
    if (newData == true) {
        Serial.print("CMD-> ");
        Serial.println(receivedChars);
        newData = false;
        command_interperter(receivedChars);
    }
}


//================================================================
void command_interperter(char* payload){
  // ---------------------------------

  if (strcmp(payload, "help") == 0)
  {
    print_help();
    return;
  }
  if (strcmp(payload, "reset") == 0)
  {
    reset_config();
    return;
  }

  // None of the above commands were received, so parse the string for
  // a command/value
  //Micro command parser
  char v[12];     // The maximum number of characters for a command
  char k[12];     // The maximum number of characters for the value
  
  char *sp = strchr(payload, 61);   //61 is INT value of =
  if (sp != NULL)
  {
    strcpy(v, sp + 1);
    *sp = '\0';
    strcpy(k, payload);
    // ---------------------------------
    if (strcmp(k, "float1") == 0)
    {
      configuration.float1 = atof(v);
      Serial.print(F("float1 = "));
      Serial.println(configuration.float1, 6);
      store_config();
      return;
    }
    // ---------------------------------
    if (strcmp(k, "integer1") == 0)
    {
      configuration.integer1 = atol(v);
      Serial.print(F("integer1 = "));
      Serial.println(configuration.integer1);
      store_config();
      return;
    }
    // ---------------------------------
    if (strcmp(k, "char1") == 0)
    {
      strcpy( configuration.char1, v );
      Serial.print(F("char11 = "));
      Serial.println(configuration.char1);
      store_config();
      return;
    }
    // ---------------------------------
  }
  Serial.println(F("[OS] Syntax error!"));

}
// =============================================================
void reset_config(void){
  Serial.print("Reset config: ");
  configuration.float1 = 1.0;
  configuration.integer1 = 0;
  strcpy( configuration.char1, "" );
  store_config();
}


// =============================================================
void print_help(){
  Serial.println(F("################"));
  Serial.println(F("Help"));
  Serial.println(F("----------------"));
  Serial.println(F("Available commands..."));
  Serial.println(F("help"));
  Serial.println(F("float1=<value>"));
  Serial.println(F("integer1=<value>"));
  Serial.println(F("char1=<value>"));
  Serial.println(F("----------------"));
  Serial.println(F("Current settings"));
  Serial.print("float1: ");
  Serial.println(configuration.float1, 6);
  Serial.print("integer1: ");
  Serial.println(configuration.integer1);
  Serial.print("char1: ");
  Serial.println(configuration.char1);
  Serial.println();
  Serial.println(F("Note: Commands have NO spaces"));
  Serial.println(F("Example"));
  Serial.println(F("float1=10.235"));
  Serial.println();

}
