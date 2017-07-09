# SimpleDHT

Simple, Stable and Fast Arduino Temp & Humidity Sensors for 
[DHT11 and DHT22](http://learn.adafruit.com/dht).

1. Simple: Simple C++ code with lots of comments.
1. Stable: Strictly follow the standard DHT protocol.
1. Fast: Support 0.5HZ(DHT22) or 1HZ(DHT11) sampling rate.

## Usage

To use this library:

1. Download the zip from specified version: https://github.com/winlinvip/SimpleDHT/releases
2. Import to Arduino: Arduino => Sketch => Include Library => Add .ZIP Library...
3. Open example: Arduino => File => Examples => SimpleDHT => DHT11Default
4. Connect the DHT11 and Upload program to Arduino.
5. Open the Serial Window of Arduino IDE, we got the result as following.

```
=================================
Sample DHT11...
Sample OK: 19 *C, 31 H
=================================
Sample DHT11...
Sample OK: 19 *C, 31 H
=================================
```

> Remark: For DHT11, no more than 1 Hz sampling rate (once every second).

> Remark: For DHT22, no more than 0.5 Hz sampling rate (once every 2 seconds).

## Sensors

- [x] DHT11, The [product](https://www.adafruit.com/product/386), [datasheet](https://akizukidenshi.com/download/ds/aosong/DHT11.pdf) and [example](https://github.com/winlinvip/SimpleDHT/tree/master/examples/DHT11Default), 1HZ sampling rate.
- [x] DHT22, The [product](https://www.adafruit.com/product/385), [datasheet](http://akizukidenshi.com/download/ds/aosong/AM2302.pdf) and [example](https://github.com/winlinvip/SimpleDHT/tree/master/examples/DHT22Default), 0.5Hz sampling rate.

## Examples

This library including the following examples:

1. [DHT11Default](https://github.com/winlinvip/SimpleDHT/tree/master/examples/DHT11Default): Use DHT11 to sample.
1. [DHT11WithRawBits](https://github.com/winlinvip/SimpleDHT/tree/master/examples/DHT11WithRawBits): Use DHT11 to sample and get the 40bits RAW data.
1. [DHT11ErrCount](https://github.com/winlinvip/SimpleDHT/tree/master/examples/DHT11ErrCount): Use DHT11 to sample and stat the success rate.
1. [DHT22Default](https://github.com/winlinvip/SimpleDHT/tree/master/examples/DHT22Default): Use DHT22 to sample.
1. [DHT22WithRawBits](https://github.com/winlinvip/SimpleDHT/tree/master/examples/DHT22WithRawBits): Use DHT22 to sample and get the 40bits RAW data.
1. [DHT22Integer](https://github.com/winlinvip/SimpleDHT/tree/master/examples/DHT22Integer): Use DHT22 to sample and ignore the fractional data.
1. [DHT22ErrCount](https://github.com/winlinvip/SimpleDHT/tree/master/examples/DHT22ErrCount): Use DHT22 to sample and stat the success rate.
1. [TwoSensorsDefault](https://github.com/winlinvip/SimpleDHT/tree/master/examples/TwoSensorsDefault): Use two DHT11 to sample.

## Links

1. [adafruit/DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)
1. [Arduino #4469: Add SimpleDHT library.](https://github.com/arduino/Arduino/issues/4469)
1. [DHT11 datasheet and protocol.](https://akizukidenshi.com/download/ds/aosong/DHT11.pdf)
1. [DHT22 datasheet and protoocl.](http://akizukidenshi.com/download/ds/aosong/AM2302.pdf)

Winlin 2016.1
