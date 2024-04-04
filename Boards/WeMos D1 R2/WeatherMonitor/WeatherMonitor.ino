#include "DHT.h"                // Thermometer and hygrometer

#include <Wire.h>               // DFRobot_BMP280 sensor
#include "DFRobot_BMP280.h"     // DFRobot_BMP280 sensor

#include <ESP8266WiFi.h>        
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#define DHT22PIN1 D4             // digital pin for DHT22 1
#define DHT22PIN2 D5             // digital pin for DHT22 2

#define DHT22TYPE1 DHT22         // DHT 22  (AM2302), AM2321
#define DHT22TYPE2 DHT22         // DHT 22  (AM2302), AM2321

#define PHOTORESISTOR_PIN A0    // A0 - analog input 

DHT dht1(DHT22PIN1, DHT22TYPE1);
DHT dht2(DHT22PIN2, DHT22TYPE2);

DFRobot_BMP280 bmp280;

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
  dht22.begin();

  if (!bmp280.begin()) {  
    Serial.println("Could not find a valid BMP280 sensor!");
    while (1);
  }
  
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);

    char payload[2000];

    char begining[] = "{\"BoardId\":\"WeMosD1R2\",\"Inside\":{";

    char insideTemperatureStr[] = "\"Temperature\":";
    float insideTemperature = dht1.readTemperature();   
    char insideHumidityPercentageStr[] = ",\"HumidityPercentage\":";
    int insideHumidityPercentage = dht1.readHumidity();
    char insideHeatIndexStr[] = ",\"HeatIndex\":";
    float insideHeatIndex = dht1.computeHeatIndex(insideTemperature, insideHumidityPercentage, false); // Compute heat index in Celsius (isFahreheit = false)

    char insidePressureStr[] = ",\"Pressure\":";
    int insidePressure = bmp280.readPressureValue()/100;
       
    char outside[] = "},\"Outside\":{";
    char outsideTemperatureStr[] = "\"Temperature\":";
    float outsideTemperature = dht22.readTemperature();
    char outsideHumidityPercentageStr[] = ",\"HumidityPercentage\":";
    int outsideHumidityPercentage = dht22.readHumidity();
    char outsideHeatIndexStr[] = ",\"HeatIndex\":";
    float outsideHeatIndex = dht22.computeHeatIndex(dht11.readTemperature(), dht11.readHumidity(), false); // Compute heat index in Celsius (isFahreheit = false)
      
    char outsideLumosityPercentageStr[] = ",\"LumosityPercentage\":";
    int rawLumosity = analogRead(PHOTORESISTOR_PIN);
    
    // analog reading, reading minimum value, reading max value, minimum transformed value, maximum transformed value
    // 0 .. 1023 --> 0 .. 100 | 10k ohm: ~91 - 1024 - but starging value in not so sunny room was 1024 | 1k ohm: starting value ~650, min value ~30, max value 1024 using flashlight
    int lumosityPercentage = map(rawLumosity, 30, 1024, 0, 100); 

    char ending[] = "}}";

    sprintf(payload,
      "%s%s%.1f%s%i%s%.1f%s%i%s%s%.1f%s%i%s%.1f%s%i%s",
      begining,
      insideTemperatureStr,
      insideTemperature,
      insideHumidityPercentageStr,
      insideHumidityPercentage,
      insideHeatIndexStr,
      insideHeatIndex,
      insidePressureStr,
      insidePressure,
      outside,
      outsideTemperatureStr,
      outsideTemperature,
      outsideHumidityPercentageStr,
      outsideHumidityPercentage,
      outsideHeatIndexStr,
      outsideHeatIndex,
      outsideLumosityPercentageStr,
      lumosityPercentage,
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
