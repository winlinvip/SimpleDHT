/*
The MIT License (MIT)

Copyright (c) 2016 winlin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "SimpleDHT.h"

// confirm the OUTPUT is level in us, 
// for example, when DHT11 start sample, it will
//    1. PULL LOW 80us, call confirm(pin, 80, LOW)
//    2. PULL HIGH 80us, call confirm(pin, 80, HIGH)
// @return 0 success; oterwise, error.
// @remark should never used to read bits, 
//    for function call use more time, maybe never got bit0.
// @remark please use simple_dht11_read().
int __simple_dht11_confirm(int pin, int us, byte level) {
    // wait one more count to ensure.
    int cnt = us / 10 + 1;

    bool ok = false;
    for (int i = 0; i < cnt; i++) {
        if (digitalRead(pin) != level) {
            ok = true;
            break;
        }
        delayMicroseconds(10);
    }

    if (!ok) {
        return -1;
    }
    return 0;
}

// @data the bits of a byte.
// @remark please use simple_dht11_read().
byte __simple_dht11_bits2byte(byte data[8]) {
    byte v = 0;
    for (int i = 0; i < 8; i++) {
        v += data[i] << (7 - i);
    }
    return v;
}

// read temperature and humidity from dht11.
// @param pin the pin for DHT11, for example, 2.
// @param data a byte[40] to read bits to 5bytes.
// @return 0 success; otherwise, error.
// @remark please use simple_dht11_read().
int __simple_dht11_sample(int pin, byte data[40]) {
    // empty output data.
    memset(data, 0, 40);

    // notify DHT11 to start: 
    //    1. PULL LOW 20ms.
    //    2. PULL HIGH 20-40us.
    //    3. SET TO INPUT.
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(20);
    digitalWrite(pin, HIGH);
    delayMicroseconds(30);
    pinMode(pin, INPUT);

    // DHT11 starting:
    //    1. PULL LOW 80us
    //    2. PULL HIGH 80us
    if (__simple_dht11_confirm(pin, 80, LOW)) {
        return 100;
    }
    if (__simple_dht11_confirm(pin, 80, HIGH)) {
        return 101;
    }

    // DHT11 data transmite:
    //    1. 1bit start, PULL LOW 50us
    //    2. PULL HIGH 26-28us, bit(0)
    //    3. PULL HIGH 70us, bit(1)
    for (int j = 0; j < 40; j++) {
        if (__simple_dht11_confirm(pin, 50, LOW)) {
            return 102;
        }

        // read a bit, should never call method,
        // for the method call use more than 20us,
        // so it maybe failed to detect the bit0.
        bool ok = false;
        int tick = 0;
        for (int i = 0; i < 8; i++, tick++) {
            if (digitalRead(pin) != HIGH) {
                ok = true;
                break;
            }
            delayMicroseconds(10);
        }
        if (!ok) {
            return 103;
        }
        data[j] = (tick > 3? 1:0);
    }

    // DHT11 EOF:
    //    1. PULL LOW 50us.
    if (__simple_dht11_confirm(pin, 50, LOW)) {
        return 104;
    }

    return 0;
}

// parse the 40bits data to temperature and humidity.
// @remark please use simple_dht11_read().
int __simple_dht11_parse(byte data[40], byte* ptemperature, byte* phumidity) {
    byte humidity = __simple_dht11_bits2byte(data);
    byte humidity2 = __simple_dht11_bits2byte(data + 8);
    byte temperature = __simple_dht11_bits2byte(data + 16);
    byte temperature2 = __simple_dht11_bits2byte(data + 24);
    byte check = __simple_dht11_bits2byte(data + 32);
    byte expect = humidity + humidity2 + temperature + temperature2;
    if (check != expect) {
        return 105;
    }
    *ptemperature = temperature;
    *phumidity = humidity;
    return 0;
}

// print the raw data of dht11, 5bytes(40bits).
void simple_dht11_serial_print(byte data[40]) {
    for (int i = 0; i < 40; i++) {
        Serial.print((int)data[i]);
        if (i > 0 && ((i + 1) % 4) == 0) {
            Serial.print(' ');
        }
    }
    Serial.println("");
}

// to read from dht11.
// @param pin the DHT11 pin.
// @param ptemperature output, NULL to igore.
// @param phumidity output, NULL to ignore.
// @param pdata output 40bits sample, NULL to ignore.
// @remark the min delay for this method is 200ms.
int simple_dht11_read(int pin, byte* ptemperature, byte* phumidity, byte pdata[40]) {
    int ret = 0;

    byte data[40] = {0};
    if ((ret = __simple_dht11_sample(pin, data)) != 0) {
        return ret;
    }

    byte temperature = 0;
    byte humidity = 0;
    if ((ret = __simple_dht11_parse(data, &temperature, &humidity)) != 0) {
        return ret;
    }

    if (pdata) {
        memcpy(pdata, data, 40);
    }
    if (ptemperature) {
        *ptemperature = temperature;
    }
    if (phumidity) {
        *phumidity = humidity;
    }

    return ret;
}
