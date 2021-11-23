#include "main.h"

void callback(char *topic, byte *payload, unsigned int length) {

    String payloadString = "";
    Serial.print("\nMensage recibido = [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++)
        payloadString += (char) payload[i];

    Serial.println(payloadString);

    if (payloadString == "ACON") {
        unsigned long code = 0xAE1081C0UL;
        digitalWrite(LED_BUILTIN_AUX, LOW);
        setACTemp(17);
        return;
    }
    if (payloadString == "ACOFF") {
        digitalWrite(LED_BUILTIN_AUX, HIGH);
        setACTemp(17);
        return;
    }

    if (payloadString.substring(0, 5) == "ACTEMP=") {
        int currentTemp = payloadString.substring(7).toInt();
        setACTemp(currentTemp);
        return;
    }

    if (payloadString.substring(0, 5) == "WIZON") {
        setWizState(true);
        return;
    }

    if (payloadString.substring(0, 6) == "WIZOFF") {
        setWizState(false);
        return;
    }

    if (payloadString.substring(0, 7) == "WIZRGB=") {
        //  WIZRGB=RED,GRE,BLU
        int r = payloadString.substring(7, 10).toInt();
        int g = payloadString.substring(11, 14).toInt();
        int b = payloadString.substring(15, 18).toInt();
        setWizRGB(r, g, b);
        return;
    }

    if (payloadString.substring(0, 6) == "WIZCW=") {
        //  WIZRGB=COLD,WARM
        int cold = payloadString.substring(7, 10).toInt();
        int warm = payloadString.substring(11, 14).toInt();
        setWizWhite(cold,warm);
        return;
    }

    if (payloadString.substring(0, 7) == "WIZDIM=") {
        int dimming = payloadString.substring(7).toInt();
        setWizDimming(dimming);
        return;
    }
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Intentando una conexión MQTT...");
        client.setBufferSize(255);
        if (client.connect("ESP8266", "LDR", "PNxKHCzjE6un6rs")) {
            Serial.println("¡Conectado!");
            client.subscribe(inputTopic);
        } else {
            Serial.print("¡Fallido!, Codigo de Resultado (rc) =");
            Serial.print(client.state());
            Serial.println(" intente de nuevo dentro de 2 segundos");
            //delay(2000);
        }
    }
}

void mqttControl() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}
