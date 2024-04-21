#include "DHT.h"                // Thermometer and hygrometer

#include <ESP8266WiFi.h>        
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#define DHT22PIN1 D2            // digital pin for DHT22

#define DHT22TYPE1 DHT22         // DHT 22  (AM2302), AM2321

DHT dht1(DHT22PIN1, DHT22TYPE1);

const char* ssid = "ESP8266";   // "ESP8266";             
const char* password = "ESP8266"; // "ESP8266";
const char* serverName = "http://192.168.1.36:5102/sensor";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());

  dht11.begin();
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);

    char payload[2000];

    char begining[] = "{\"BoardId\":\"WeMosD1\",\"Inside\":{";

    char insideTemperatureStr[] = "\"Temperature\":";
    float insideTemperature = dht1.readTemperature();   

    char ending[] = "}}";

    sprintf(payload,
      "%s%s%.1f%s",
      begining,
      insideTemperatureStr,
      insideTemperature,
      ending);

    Serial.println(payload);

    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(payload1);
     
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
        
    // Free resources
    http.end();

    delay(10000); // increase to ~60 sec
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}
