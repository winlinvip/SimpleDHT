/*
The MIT License (MIT)

Copyright (c) 2016-2017 winlin

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

SimpleDHT::SimpleDHT() {
}

SimpleDHT::SimpleDHT(int pin) {
    setPin(pin);
}

int SimpleDHT::read(byte* ptemperature, byte* phumidity, byte pdata[40]) {
    int ret = SimpleDHTErrSuccess;

    if (pin == -1) {
        return SimpleDHTErrNoPin;
    }

    float temperature = 0;
    float humidity = 0;
    if ((ret = read2(&temperature, &humidity, pdata)) != SimpleDHTErrSuccess) {
        return ret;
    }

    if (ptemperature) {
        *ptemperature = (byte)(int)temperature;
    }

    if (phumidity) {
        *phumidity = (byte)(int)humidity;
    }

    return ret;
}

int SimpleDHT::read(int pin, byte* ptemperature, byte* phumidity, byte pdata[40]) {
    setPin(pin);
    return read(ptemperature, phumidity, pdata);
}

void SimpleDHT::setPin(int pin) {
    this->pin = pin;
#ifdef __AVR
    // (only AVR) - set low level properties for configured pin
    bitmask = digitalPinToBitMask(pin);
    port = digitalPinToPort(pin);
#endif
}

#ifdef __AVR
int SimpleDHT::getBitmask() {
    return bitmask;
}

int SimpleDHT::getPort() {
    return port;
}
#endif

long SimpleDHT::levelTime(byte level, int firstWait, int interval) {
    unsigned long time_start = micros();
    long time = 0;

#ifdef __AVR
    uint8_t portState = level ? bitmask : 0;
#endif

    bool loop = true;
    for (int i = 0 ; loop; i++) {
        if (time < 0 || time > levelTimeout) {
            return -1;
        }

        if (i == 0) {
            if (firstWait > 0) {
                delayMicroseconds(firstWait);
            }
        } else if (interval > 0) {
            delayMicroseconds(interval);
        }

        // for an unsigned int type, the difference have a correct value
        // even if overflow, explanation here:
        //     https://arduino.stackexchange.com/questions/33572/arduino-countdown-without-using-delay
        time = micros() - time_start;

#ifdef __AVR
        loop = ((*portInputRegister(port) & bitmask) == portState);
#else
        loop = (digitalRead(pin) == level);
#endif
    }

    return time;
}

byte SimpleDHT::bits2byte(byte data[8]) {
    byte v = 0;
    for (int i = 0; i < 8; i++) {
        v += data[i] << (7 - i);
    }
    return v;
}

int SimpleDHT::parse(byte data[40], short* ptemperature, short* phumidity) {
    short humidity = bits2byte(data);
    short humidity2 = bits2byte(data + 8);
    short temperature = bits2byte(data + 16);
    short temperature2 = bits2byte(data + 24);
    byte check = bits2byte(data + 32);
    byte expect = (byte)humidity + (byte)humidity2 + (byte)temperature + (byte)temperature2;
    if (check != expect) {
        return SimpleDHTErrDataChecksum;
    }

    *ptemperature = temperature<<8 | temperature2;
    *phumidity = humidity<<8 | humidity2;

    return SimpleDHTErrSuccess;
}

SimpleDHT11::SimpleDHT11() {
}

SimpleDHT11::SimpleDHT11(int pin) : SimpleDHT (pin) {
}

int SimpleDHT11::read2(float* ptemperature, float* phumidity, byte pdata[40]) {
    int ret = SimpleDHTErrSuccess;

    if (pin == -1) {
        return SimpleDHTErrNoPin;
    }

    byte data[40] = {0};
    if ((ret = sample(data)) != SimpleDHTErrSuccess) {
        return ret;
    }

    short temperature = 0;
    short humidity = 0;
    if ((ret = parse(data, &temperature, &humidity)) != SimpleDHTErrSuccess) {
        return ret;
    }

    if (pdata) {
        memcpy(pdata, data, 40);
    }
    if (ptemperature) {
        *ptemperature = (int)(temperature>>8);
    }
    if (phumidity) {
        *phumidity = (int)(humidity>>8);
    }

    // For example, when remove the data line, it will be success with zero data.
    if (temperature == 0 && humidity == 0) {
        return SimpleDHTErrZeroSamples;
    }

    return ret;
}

int SimpleDHT11::read2(int pin, float* ptemperature, float* phumidity, byte pdata[40]) {
    setPin(pin);
    return read2(ptemperature, phumidity, pdata);
}

int SimpleDHT11::sample(byte data[40]) {
    // empty output data.
    memset(data, 0, 40);

    // According to protocol: [1] https://akizukidenshi.com/download/ds/aosong/DHT11.pdf
    // notify DHT11 to start:
    //    1. PULL LOW 20ms.
    //    2. PULL HIGH 20-40us.
    //    3. SET TO INPUT.
    // Changes in timing done according to:
    //  [2] https://www.mouser.com/ds/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf
    // - original values specified in code
    // - since they were not working (MCU-dependent timing?), replace in code with
    //   _working_ values based on measurements done with levelTimePrecise()
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);            // 1.
    delay(20);                         // specs [2]: 18us

    // Pull high and set to input, before wait 40us.
    // @see https://github.com/winlinvip/SimpleDHT/issues/4
    // @see https://github.com/winlinvip/SimpleDHT/pull/5
    digitalWrite(pin, HIGH);           // 2.
    pinMode(pin, INPUT);
    delayMicroseconds(25);             // specs [2]: 20-40us

    // DHT11 starting:
    //    1. PULL LOW 80us
    //    2. PULL HIGH 80us
    long t = levelTime(LOW);          // 1.
    if (t < 30) {                    // specs [2]: 80us
        return simpleDHTCombileError(t, SimpleDHTErrStartLow);
    }

    t = levelTime(HIGH);             // 2.
    if (t < 50) {                    // specs [2]: 80us
        return simpleDHTCombileError(t, SimpleDHTErrStartHigh);
    }

    // DHT11 data transmite:
    //    1. 1bit start, PULL LOW 50us
    //    2. PULL HIGH:
    //         - 26-28us, bit(0)
    //         - 70us, bit(1)
    for (int j = 0; j < 40; j++) {
          t = levelTime(LOW);          // 1.
          if (t < 24) {                    // specs says: 50us
              return simpleDHTCombileError(t, SimpleDHTErrDataLow);
          }

          // read a bit
          t = levelTime(HIGH);              // 2.
          if (t < 11) {                     // specs say: 20us
              return simpleDHTCombileError(t, SimpleDHTErrDataRead);
          }
          data[ j ] = (t > 40 ? 1 : 0);     // specs: 26-28us -> 0, 70us -> 1
    }

    // DHT11 EOF:
    //    1. PULL LOW 50us.
    t = levelTime(LOW);                     // 1.
    if (t < 24) {                           // specs say: 50us
        return simpleDHTCombileError(t, SimpleDHTErrDataEOF);
    }

    return SimpleDHTErrSuccess;
}

SimpleDHT22::SimpleDHT22() {
}

SimpleDHT22::SimpleDHT22(int pin) : SimpleDHT (pin) {
}

int SimpleDHT22::read2(float* ptemperature, float* phumidity, byte pdata[40]) {
    int ret = SimpleDHTErrSuccess;

    if (pin == -1) {
        return SimpleDHTErrNoPin;
    }

    byte data[40] = {0};
    if ((ret = sample(data)) != SimpleDHTErrSuccess) {
        return ret;
    }

    short temperature = 0;
    short humidity = 0;
    if ((ret = parse(data, &temperature, &humidity)) != SimpleDHTErrSuccess) {
        return ret;
    }

    if (pdata) {
        memcpy(pdata, data, 40);
    }
    if (ptemperature) {
        *ptemperature = (float)((temperature & 0x8000 ? -1 : 1) * (temperature & 0x7FFF)) / 10.0;
    }
    if (phumidity) {
        *phumidity = (float)humidity / 10.0;
    }

    return ret;
}

int SimpleDHT22::read2(int pin, float* ptemperature, float* phumidity, byte pdata[40]) {
    setPin(pin);
    return read2(ptemperature, phumidity, pdata);
}

int SimpleDHT22::sample(byte data[40]) {
    // empty output data.
    memset(data, 0, 40);

    // According to protocol: http://akizukidenshi.com/download/ds/aosong/AM2302.pdf
    // notify DHT11 to start:
    //    1. T(be), PULL LOW 1ms(0.8-20ms).
    //    2. T(go), PULL HIGH 30us(20-200us), use 40us.
    //    3. SET TO INPUT.
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(1000);
    // Pull high and set to input, before wait 40us.
    // @see https://github.com/winlinvip/SimpleDHT/issues/4
    // @see https://github.com/winlinvip/SimpleDHT/pull/5
    digitalWrite(pin, HIGH);
    pinMode(pin, INPUT);
    delayMicroseconds(40);

    // DHT11 starting:
    //    1. T(rel), PULL LOW 80us(75-85us).
    //    2. T(reh), PULL HIGH 80us(75-85us).
    long t = 0;
    if ((t = levelTime(LOW)) < 30) {
        return simpleDHTCombileError(t, SimpleDHTErrStartLow);
    }
    if ((t = levelTime(HIGH)) < 50) {
        return simpleDHTCombileError(t, SimpleDHTErrStartHigh);
    }

    // DHT11 data transmite:
    //    1. T(LOW), 1bit start, PULL LOW 50us(48-55us).
    //    2. T(H0), PULL HIGH 26us(22-30us), bit(0)
    //    3. T(H1), PULL HIGH 70us(68-75us), bit(1)
    for (int j = 0; j < 40; j++) {
          t = levelTime(LOW);          // 1.
          if (t < 24) {                    // specs says: 50us
              return simpleDHTCombileError(t, SimpleDHTErrDataLow);
          }

          // read a bit
          t = levelTime(HIGH);              // 2.
          if (t < 11) {                     // specs say: 26us
              return simpleDHTCombileError(t, SimpleDHTErrDataRead);
          }
          data[ j ] = (t > 40 ? 1 : 0);     // specs: 22-30us -> 0, 70us -> 1
    }

    // DHT11 EOF:
    //    1. T(en), PULL LOW 50us(45-55us).
    t = levelTime(LOW);
    if (t < 24) {
        return simpleDHTCombileError(t, SimpleDHTErrDataEOF);
    }

    return SimpleDHTErrSuccess;
}
