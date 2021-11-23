#include "main.h"

void IRAM_ATTR TimerHandler() {
    mqttCounter++;
    irCounter++;
    Serial.println(mqttServer);
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_BUILTIN_AUX, OUTPUT);
    Serial.begin(9600);
    setupWiFi();
    client.setServer(mqttServer, 1883);
    client.setCallback(callback);

    dht.begin();

    IrSender.begin(D5, false);
    IrSender.enableIROut(38);
    IrReceiver.begin(D2, false);

}

void loop() {

    if (WiFi.status() != WL_CONNECTED)
        setupWiFi();

    mqttControl();
    readIR();
    sendData();

}