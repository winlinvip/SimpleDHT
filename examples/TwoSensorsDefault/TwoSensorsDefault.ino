#include <SimpleDHT.h>

// Created by santosomar Ωr using SimpleDHT library to read data from two DHT11 sensors
// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      SENSOR 1 is in Digital Data pin: 2
//      SENSOR 2 is in Digital Data pin: 4

int dataPinSensor1 = 2;
int dataPinSensor2 = 4;
SimpleDHT11 dht1(dataPinSensor1);
SimpleDHT11 dht2(dataPinSensor2);

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Reading data from sensor 1...
  Serial.println("=================================");

  // Reading data from sensor 1...
  Serial.println("Getting data from sensor 1...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht1.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read Sensor 1 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }

   // converting Celsius to Fahrenheit
  byte f = temperature * 1.8 + 32;
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)f); Serial.print(" *F, "); 
  Serial.print((int)humidity); Serial.println(" H humidity");


  // Reading data from sensor 2...
  // ============================
  Serial.println("Getting data from sensor 2...");

  byte temperature2 = 0;
  byte humidity2 = 0;
  if ((err = dht2.read(&temperature2, &humidity2, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read Sensor 2 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }

  // converting Celsius to Fahrenheit
  byte fb = temperature2 * 1.8 + 32;
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature2); Serial.print(" *C, "); 
  Serial.print((int)fb); Serial.print(" *F, "); 
  Serial.print((int)humidity2); Serial.println(" H humidity");

  // DHT11 sampling rate is 1HZ.
  delay(1500);
}
