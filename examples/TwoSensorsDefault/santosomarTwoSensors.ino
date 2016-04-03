#include <SimpleDHT.h>

// Created by santosomar Ωr using SimpleDHT library to read data from two DHT11 sensors
// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      SENSOR 1 is in Digital Data pin: 2
//      SENSOR 1 is in Digital Data pin: 2

int dataPinSensor1 = 2;
int dataPinSensor2 = 4;
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Reading data from sensor 1...
  Serial.println("=================================");

  // Reading data from sensor 1...
  Serial.println("Getting data from sensor 1...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  if (dht11.read(dataPinSensor1, &temperature, &humidity, NULL)) {
    Serial.print("Communication error with Sensor 1");
    return;
  }

   // converting Celsius to Fahrenheit

  byte f = temperature * 1.8 + 32;  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)f); Serial.print(" *F, "); 
  Serial.print((int)humidity); Serial.println(" % humidity");


  // Reading data from sensor 2...
  // ============================

  Serial.println("Getting data from sensor 2...");

  byte temperature2 = 0;
  byte humidity2 = 0;
  if (dht11.read(dataPinSensor2, &temperature2, &humidity2, NULL)) {
    Serial.print("Communication error with sensor 2");
    return;
  }

     // converting Celsius to Fahrenheit

  byte fb = temperature2 * 1.8 + 32;
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)fb); Serial.print(" *F, "); 
  Serial.print((int)humidity2); Serial.println(" % humidity");


  
  // DHT11 sampling rate is 1HZ.
  delay(1500);
}
