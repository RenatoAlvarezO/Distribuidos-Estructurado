//
// Created by renato on 8/11/21.
//

#ifndef IR_MAIN_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "ESP8266TimerInterrupt.h"
#include "PubSubClient.h"
#include <DHT.h>
#include <DHT_U.h>

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
int connectionTimeout = 1000;
int maxAttempts = 20;
bool connected = false;

WiFiClient espClient;
PubSubClient client(espClient);

const char *tempTopic = "ESP8266/AC/Temp";
const char *coldTopic = "ESP8266/AC/Cold";
const char *heatTopic = "ESP8266/AC/Heat";
const char *fanTopic = "ESP8266/AC/Fan";
const char *swingTopic = "ESP8266/AC/Swing";
const char *rgbTopic = "ESP8266/WiZ/RGB";
const char *stateTopic = "ESP8266/WiZ/state";
const char *cwTopic = "ESP8266/WiZ/CW";
const char *dimTopic = "ESP8266/WiZ/Dim";

const char *ldrTopic = "ESP8266/LDR";
const char *dhtTempTopic = "ESP8266/Temp";
const char *dhtHumTopic = "ESP8266/Hum";


//  Timers
unsigned long mqttCounter = 0;
unsigned long irCounter = 0;
long irUpdateTime = 100;
long mqttUpdateTime = 1000;

//  Data
char buffer[50];
int LDRValue;
float DHTTemperature;
float DHTHumidity;

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

//  DHT
#define DHTTYPE DHT11
#define DHTPIN D4
DHT dht(DHTPIN, DHTTYPE);

#define IR_MAIN_H

#endif //IR_MAIN_H
