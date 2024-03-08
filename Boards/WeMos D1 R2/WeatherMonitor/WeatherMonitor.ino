#include "DHT.h"                // Thermometer and hygrometer

#include <Wire.h>               // DFRobot_BMP280 sensor
#include "DFRobot_BMP280.h"     // DFRobot_BMP280 sensor

#define DHT11PIN D4             // digital pin for DHT11
#define DHT11TYPE DHT11         // DHT 11

#define DHT22PIN D5             // digital pin for DHT22
#define DHT22TYPE DHT22         // DHT 22  (AM2302), AM2321

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
  //delay(59970); // Wait 60 seconds between measurements - experimental sensor reading time
  delay(1000);
  
  Serial.print("DHT11: ");

  Serial.print("Temperature: ");
  Serial.print(dht11.readTemperature());  // Read temperature as Celsius (the default)
  Serial.print(" *C ");
  
  Serial.print("Humidity: ");
  Serial.print(dht11.readHumidity());
  Serial.print(" % ");

  Serial.print("Heat Index: ");
  Serial.print(dht11.computeHeatIndex(dht11.readTemperature(), dht11.readHumidity(), false)); // Compute heat index in Celsius (isFahreheit = false)
  Serial.print(" *C ");

  Serial.print("DHT22: ");

  Serial.print("T: ");
  Serial.print(dht22.readTemperature());  // Read temperature as Celsius (the default)
  Serial.print(" *C ");
  
  Serial.print("H: ");
  Serial.print(dht22.readHumidity());
  Serial.print(" % ");

  Serial.print("HI: ");
  Serial.print(dht22.computeHeatIndex(dht22.readTemperature(), dht22.readHumidity(), false)); // Compute heat index in Celsius (isFahreheit = false)
  Serial.print(" *C ");

  Serial.println("--- BMP280 ---");

  Serial.print("Temperature: ");
  Serial.print(bmp280.readTemperatureValue());
  Serial.println(" *C");

  int pressure = bmp280.readPressureValue()/100;
    
  Serial.print("Pressure: ");
  Serial.print(bmp280.readPressureValue()/100);
  Serial.println(" hPa");

  Serial.print("Altitude: ");
  Serial.print(bmp280.readAltitudeValue(1013.25)); // this should be adjusted to your local forecast?
  Serial.println(" m");
}
