

const byte numChars = 48;       // Max qty of bytes we can receive
char receivedChars[numChars];   // an array to store the received data
boolean newData = false;



struct config_t {
  char fingerprint[64] = "";
  char shost[64] = "";
  char sport[6] = "";
  float tc1slope = 1.0;
  float tc1offset = 0.0;
  float tc2slope = 1.0;
  float tc2offset = 0.0;
  float CntSlope = 1.0;
  float CntOffset = 0.0;
  char sapikey[32] = "";
  char my_ssid[32] = "";
  char my_psk[32] = "";
  unsigned long CntSeconds = 300;    // 5 minutes
} configuration;


void setup() {

Serial.begin(115200);
  Serial.print(F("\n\n***\r\n\r\n"));
  Serial.println(ESP.getResetReason());
  Serial.print(F("\n\n***\n\n"));
}


void loop() {
  recvWithEndMarker();    // Check for serial RX data

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
void showNewData() {
    if (newData == true) {
        Serial.print("$[CMD] ");
        Serial.println(receivedChars);
        newData = false;
        command_interperter(receivedChars);
    }
}



