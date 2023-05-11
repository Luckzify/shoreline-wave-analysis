#include<stdio.h>
#include <string.h>

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include <AccelStepper.h>

#include "arduino_secrets.h"

// WIFI MQTT CODE /////////////////////////////////////////////
char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int        port     = 1883;
const char topic[]  = "wave/motor";

// STEPPER CODE /////////////////////////////////////////////

AccelStepper stepper(AccelStepper::FULL4WIRE, 7, 6, 5, 4);

int wavetype;
int speed;
int distance;

void setup() {
  // attempt to connect to WiFi network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    delay(5000);
  }
  if (!mqttClient.connect(broker, port)) {
    while (1);
  }
  // subscribe to a topic
  mqttClient.subscribe(topic);

  // Wave Tank
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
    wavetype = atoi(token);

    token = strtok(NULL, " ");
    speed = atoi(token);

    token = strtok(NULL, " ");
    distance = atoi(token);

    /*MonoPulse Mode*/
    // value of 255: pulse mode
    if(wavetype == 1){
      stepper.setMaxSpeed(speed);
      stepper.setAcceleration(speed);

      stepper.moveTo(distance);
      while (stepper.currentPosition() != distance) // Full speed up to 300
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
      // Now stopped after quickstop
    }
    if(wavetype == 2){
      stepper.setMaxSpeed(speed);
      stepper.setAcceleration(speed);

      for (int i = 0; i < 5; i++) {
        stepper.moveTo(distance);
        while (stepper.currentPosition() != distance) // Full speed up to 300
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
        // Now stopped after quickstop
      }
    }
    if(wavetype == 3){
      stepper.setMaxSpeed(speed);
      stepper.setAcceleration(speed);

      stepper.moveTo(distance);
      while (stepper.currentPosition() != distance) // Full speed up to 300
        stepper.run();
      stepper.stop(); // Stop as fast as possible: sets new target
      stepper.runToPosition(); 
      // Now stopped after quickstop
    
      // Now go backwards
      stepper.setMaxSpeed(1000);
      stepper.setAcceleration(1000);
      stepper.moveTo(0);
      while (stepper.currentPosition() != 0) // Full speed basck to 0
        stepper.run();
      stepper.stop(); // Stop as fast as possible: sets new target
      stepper.runToPosition(); 
      // Now stopped after quickstop
    }
  }
}