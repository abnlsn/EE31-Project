/*
* Authors: Abe Nelson, Eric M. Rohloff
* Date: 11/21/2024
* 
* Wifi Client Setup to Send and Recieve Messages from Server
*/

// Variable Definitions
#ifndef WIFI_CLIENT_H
#define WIFI_CLIENT_H

// Function to connect to Wifi
void wifi_setup();

// Function to get Message from WebSocket Server
String wifi_getmessage();

// Function to send Message to WebSocket Server
void wifi_sendmessage(String message);

#endif