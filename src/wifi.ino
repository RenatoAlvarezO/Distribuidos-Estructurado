#include "main.h"

void setupWiFi() {

    Serial.println();
    Serial.print("Conectandose a ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_BUILTIN_AUX, HIGH);

    Serial.println("Conectando");
    unsigned long lastMills = 0;
    while (WiFi.status() != WL_CONNECTED && connectionCount < maxAttempts) {
        unsigned long now = millis();
        if (now - lastMills > connectionTimeout) {
            Serial.print(".");
            connectionCount++;
            lastMills = now;
        }
    }

    if (connectionCount >= connectionTimeout) {
        Serial.println("\nNo se pudo conectar");
        digitalWrite(LED_BUILTIN, HIGH);
        connected = false;
        while (1) {
            digitalWrite(LED_BUILTIN, LOW);
            delay(500);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(500);
        }
    }

    Serial.println("\n¡Conectado!");
    digitalWrite(LED_BUILTIN, LOW);
    connected = true;

}

