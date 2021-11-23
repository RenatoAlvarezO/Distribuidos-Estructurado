#include "main.h"

void readLDR() {
    LDRValue = analogRead(0);
}

void readIR() {
    unsigned long irNow = millis();
    if (irNow - irCounter > irUpdateTime) {
        if (IrReceiver.decode()) {
            Serial.print("Codigo recibido por IR = 0x");
            Serial.print(IrReceiver.decodedIRData.command, HEX);
            Serial.print(IrReceiver.decodedIRData.address, HEX);
            Serial.println();
            IrReceiver.resume();
        }
        irCounter = irNow;
    }
}

void sendData() {

    unsigned long mqqtNow = millis();
    if (mqqtNow - mqttCounter > mqttUpdateTime) {
        readLDR();
        snprintf(buffer, sizeof(buffer), "%d", LDRValue);
        client.publish(ldrTopic, buffer);

        DHTTemperature = dht.readTemperature();
        snprintf(buffer, sizeof(buffer), "%2.1f", DHTTemperature);
        client.publish(dhtTempTopic, buffer);

        DHTHumidity = dht.readHumidity();
        snprintf(buffer, sizeof(buffer), "%2.1f", DHTHumidity);
        client.publish(dhtHumTopic, buffer);

        mqttCounter = mqqtNow;
    }
}

void setACTemp(unsigned long temperature, int mode) {

    if (mode < 0 || mode > 2)
        return;

    unsigned char high[] = {0x0B, 0x8E, 0x8B};
    unsigned char low = {0x10};
    unsigned int adresses[] = {0x24C0, 0xA1C0, 0xA4C0};

    temperature = temperature < 16 ? 0 : temperature > 30 ? 15 : temperature - 16;
    unsigned int code = (high[mode] - temperature << 8) | low + temperature;
    code &= 0x0000FFFF;
    IrSender.sendOnkyo(adresses[mode], code, 3);
}

void setACSwing() {
    IrSender.sendOnkyo(0xD0, 0x2F, 3);
}

void setACFanSpeed(int mode) {
    if (mode < 0 || mode > 3)
        return;
    unsigned int address = (0x34C0) - (mode << 12);
    unsigned int command = ((0xF11A) + (mode << 12)) & 0x0000FFFF;
    IrSender.sendOnkyo(address, command, 3);
}


