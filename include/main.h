//
// Created by renato on 8/11/21.
//

#ifndef IR_MAIN_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "ESP8266TimerInterrupt.h"
#include "PubSubClient.h"

#include <IRremote.h>
#include </home/renato/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266WiFi/src/WiFiUdp.h>

#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15


//  MQTT
const char *ssid = "Orias";
const char *password = "Escualido1470";
const char *mqttServer = "node02.myqtthub.com";

//  WiFi
int connectionCount = 0;
int connectionTimeout = 20;
int maxAttempts = 3;
bool connected = false;

WiFiClient espClient;
PubSubClient client(espClient);

const char *inputTopic = "ESP8266/input";
const char *outputTopic = "ESP8266/output";

//  Timers
int mqttCounter = 0;
int irCounter = 0;
long irUpdateTime = 100;
long mqttUpdateTime = 1000;

//  Data
char buffer[50];
int LDRValue;

//  IR
decode_results results;

//  AC MODES
#define TEMPMODE 0
#define COLDMODE 1
#define HEATMODE 2

#define FANLOW 0
#define FANMID 1
#define FANHIGH 2
#define FANAUTO 3

//  Interrupcion por Timer
ESP8266Timer interruptTimer;

//  WiZ Lightbulb

char packet[255];
char udpBuffer[100];
WiFiUDP UDP;
uint16_t UDPPORT = 38899;
IPAddress wizIP(192,168,0,4);

#define IR_MAIN_H

#endif //IR_MAIN_H
