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
#define DEG_PER_STEP 1.8
#define STEP_PER_REVOLUTION (360 / DEG_PER_STEP)

AccelStepper stepper(AccelStepper::FULL4WIRE, 7, 6, 5, 4);

int wavetype = 0;
int speed = 0;
int distance = 0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  // You can provide a unique client ID, if not set the library uses Arduino-millis()
  // Each client must have a unique client ID
  // mqttClient.setId("clientId");

  // You can provide a username and password for authentication
  // mqttClient.setUsernamePassword("username", "password");

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);

  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("Waiting for messages on topic: ");
  Serial.println(topic);
  Serial.println();
}

void loop() {
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
    // we received a message, print out the topic and contents
    Serial.print("Received a message with topic '");
    Serial.print(mqttClient.messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // Stream in characters one by one into string message
    char message[100] = "";
    while (mqttClient.available()) {
      char ch = (char)mqttClient.read();
      strncat(message, &ch, 1);
    }
    Serial.print("Message: "); Serial.print(message);

    Serial.println();

    char * token = strtok(message, " ");
    wavetype = atoi(token);
    Serial.print("Wavetype: "); Serial.print(wavetype);

    Serial.println();

    token = strtok(NULL, " ");
    speed = atoi(token);
    Serial.print("Speed: "); Serial.print(speed);

    Serial.println();

    token = strtok(NULL, " ");
    distance = atoi(token);
    Serial.print("Distance: "); Serial.print(distance);

    Serial.println();
    Serial.println();

    /*MonoPulse Mode*/
    // value of 255: pulse mode
    if(wavetype == 1){
      Serial.print("MonoPulse Mode at speed: "); Serial.print(speed); Serial.print(" and distance: "); Serial.print(distance);
      // stepper.setMaxSpeed(speed);
      // stepper.setAcceleration(speed);

      // stepper.moveTo(distance);
      // while (stepper.currentPosition() != distance) // Full speed up to 300
      //   stepper.run();
      // stepper.stop(); // Stop as fast as possible: sets new target
      // stepper.runToPosition(); 
      // // Now stopped after quickstop
    
      // // Now go backwards
      // stepper.moveTo(0);
      // while (stepper.currentPosition() != 0) // Full speed basck to 0
      //   stepper.run();
      // stepper.stop(); // Stop as fast as possible: sets new target
      // stepper.runToPosition(); 
      // // Now stopped after quickstop
    }
    if(wavetype == 2){
      Serial.print("Wavetype2 Mode at speed: "); Serial.print(speed); Serial.print(" and distance: "); Serial.print(distance);
    }
    if(wavetype == 3){
      Serial.print("Wavetype3 Mode at speed: "); Serial.print(speed); Serial.print(" and distance: "); Serial.print(distance);
    }






  }
}