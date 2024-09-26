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

#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;  // your network SSID (name)
char pass[] = SECRET_PASS;  // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;           // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "ee31.eecs.tufts.edu";  // name address for Google (using DNS)
int portNumber = 80;

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

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
    delay(10000);
  }
  Serial.println("Connected to WiFi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
}

void get_command() {
  if (client.connect(server, portNumber)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    format_get(HTTP_UUID, HTTP_UUID);
    client.println("Host: ee31.eecs.tufts.edu");

    client.println("Connection: close");

    client.println();

    delay(1000);
    loop();
  } else {
    Serial.println("not connected");
  }
}

void format_get(char source[], char dest[]) {
  client.print("GET /");
  client.print(source);
  client.print("/");
  client.print(dest);
  client.println(" HTTP/1.1");
}

int client_readline(char *buf, int bufsize) {
  int count = 0;
  char c = client.read();

  while (client.available() > 0 && c != '\n') {
    buf[count] = c;
    c = client.read();
    count++;
  }
  buf[count] = '\0';

  return count;
}

void line_parsevar(char *line, int line_len, char *buf, int buf_len, char *varname) {
  int state = 0; // 0 = reading variable name, 1 = reading variable value

  char current_varname[200];
  int varname_counter = 0;
  int buf_counter = 0;

  for (char i = 0; i < line_len; i++) {
    if (state == 0) {
      if (line[i] != '=') {
        current_varname[varname_counter] = line[i];
        varname_counter++;
      } else {
        current_varname[varname_counter] = '\0';
        varname_counter = 0;
        state = 1;
      }
    } else {
      if (line[i] == '&' || i == line_len - 1) {
        buf[buf_counter] = '\0';
        buf_counter = 0;
        state = 0;
        if (strcmp(varname, current_varname)) {
          printf("True\n");
          return;
        }
      } else {
        buf[buf_counter] = line[i];
        buf_counter++;
      }
    }
  }
}


void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:

  // we need buffer

  /* Things to do:
   * HTTP Status = 200
   * Get content length
   * read [content length] bits from body
   * parse body
  */


  char buf[300];
  char val[200];
  int line_len = 0;

  while (client.available()) {
    // line_len = client_readline(buf, 300);
    char c = client.read();
    Serial.print(c);
    
  }
  // line_parsevar(buf, line_len, val, 200, "hi");
  // Serial.print(val);

  Serial.print('\n');

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true)
      ;  // TODO: reconnect
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
