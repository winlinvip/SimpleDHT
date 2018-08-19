#include <SimpleDHT.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  Serial.begin(115200);
}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11 with error count");

  int cnt = 0;
  int err_cnt = 0;
  for (;;) {
    cnt++;

    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
      Serial.print("DHT11 read failed "); Serial.print(err); err_cnt++;
    } else {
      Serial.print("DHT11, ");
      Serial.print((int)temperature); Serial.print(" *C, ");
      Serial.print((int)humidity); Serial.print(" H");
    }
    Serial.print(", total: "); Serial.print(cnt);
    Serial.print(", err: "); Serial.print(err_cnt);
    Serial.print(", success rate: "); Serial.print((cnt - err_cnt) * 100.0 / (float)cnt); Serial.println("%");

    delay(1500);
  }
}
