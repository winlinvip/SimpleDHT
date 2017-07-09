#include <SimpleDHT.h>

// for DHT22, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT22 = 2;
SimpleDHT22 dht22;

void setup() {
  Serial.begin(115200);
}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT22 with error count");

  int cnt = 0;
  int err_cnt = 0;
  for (;;) {
    cnt++;

    float temperature = 0;
    float humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht22.read2(pinDHT22, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
      Serial.print("Read DHT22 failed, err="); Serial.println(err);err_cnt++;
    }

    Serial.print((float)temperature); Serial.print(" *C, ");
    Serial.print((float)humidity); Serial.print(" RH%");
    Serial.print(", total: "); Serial.print(cnt);
    Serial.print(", err: "); Serial.print(err_cnt);
    Serial.print(", success rate: "); Serial.print((cnt - err_cnt) * 100.0 / (float)cnt); Serial.println("%");

    delay(2500);
  }
}
