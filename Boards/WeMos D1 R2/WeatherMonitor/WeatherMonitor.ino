#include "DHT.h"                // Thermometer and hygrometer

#include <Wire.h>               // DFRobot_BMP280 sensor
#include "DFRobot_BMP280.h"     // DFRobot_BMP280 sensor

#include <ESP8266WiFi.h>        // WiFi
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
//#include <ESP8266mDNS.h>
//#include <ESP8266WebServer.h> 

#define DHT11PIN D4             // digital pin for DHT11
#define DHT11TYPE DHT11         // DHT 11

#define DHT22PIN D5             // digital pin for DHT22
#define DHT22TYPE DHT22         // DHT 22  (AM2302), AM2321

#define PHOTORESISTOR_PIN A0    // A0 - analog input 

DHT dht22(DHT22PIN, DHT22TYPE);
DHT dht11(DHT11PIN, DHT11TYPE);

DFRobot_BMP280 bmp280;

const char* ssid = "ESP8266";  // "ESP8266";             // TODO MOVE TO NEW FILE WITH gitingore!  
const char* password = "ESP8266";  // "ESP8266";    // TODO MOVE TO NEW FILE WITH gitingore!
const char* serverName = "http://192.168.1.36:5102/test";//"http://192.168.1.106:1880/update-sensor";

//ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

//void handleRoot();              // function prototypes for HTTP handlers
//void handleNotFound();

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

  //if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
  //  Serial.println("mDNS responder started");
  //} else {
  //  Serial.println("Error setting up MDNS responder!");
  //}

//  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
// server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

//  server.begin();                           // Actually start the server
//  Serial.println("HTTP server started");

  dht11.begin();
  dht22.begin();

  if (!bmp280.begin()) {  
    Serial.println("Could not find a valid BMP280 sensor!");
    while (1);
  }
  
}

//void handleRoot() {
//  server.send(200, "text/plain", "Hello world!");   // Send HTTP status 200 (Ok) and send some text to the browser/client
//}

//void handleNotFound(){
//  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
//}

void loop() {
  // put your main code here, to run repeatedly:
  //delay(59970); // Wait 60 seconds between measurements - experimental sensor reading time (for DHT 11 and 22 sensors)
  
  //server.handleClient();                    // Listen for HTTP requests from clients
  
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
      // Specify content-type header
      //http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&value1=24.25&value2=49.54&value3=1005.14";           
      // Send HTTP POST request
      int httpResponseCode = http.GET(); //http.POST(httpRequestData);
      
      // If you need an HTTP request with a content type: application/json, use the following:
      //http.addHeader("Content-Type", "application/json");
      //int httpResponseCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();

      delay(10000);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  //  delay(1000); //???
//  
//  Serial.print("DHT11|");
//
//  Serial.print("T: ");
//  Serial.print(dht11.readTemperature());  // Read temperature as Celsius (the default)
//  Serial.print("*C ");
//  
//  Serial.print("H: ");
//  Serial.print(dht11.readHumidity());
//  Serial.print("% ");
//
//  Serial.print("HI: ");
//  Serial.print(dht11.computeHeatIndex(dht11.readTemperature(), dht11.readHumidity(), false)); // Compute heat index in Celsius (isFahreheit = false)
//  Serial.print("*C ");
//
//  Serial.print("DHT22|");
//
//  Serial.print("T: ");
//  Serial.print(dht22.readTemperature());  // Read temperature as Celsius (the default)
//  Serial.print("*C ");
//  
//  Serial.print("H: ");
//  Serial.print(dht22.readHumidity());
//  Serial.print("% ");
//
//  Serial.print("HI: ");
//  Serial.print(dht22.computeHeatIndex(dht22.readTemperature(), dht22.readHumidity(), false)); // Compute heat index in Celsius (isFahreheit = false)
//  Serial.print("*C ");
//
//  Serial.print("BMP280|");
//
//  Serial.print("T: ");
//  Serial.print(bmp280.readTemperatureValue());
//  Serial.print("*C ");
//
//  int pressure = bmp280.readPressureValue()/100;
//    
//  Serial.print("P: ");
//  Serial.print(bmp280.readPressureValue()/100);
//  Serial.print("hPa ");
//
//  Serial.print("A: ");
//  Serial.print(bmp280.readAltitudeValue(1013.25)); // 1013.25 this should be adjusted to your local forecast?
//  Serial.print("m ");
//
//  int rawLumosity = analogRead(PHOTORESISTOR_PIN);
//  float lumosityPercentage = map (rawLumosity, 30, 1024, 0, 100); // analog reading, reading minimum value, reading max value, minimum transformed value, maximum transformed value
//
//  Serial.print("|RL: "); // Raw Lumosity: 
//  Serial.print(rawLumosity); // 0V .. 5V --> 0 .. 1023
//
//  Serial.print(" L: "); // Lumosity %
//  Serial.print(lumosityPercentage); // 0 .. 1023 --> 0 .. 100 | 10k ohm: ~91 - 1024 - but starging value in not so sunny room was 1024 | 1k ohm: starting value ~650, min value ~30, max value 1024 using flashlight 
//  Serial.println("% ");
}
