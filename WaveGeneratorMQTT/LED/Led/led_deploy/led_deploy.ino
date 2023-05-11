#include<stdio.h>
#include <string.h>

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include <AccelStepper.h>

#include "arduino_secrets.h"


AccelStepper stepper(AccelStepper::FULL4WIRE, 7, 6, 5, 4);

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
  
  stepper.setCurrentPosition(0); 
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

      stepper.setMaxSpeed(100);
      stepper.setAcceleration(100);

      stepper.moveTo(100);
      while (stepper.currentPosition() != 100) // Full speed up to 300
        stepper.run();
      stepper.stop(); // Stop as fast as possible: sets new target
      stepper.runToPosition(); 
      // Now stopped after quickstop
    
      // Now go backwards
      stepper.moveTo(0);
      while (stepper.currentPosition() != 0) // Full speed basck to 0
        stepper.run();
      stepper.stop(); // Stop as fast as possible: sets new target
      stepper.runToPosition();

      digitalWrite(LED_PIN, LOW);
    }
  }
}