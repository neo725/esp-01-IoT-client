#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <AES.h>
#include <string.h>

#include "main.h"
#include "SocketIOClient.h"

char ssid[] = "NeoHome2130-ITH"; // your network SSID (name)
char pass[] = "29550674"; // your network password

char socket_host[] = "192.168.100.2";
int socket_port = 3312;

SocketIoClient webSocket;
bool socketConnected = false;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("* ");
     Serial.println(WiFi.status());
  }

  printCurrentNet();
  printWifiData();

  //webSocket.on("message", SocketIO_OnMessage);
  webSocket.on("connect", SocketIO_OnConnect);
  webSocket.on("disconnect", SocketIO_OnDisconnect);
  webSocket.begin(socket_host, socket_port);
}

void loop() {
  // check the network connection once every 10 seconds:
  //delay(10000);
  //printCurrentNet();

  webSocket.loop();
  //delay(500);
}

void SocketIO_OnConnect(const char * payload, size_t length) {
  socketConnected = true;

  Serial.println("Socket.IO connected !");
  webSocket.emit("message", "\"A8GpBy1IHNVyt9F7OsoUwjrxDV1tZkuHvPntFP9tPRx7Rp4UuaOErCm3lXokVdEStGruam5OkZYbk1neCjp0mt+3pC7JUMpT23Ib/JZxBVSDMqLFa/2N3TBLUdvQiOBI9vSWNyCkSecsp5e+RiZPmTmRU3XCUj2AQ4cvVSEDCKHhqsiL7j9cNaPgmv4UmdYa1Er95PcFaMjw8N6yJNGQEQIS/e5es6CAUmlifo5EzM2zh04VeRnb0mDtcwmypdtF0mrWJGnsP5GRH7LsnEPaNWfi7xfOQLTP/QhHA5YGuavysLkDYHfWO7dHom/103QMyQnkUyRry9zuEynGeSkkAQ==\"");
}

void SocketIO_OnDisconnect(const char * payload, size_t length) {
  socketConnected = false;
  
  Serial.println("Socket.IO Disconnect !!!");
}

void SocketIO_OnMessage(const char * payload, size_t length) {

}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // // print the encryption type:
  // byte encryption = WiFi.encryptionType();
  // Serial.print("Encryption Type:");
  // Serial.println(encryption, HEX);
  // Serial.println();
}