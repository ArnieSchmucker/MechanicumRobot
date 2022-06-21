/*********
  Arnie Schmucker
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/

// Import required libraries
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"

// Replace with your network credentials
const char* ssid = "NETGEAR31";
const char* password = "breezyprairie077";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create a WebSocket object
AsyncWebSocket ws("/ws");

struct outputGPIO {
  const int pwmPin;
  const int dir1Pin;
  const int dir2Pin;
  bool gpioState;
};

const int pincerPin = 4;

outputGPIO RF = {21, 17, 16, false};
outputGPIO RR = {19, 18, 5, false};
outputGPIO LF = {23, 22, 14, false};
outputGPIO LR = {32, 15, 33, false};
outputGPIO lift = {27, 12, 13, false};

String sliderValue = "0";
String pincerValue = "0";
String liftValue = "0";
int dutyCycle;
int pincerCycle;
int liftCycle;

// Initialize SPIFFS
void initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void notifyClients(String state) {
  ws.textAll(state);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    int gpio=atoi((char*)data);
    if(gpio == 901) {
      forward();
    }
    else if(gpio == 902) {
      off();
    }
    else if(gpio == 903) {
      aft();
    }
    else if(gpio == 904) {
      left();
    }
    else if(gpio == 905) {
      right();
    }
    else if(gpio == 906) {
      tranLeft();
    }
    else if(gpio == 907) {
      tranRight();
    }
    
    else if(gpio == 908) {
      digitalWrite(lift.dir1Pin, HIGH);
      digitalWrite(lift.dir2Pin, LOW);
      digitalWrite(lift.pwmPin, HIGH);
    }
    else if(gpio == 909) {
     digitalWrite(lift.dir1Pin, LOW);
      digitalWrite(lift.dir2Pin, HIGH);
      digitalWrite(lift.pwmPin, HIGH); 
    } 
    else if(gpio == 910) {
     digitalWrite(lift.dir1Pin, LOW);
      digitalWrite(lift.dir2Pin, LOW);
      digitalWrite(lift.pwmPin, LOW); 
    } 
    else if(gpio >= 200 && gpio <= 300) {
      Serial.print("Pincer Slider ");
      pincerCycle = map(gpio, 200, 300, 11, 25);
      Serial.println(pincerCycle);
    } 
    
    else {
      Serial.print("Motor Slider ");
      dutyCycle = map(gpio, 0, 100, 0, 255);
      Serial.println(dutyCycle);
    }
    
    //notifyClients();
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
 
  // Set GPIOs as outputs
  pinMode(RF.pwmPin, OUTPUT);
  pinMode(RF.dir1Pin, OUTPUT);
  pinMode(RF.dir2Pin, OUTPUT);
  pinMode(LF.pwmPin, OUTPUT);
  pinMode(LF.dir1Pin, OUTPUT);
  pinMode(LF.dir2Pin, OUTPUT);
  pinMode(RR.pwmPin, OUTPUT);
  pinMode(RR.dir1Pin, OUTPUT);
  pinMode(RR.dir2Pin, OUTPUT);
  pinMode(LR.pwmPin, OUTPUT);
  pinMode(LR.dir1Pin, OUTPUT);
  pinMode(LR.dir2Pin, OUTPUT);
  pinMode(pincerPin, OUTPUT);
  pinMode(lift.pwmPin, OUTPUT);
  pinMode(lift.dir1Pin, OUTPUT);
  pinMode(lift.dir2Pin, OUTPUT);
  
  digitalWrite(RF.pwmPin,LOW);
  digitalWrite(LF.pwmPin, LOW);
  digitalWrite(RR.pwmPin,LOW);
  digitalWrite(LR.pwmPin, LOW);

  initSPIFFS();
  initWiFi();
  initWebSocket();

  // configure LED PWM functionalitites
  ledcSetup(8, 5000, 8);
  ledcSetup(1, 50, 8);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(RF.pwmPin, 8);
  ledcAttachPin(LF.pwmPin, 8);
  ledcAttachPin(RR.pwmPin, 8);
  ledcAttachPin(LR.pwmPin, 8); 
  ledcAttachPin(pincerPin, 1);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html",false);
  });

  server.serveStatic("/", SPIFFS, "/");

  server.on("/currentValue", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "/text/plain", String(sliderValue).c_str());
  });

  server.on("/currentValue_01", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "/text/plain", String(pincerValue).c_str());
  });

  // Start server
  server.begin();
}

void loop() {

  ledcWrite(8, dutyCycle);
  ledcWrite(1, pincerCycle);
  ws.cleanupClients();
}
