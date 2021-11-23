#include "main.h"

void callback(char *topic, byte *payload, unsigned int length) {

    String payloadString = "";
    Serial.print("\nMensage recibido = [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++)
        payloadString += (char) payload[i];

    Serial.println(payloadString);

    //  AC
    if (strcmp(topic, tempTopic) == 0) {
        setACTemp(payloadString.toInt(), TEMPMODE);
        return;
    }

    if (strcmp(topic, coldTopic) == 0) {
        setACTemp(payloadString.toInt(), COLDMODE);
        return;
    }

    if (strcmp(topic, heatTopic) == 0) {
        setACTemp(payloadString.toInt(), HEATMODE);
        return;
    }

    if (strcmp(topic, fanTopic) == 0) {
        setACFanSpeed(payloadString.toInt());
        return;
    }

    if (strcmp(topic, swingTopic) == 0) {
        setACSwing();
        return;
    }

    //  WIZ
    if (strcmp(topic, rgbTopic) == 0) {
        int rIndex = payloadString.indexOf(",");
        int gIndex = payloadString.indexOf(",", rIndex + 1);

        int r = payloadString.substring(0, rIndex).toInt();
        int g = payloadString.substring(rIndex + 1, gIndex).toInt();
        int b = payloadString.substring(gIndex + 1).toInt();

        setWizRGB(r, g, b);
        return;
    }

    if (strcmp(topic, stateTopic) == 0) {
        setWizState(payloadString == "ON");
        return;
    }

    if (strcmp(topic, cwTopic) == 0) {
        int coldIndex = payloadString.indexOf(",");

        int cold = payloadString.substring(0, coldIndex).toInt();
        int warm = payloadString.substring(coldIndex + 1).toInt();
        setWizWhite(cold, warm);
        return;
    }

    if (strcmp(topic, dimTopic) == 0) {
        setWizDimming(payloadString.toInt());
        return;
    }

}

void reconnect() {

    while (!client.connected()) {
        unsigned long lastMillis = 0;
        ESP.wdtFeed();
        Serial.print("Intentando una conexión MQTT...");
        client.setBufferSize(255);
        if (client.connect("ESP8266", "LDR", "PNxKHCzjE6un6rs")) {
            Serial.println("¡Conectado!");
            client.subscribe(tempTopic);
            client.subscribe(coldTopic);
            client.subscribe(heatTopic);
            client.subscribe(fanTopic);
            client.subscribe(swingTopic);
            client.subscribe(rgbTopic);
            client.subscribe(stateTopic);
            client.subscribe(cwTopic);
            client.subscribe(dimTopic);
            return;
        } else {
            unsigned long now = millis();
            if (now - lastMillis > connectionTimeout * 2) {
                Serial.print("¡Fallido!, Codigo de Resultado (rc) =");
                Serial.print(client.state());
                Serial.println(" intente de nuevo dentro de 2 segundos");
                lastMillis = now;
            }
        }


    }
}

void mqttControl() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}
