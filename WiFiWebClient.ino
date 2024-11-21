/*
  Web client

 This sketch connects to a website (http://www.google.com)
 using the WiFi module.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 Circuit:
 * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and Uno WiFi Rev.2)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */

// TODO: make this work better


#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include "state_machine.h"

#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;  // your network SSID (name)
char pass[] = SECRET_PASS;  // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;           // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "34.28.153.91";  // name address for Google (using DNS)
int portNumber = 80;

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient wifi_client;
WebSocketClient client = WebSocketClient(wifi_client, server, portNumber);

int count = 0;

void setup() {
  // Setup state machine

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  statemachine_setup();

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(2000);
  }
  Serial.println("Connected to WiFi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
}

String line_getvar(String body) {
  int state = 0; // 0 = reading variable name, 1 = reading variable value

  String current_varname;

  String var_value;

  for (int i = 0; i < body.length(); i++) {
    if (state == 0) {
      if (body[i] != '.') {
        current_varname.concat(body[i]);
      } else {
        if (current_varname != WEB_UUID) {
          return "";
        }
        state = 1;
      }
    } else {
      if (i == body.length()) {
        Serial.println("End of var");
        current_varname = "";
        var_value = "";
        state = 0;
      } else {
        var_value.concat(body[i]);
      }
    }
  }
  return var_value;
}


void loop() {
  client.begin();
  client.beginMessage(TYPE_TEXT);
  client.print(HTTP_UUID);
  client.endMessage();

  while (client.connected()) {
    if (count > 6000) {
      count = 0;
    }

    // check if a message is available to be received
    int messageSize = client.parseMessage();
    if (messageSize > 0) {
      Serial.println("Received a message:");
      String response = client.readString();
      String msg = line_getvar(response);
      Serial.println(msg);
    }

    // wait 10ms
    delay(10);
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
