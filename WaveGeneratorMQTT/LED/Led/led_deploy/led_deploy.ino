#include<stdio.h>
#include <string.h>

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h"

// WIFI MQTT CODE /////////////////////////////////////////////
char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int        port     = 1883;
const char topic[]  = "led/control";

int led = 0;
#define LED_PIN 8

void setup() {
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    delay(5000);
  }

  if (!mqttClient.connect(broker, port)) {
    while (1);
  }

  // subscribe to a topic
  mqttClient.subscribe(topic);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {

    // Stream in characters one by one into string message
    char message[100] = "";
    while (mqttClient.available()) {
      char ch = (char)mqttClient.read();
      strncat(message, &ch, 1);
    }

    char * token = strtok(message, " ");
    led = atoi(token);

    if(led == 0){
      digitalWrite(LED_PIN, LOW);
    }
    if(led == 1){
      digitalWrite(LED_PIN, HIGH);
    }
  }
}