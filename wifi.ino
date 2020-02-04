/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;
int sensorValue = 0; 
int sensorPin = A0;

void setup() {
  pinMode (D0, OUTPUT)
  pinMode (D1, OUTPUT)
  pinMode (D2, OUTPUT)
  pinMode (A0, INPUT)

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Tech Achiever", "#TAIndore");

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;
    sensorValue = analogRead(sensorPin);
    
  sensorValue = map(val, 0, 1023, 0, 100);
  analogWrite(9, val);
  Serial.println(sensorValue);

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://subhamera.000webhostapp.com/api.php?id=2&sensor="String(sensor Value))) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();


      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
          char charBuf[4];
         payload.toCharArray(charBuf, 4)
         digitalWrite(D0, charBuf[0]-48);
         digitalWrite(D1, charBuf[1]-48);
         digitalWrite(D2, charBuf[2]-48); 

          
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(1000);
}
