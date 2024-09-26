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
WiFiClient wifi_client;
HttpClient client = HttpClient(wifi_client, server, portNumber);

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

String line_getvar(String body, String varname) {
  int state = 0; // 0 = reading variable name, 1 = reading variable value

  String current_varname;

  String var_value;

  for (int i = 0; i < body.length(); i++) {
    if (state == 0) {
      if (body[i] != '=') {
        current_varname.concat(body[i]);
      } else {
        var_value = "";
        state = 1;
      }
    } else {
      if (body[i] == '&' || i == body.length()) {
        Serial.println("End of var");
        if (varname == current_varname) {
          Serial.println("True");
          return var_value;
        }
        current_varname = "";
        var_value = "";
        state = 0;
      } else {
        var_value.concat(body[i]);
      }
    }
    Serial.print(current_varname);
    Serial.print(" = ");
    Serial.println(var_value);
  }
}


void loop() {
  Serial.println("Get request");
  client.get("/F392FC86D8D7/F392FC86D8D7");

  String response = client.responseBody();
  Serial.println(response);

  String hi = line_getvar(response, "hi");
  Serial.println(hi);

  while (1);
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
