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

// High 8bits are time duration.
// Low 8bits are error code.
// For example, 0x0310 means t=0x03 and code=0x10,
// which is start low signal(0x10) error.
// @see https://github.com/winlinvip/SimpleDHT/issues/25
#define simpleDHTCombileError(t, err) ((t << 8) & 0xff00) | (err & 0x00ff)

// Get the time duration from error.
#define SimpleDHTErrDuration(err) ((err&0xff00)>>8)
// Get the error code defined bellow.
#define SimpleDHTErrCode(err) (err&0x00ff)

// Success.
#define SimpleDHTErrSuccess 0
// Error to wait for start low signal.
#define SimpleDHTErrStartLow 16
// Error to wait for start high signal.
#define SimpleDHTErrStartHigh 17
// Error to wait for data start low signal.
#define SimpleDHTErrDataLow 18
// Error to wait for data read signal.
#define SimpleDHTErrDataRead 19
// Error to wait for data EOF signal.
#define SimpleDHTErrDataEOF 20
// Error to validate the checksum.
#define SimpleDHTErrDataChecksum 21
// Error when temperature and humidity are zero, it shouldn't happen.
#define SimpleDHTErrZeroSamples 22
// Error when pin is not initialized.
#define SimpleDHTErrNoPin 23
// Error when pin mode is invalid.
#define SimpleDHTErrPinMode 24

class SimpleDHT {
protected:
    long levelTimeout = 500000; // 500ms
    int pin = -1;
    uint8_t pinInputMode = INPUT;
#ifdef __AVR
    // For direct GPIO access (8-bit AVRs only), store port and bitmask
    // of the digital pin connected to the DHT.
    // (other platforms use digitalRead(), do not need this)
    uint8_t bitmask = 0xFF;
    uint8_t port    = 0xFF;
#endif
public:
    SimpleDHT();
    SimpleDHT(int pin);
public:
    // To (eventually) change the pin configuration for existing instance
    // @param pin The DHT11 or DHT22 pin.
    virtual void setPin(int pin);
    // Set the input mode of the pin from INPUT and INPUT_PULLUP
    // to permit the use of the internal pullup resistor for
    // for bare modules
    // @param mode the pin input mode.
    // @return SimpleDHTErrSuccess is success; otherwise, failed.
    virtual int setPinInputMode(uint8_t mode);
public:
    // Read from dht11 or dht22.
    // @param pin The DHT11 pin.
    // @param ptemperature output, NULL to igore. In Celsius.
    // @param phumidity output, NULL to ignore.
    //      For DHT11, in H, such as 35H.
    //      For DHT22, in RH%, such as 53%RH.
    // @param pdata output 40bits sample, NULL to ignore.
    // @remark the min delay for this method is 1s(DHT11) or 2s(DHT22).
    // @return SimpleDHTErrSuccess is success; otherwise, failed.
    virtual int read(byte* ptemperature, byte* phumidity, byte pdata[40]);
    virtual int read(int pin, byte* ptemperature, byte* phumidity, byte pdata[40]);
    // To get a more accurate data.
    // @remark it's available for dht22. for dht11, it's the same of read().
    virtual int read2(float* ptemperature, float* phumidity, byte pdata[40]) = 0;
    virtual int read2(int pin, float* ptemperature, float* phumidity, byte pdata[40]) = 0;
protected:
    // For only AVR - methods returning low level conf. of the pin
#ifdef __AVR
    // @return Bitmask to access pin state from port input register
    virtual int getBitmask();
    // @return Bitmask to access pin state from port input register
    virtual int getPort();
#endif
protected:
    // Measure and return time (in microseconds)
    // with precision defined by interval between checking the state
    // while pin is in specified state (HIGH or LOW)
    // @param level    state which time is measured.
    // @param interval time interval between consecutive state checks.
    // @return measured time (microseconds). -1 if timeout.
    virtual long levelTime(byte level, int firstWait = 10, int interval = 6);
    // @data the bits of a byte.
    // @remark please use simple_dht11_read().
    virtual byte bits2byte(byte data[8]);
    // read temperature and humidity from dht11.
    // @param data a byte[40] to read bits to 5bytes.
    // @return 0 success; otherwise, error.
    // @remark please use simple_dht11_read().
    virtual int sample(byte data[40]) = 0;
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
    SimpleDHT11();
    SimpleDHT11(int pin);
public:
    virtual int read2(float* ptemperature, float* phumidity, byte pdata[40]);
    virtual int read2(int pin, float* ptemperature, float* phumidity, byte pdata[40]);
protected:
    virtual int sample(byte data[40]);
};

/*
    Simple DHT22

    Simple, Stable and Fast DHT22 library.

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
    SimpleDHT22();
    SimpleDHT22(int pin);
public:
    virtual int read2(float* ptemperature, float* phumidity, byte pdata[40]);
    virtual int read2(int pin, float* ptemperature, float* phumidity, byte pdata[40]);
protected:
    virtual int sample(byte data[40]);
};

#endif
