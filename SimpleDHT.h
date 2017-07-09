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

#ifndef __SIMPLE_DHT_H
#define __SIMPLE_DHT_H

#include <Arduino.h>

// Success.
#define SimpleDHTErrSuccess 0
// Error to wait for start low signal.
#define SimpleDHTErrStartLow 100
// Error to wait for start high signal.
#define SimpleDHTErrStartHigh 101
// Error to wait for data start low signal.
#define SimpleDHTErrDataLow 102
// Error to wait for data read signal.
#define SimpleDHTErrDataRead 103
// Error to wait for data EOF signal.
#define SimpleDHTErrDataEOF 104
// Error to validate the checksum.
#define SimpleDHTErrDataChecksum 105
// Error when temperature and humidity are zero, it shouldn't happen.
#define SimpleDHTErrZeroSamples 106

class SimpleDHT {
public:
    // to read from dht11 or dht22.
    // @param pin the DHT11 pin.
    // @param ptemperature output, NULL to igore. In Celsius.
    // @param phumidity output, NULL to ignore.
    //      For DHT11, in H, such as 35H.
    //      For DHT22, in RH%, such as 53%RH.
    // @param pdata output 40bits sample, NULL to ignore.
    // @remark the min delay for this method is 1s(DHT11) or 2s(DHT22).
    // @return SimpleDHTErrSuccess is success; otherwise, failed.
    virtual int read(int pin, byte* ptemperature, byte* phumidity, byte pdata[40]);
    // to get a more accurate data.
    // @remark it's available for dht22. for dht11, it's the same of read().
    virtual int read2(int pin, float* ptemperature, float* phumidity, byte pdata[40]) = 0;
protected:
    // confirm the OUTPUT is level in us, 
    // for example, when DHT11 start sample, it will
    //    1. PULL LOW 80us, call confirm(pin, 80, LOW)
    //    2. PULL HIGH 80us, call confirm(pin, 80, HIGH)
    // @return 0 success; oterwise, error.
    // @remark should never used to read bits, 
    //    for function call use more time, maybe never got bit0.
    // @remark please use simple_dht11_read().
    virtual int confirm(int pin, int us, byte level);
    // @data the bits of a byte.
    // @remark please use simple_dht11_read().
    virtual byte bits2byte(byte data[8]);
    // read temperature and humidity from dht11.
    // @param pin the pin for DHT11, for example, 2.
    // @param data a byte[40] to read bits to 5bytes.
    // @return 0 success; otherwise, error.
    // @remark please use simple_dht11_read().
    virtual int sample(int pin, byte data[40]) = 0;
    // parse the 40bits data to temperature and humidity.
    // @remark please use simple_dht11_read().
    virtual int parse(byte data[40], short* ptemperature, short* phumidity);
};

/*
    Simple DHT11

    Simple, Stable and Fast DHT11 library.

    The circuit:
    * VCC: 5V or 3V
    * GND: GND
    * DATA: Digital ping, for instance 2.

    23 Jan 2016 By winlin <winlin@vip.126.com>

    https://github.com/winlinvip/SimpleDHT#usage
    https://akizukidenshi.com/download/ds/aosong/DHT11.pdf
    https://cdn-shop.adafruit.com/datasheets/DHT11-chinese.pdf

*/
class SimpleDHT11 : public SimpleDHT {
public:
    virtual int read2(int pin, float* ptemperature, float* phumidity, byte pdata[40]);
protected:
    virtual int sample(int pin, byte data[40]);
};

/*
    Simple DHT11

    Simple, Stable and Fast DHT11 library.

    The circuit:
    * VCC: 5V or 3V
    * GND: GND
    * DATA: Digital ping, for instance 2.

    3 Jun 2017 By winlin <winlin@vip.126.com>

    https://github.com/winlinvip/SimpleDHT#usage
    http://akizukidenshi.com/download/ds/aosong/AM2302.pdf
    https://cdn-shop.adafruit.com/datasheets/DHT22.pdf

*/
class SimpleDHT22 : public SimpleDHT {
public:
    virtual int read2(int pin, float* ptemperature, float* phumidity, byte pdata[40]);
protected:
    virtual int sample(int pin, byte data[40]);
};

#endif
