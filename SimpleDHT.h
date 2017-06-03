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

#ifndef __SIMPLE_DHT_H
#define __SIMPLE_DHT_H

#include <Arduino.h>

class SimpleDHT {
public:
    // Success.
    static int ErrSuccess;
    // Error to wait for start low signal.
    static int ErrStartLow;
    // Error to wait for start high signal.
    static int ErrStartHigh;
    // Error to wait for data start low signal.
    static int ErrDataLow;
    // Error to wait for data read signal.
    static int ErrDataRead;
    // Error to wait for data EOF signal.
    static int ErrDataEOF;
    // Error to validate the checksum.
    static int ErrDataChecksum;
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
    https://cdn-shop.adafruit.com/datasheets/DHT11-chinese.pdf

*/
class SimpleDHT11 : public SimpleDHT {
public:
    // to read from dht11.
    // @param pin the DHT11 pin.
    // @param ptemperature output, NULL to igore.
    // @param phumidity output, NULL to ignore.
    // @param pdata output 40bits sample, NULL to ignore.
    // @remark the min delay for this method is 1s.
    // @return SimpleDHT11::ErrSuccess is success; otherwise, failed.
    int read(int pin, byte* ptemperature, byte* phumidity, byte pdata[40]);
protected:
    // confirm the OUTPUT is level in us, 
    // for example, when DHT11 start sample, it will
    //    1. PULL LOW 80us, call confirm(pin, 80, LOW)
    //    2. PULL HIGH 80us, call confirm(pin, 80, HIGH)
    // @return 0 success; oterwise, error.
    // @remark should never used to read bits, 
    //    for function call use more time, maybe never got bit0.
    // @remark please use simple_dht11_read().
    int confirm(int pin, int us, byte level);
    // @data the bits of a byte.
    // @remark please use simple_dht11_read().
    byte bits2byte(byte data[8]);
    // read temperature and humidity from dht11.
    // @param pin the pin for DHT11, for example, 2.
    // @param data a byte[40] to read bits to 5bytes.
    // @return 0 success; otherwise, error.
    // @remark please use simple_dht11_read().
    virtual int sample(int pin, byte data[40]);
    // parse the 40bits data to temperature and humidity.
    // @remark please use simple_dht11_read().
    int parse(byte data[40], byte* ptemperature, byte* phumidity);
};

#endif
