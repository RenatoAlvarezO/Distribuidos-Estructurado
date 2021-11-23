#include "main.h"

void setWizFullValue(bool state, int r, int g, int b, int c, int w, int dimming) {
    String buffer = "{\"method\":\"setPilot\",\"params\":{";
    buffer += "\"state\":" + String(state) + ",";
    buffer += "\"r\":" + String(r) + ",";
    buffer += "\"g\":" + String(g) + ",";
    buffer += "\"b\":" + String(b) + ",";
    buffer += "\"c\":" + String(c) + ",";
    buffer += "\"w\":" + String(w) + ",";
    buffer += "\"dimming\":" + String(dimming) + "}}";
    sendWizUDP(buffer);
}

void setWizState(bool state) {
    String buffer = "{\"method\":\"setPilot\",\"params\":{";
    buffer += "\"state\":" + String(state) + "}}";
    sendWizUDP(buffer);
}

void setWizRGB(int r, int g, int b) {
    String buffer = "{\"method\":\"setPilot\",\"params\":{";
    buffer += "\"r\":" + String(r) + ",";
    buffer += "\"g\":" + String(g) + ",";
    buffer += "\"b\":" + String(b) + "}}";
    sendWizUDP(buffer);
}

void setWizR(int r) {
    String buffer = "{\"method\":\"setPilot\",\"params\":{";
    buffer += "\"r\":" + String(r) + "}}";
    sendWizUDP(buffer);
}

void setWizG(int g) {
    String buffer = "{\"method\":\"setPilot\",\"params\":{";
    buffer += "\"g\":" + String(g) + "}}";
    sendWizUDP(buffer);
}

void setWizB(int b) {
    String buffer = "{\"method\":\"setPilot\",\"params\":{";
    buffer += "\"b\":" + String(b) + "}}";
    sendWizUDP(buffer); 
}

void setWizWhite(int cold, int warm) {
    String buffer = "{\"method\":\"setPilot\",\"params\":{";
    buffer += "\"c\":" + String(cold) + ",";
    buffer += "\"w\":" + String(warm) + "}}";
    sendWizUDP(buffer);
}

void setWizDimming(int dimming) {
    String buffer = "{\"method\":\"setPilot\",\"params\":{";
    buffer += "\"dimming\":" + String(dimming) + "}}";
    sendWizUDP(buffer);
}

void sendWizUDP(String value) {
    value.toCharArray(udpBuffer, 100);
    UDP.beginPacket(wizIP, UDPPORT);
    UDP.write(udpBuffer);
    UDP.endPacket();
}