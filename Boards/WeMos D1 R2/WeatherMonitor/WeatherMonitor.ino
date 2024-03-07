#include "DHT.h"                // Thermometer and hygrometer

#include <Wire.h>               // DFRobot_BMP280 sensor
#include "DFRobot_BMP280.h"     // DFRobot_BMP280 sensor

#define DHT11PIN D4             // digital pin for DHT11
#define DHT11TYPE DHT11         // DHT 11

#define DHT22PIN D5             // digital pin for DHT22
#define DHT22TYPE DHT22         // DHT 22  (AM2302), AM2321

#define SEA_LEVEL_PRESSURE    1015.0f   // sea level pressure

DHT dht11(DHT11PIN, DHT11TYPE);
DHT dht22(DHT22PIN, DHT22TYPE);

typedef DFRobot_BMP280_IIC    BMP;    // ******** use abbreviations instead of full names ********

BMP   bmp(&Wire, BMP::eSdoLow);

// show last sensor operate status
void printLastOperateStatus(BMP::eStatus_t eStatus)
{
  switch(eStatus) {
  case BMP::eStatusOK:    Serial.println("everything ok"); break;
  case BMP::eStatusErr:   Serial.println("unknow error"); break;
  case BMP::eStatusErrDeviceNotDetected:    Serial.println("device not detected"); break;
  case BMP::eStatusErrParameter:    Serial.println("parameter error"); break;
  default: Serial.println("unknow status"); break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  dht11.begin();
  dht22.begin();

  bmp.reset();
  Serial.println("bmp read data test");
  while(bmp.begin() != BMP::eStatusOK) {
    Serial.println("bmp begin faild");
    printLastOperateStatus(bmp.lastOperateStatus);
    delay(2000);
  }
  Serial.println("bmp begin success");

  bmp.setConfigFilter(BMP::eConfigFilter_off);        // set config filter
  bmp.setConfigTStandby(BMP::eConfigTStandby_125);    // set standby time
  bmp.setCtrlMeasSamplingTemp(BMP::eSampling_X8);     // set temperature over sampling
  bmp.setCtrlMeasSamplingPress(BMP::eSampling_X8);    // set pressure over sampling
  bmp.setCtrlMeasMode(BMP::eCtrlMeasModeNormal);     // set control measurement mode to make these settings effective

  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(59970); // Wait 60 seconds between measurements - experimental sensor reading time
  
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
  Serial.print(bmp.getTemperature());
  Serial.print(" *C");

  uint32_t pressure = bmp.getPressure();
    
  Serial.print("Pressure: ");
  Serial.print(pressure/100);
  Serial.print(" hPa");

  Serial.print("Altitude: ");
  Serial.print(bmp.calAltitude(SEA_LEVEL_PRESSURE, pressure)); // this should be adjusted to your local forecast??
  Serial.println(" m");
}
