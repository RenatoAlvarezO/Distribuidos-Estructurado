#include "main.h"

void setupWiFi() {

    Serial.println();
    Serial.print("Conectandose a ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_BUILTIN_AUX, HIGH);

    Serial.println("Conectando");
    while (WiFi.status() != WL_CONNECTED && connectionCount < connectionTimeout) {
        Serial.print(".");
        connectionCount++;
    }

    if (connectionCount >= connectionTimeout) {
        Serial.println("\nNo se pudo conectar");
        digitalWrite(LED_BUILTIN, HIGH);
        connected = false;
    } else {
        Serial.println("\n¡Conectado!");
        digitalWrite(LED_BUILTIN, LOW);
        connected = true;
    }
}

void checkWiFiConnection() {

    if (WiFi.status() == WL_CONNECTED)
        return;
    connected = false;
    Serial.println("Intentando volver a Conectar al WiFi");
    for (int attemps = 0; attemps > maxAttempts; attemps++) {
        setupWiFi();
        if (connected)
            return;
    }

    Serial.println("No se pudo conectar, revise su conexión y luego reinicie el dispositivo");
    while (1) {
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
    }
}
