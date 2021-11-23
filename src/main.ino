#include "main.h"

void IRAM_ATTR TimerHandler() {
    mqttCounter++;
    irCounter++;
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_BUILTIN_AUX, OUTPUT);
    Serial.begin(9600);
    setupWiFi();
    client.setServer(mqttServer, 1883);
    client.setCallback(callback);

    interruptTimer.attachInterruptInterval(1000, TimerHandler);

    IrSender.begin(D5, false);
    IrSender.enableIROut(38);
    IrReceiver.begin(D2, false);
}

void loop() {

    checkWiFiConnection();
    mqttControl();
    readIR();
    sendData();

}