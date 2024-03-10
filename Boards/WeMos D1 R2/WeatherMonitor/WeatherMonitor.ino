#include "DHT.h"                // Thermometer and hygrometer

#include <Wire.h>               // DFRobot_BMP280 sensor
#include "DFRobot_BMP280.h"     // DFRobot_BMP280 sensor

#define DHT11PIN D4             // digital pin for DHT11
#define DHT11TYPE DHT11         // DHT 11

#define DHT22PIN D5             // digital pin for DHT22
#define DHT22TYPE DHT22         // DHT 22  (AM2302), AM2321

#define PHOTORESISTOR_PIN A0    // A0 - analog input 

DHT dht22(DHT22PIN, DHT22TYPE);
DHT dht11(DHT11PIN, DHT11TYPE);

DFRobot_BMP280 bmp280;  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  dht11.begin();
  dht22.begin();

  if (!bmp280.begin()) {  
    Serial.println("Could not find a valid BMP280 sensor!");
    while (1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //delay(59970); // Wait 60 seconds between measurements - experimental sensor reading time (for DHT 11 and 22 sensors)
  delay(1000);
  
  Serial.print("DHT11|");

  Serial.print("T: ");
  Serial.print(dht11.readTemperature());  // Read temperature as Celsius (the default)
  Serial.print("*C ");
  
  Serial.print("H: ");
  Serial.print(dht11.readHumidity());
  Serial.print("% ");

  Serial.print("HI: ");
  Serial.print(dht11.computeHeatIndex(dht11.readTemperature(), dht11.readHumidity(), false)); // Compute heat index in Celsius (isFahreheit = false)
  Serial.print("*C ");

  Serial.print("DHT22|");

  Serial.print("T: ");
  Serial.print(dht22.readTemperature());  // Read temperature as Celsius (the default)
  Serial.print("*C ");
  
  Serial.print("H: ");
  Serial.print(dht22.readHumidity());
  Serial.print("% ");

  Serial.print("HI: ");
  Serial.print(dht22.computeHeatIndex(dht22.readTemperature(), dht22.readHumidity(), false)); // Compute heat index in Celsius (isFahreheit = false)
  Serial.print("*C ");

  Serial.print("BMP280|");

  Serial.print("T: ");
  Serial.print(bmp280.readTemperatureValue());
  Serial.print("*C ");

  int pressure = bmp280.readPressureValue()/100;
    
  Serial.print("P: ");
  Serial.print(bmp280.readPressureValue()/100);
  Serial.print("hPa ");

  Serial.print("A: ");
  Serial.print(bmp280.readAltitudeValue(1013.25)); // 1013.25 this should be adjusted to your local forecast?
  Serial.print("m ");

  int rawLumosity = analogRead(PHOTORESISTOR_PIN);
  float lumosityPercentage = map (rawLumosity, 30, 1024, 0, 100); // analog reading, reading minimum value, reading max value, minimum transformed value, maximum transformed value

  Serial.print("|RL: "); // Raw Lumosity: 
  Serial.print(rawLumosity); // 0V .. 5V --> 0 .. 1023

  Serial.print(" L: "); // Lumosity %
  Serial.print(lumosityPercentage); // 0 .. 1023 --> 0 .. 100 | 10k ohm: ~91 - 1024 - but starging value in not so sunny room was 1024 | 1k ohm: starting value ~650, min value ~30, max value 1024 using flashlight 
  Serial.println("% ");
  
}
