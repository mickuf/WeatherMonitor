#include "DHT.h"                // Thermometer and hygrometer

#define DHT11PIN D4             // digital pin for DHT11
#define DHT11TYPE DHT11         // DHT 11

DHT dht11(DHT11PIN, DHT11TYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  dht11.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(60000); // Wait 60 seconds between measurements.
  
  Serial.print("DHT11: ");

  Serial.print("Temperature: ");
  Serial.print(dht11.readTemperature());  // Read temperature as Celsius (the default)
  Serial.print(" *C ");
  
  Serial.print("Humidity: ");
  Serial.print(dht11.readHumidity());
  Serial.print(" % ");

  Serial.print("Heat Index: ");
  Serial.print(dht11.computeHeatIndex(dht11.readTemperature(), dht11.readHumidity(), false)); // Compute heat index in Celsius (isFahreheit = false)
  Serial.println(" *C ");
}
