#include "DHT.h"                // Thermometer and hygrometer

#define DHT11PIN D4             // digital pin for DHT11
#define DHT11TYPE DHT11         // DHT 11

#define DHT22PIN D5             // digital pin for DHT22
#define DHT22TYPE DHT22         // DHT 22  (AM2302), AM2321

DHT dht11(DHT11PIN, DHT11TYPE);
DHT dht22(DHT22PIN, DHT22TYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  dht11.begin();
  dht22.begin();
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
  Serial.println(" *C ");
}
