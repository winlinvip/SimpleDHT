#include <SimpleDHT.h>

// for DHT22,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT22 = 2;
SimpleDHT22 dht22(pinDHT22);

void setup() {
  Serial.begin(115200);
}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT22 with RAW bits...");
  
  // read with raw sample data.
  // @remark We use read2 to get a float data, such as 10.1*C
  //    if user doesn't care about the accurate data, use read to get a byte data, such as 10*C.
  float temperature = 0;
  float humidity = 0;
  byte data[5] = {0};
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(&temperature, &humidity, data)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(2000);
    return;
  }
  
  Serial.print("Sample RAW Bits: ");
  for (int i = 0; i < 5; i++) {
      for (int n = 0; n < 8; n++)
          Serial.print(bitRead(data[i], n));
      Serial.print(' ');
  }
  Serial.println("");
  
  Serial.print("Sample OK: ");
  Serial.print((float)temperature); Serial.print(" *C, ");
  Serial.print((float)humidity); Serial.println(" RH%");
  
  // DHT22 sampling rate is 0.5HZ.
  delay(2500);
}
