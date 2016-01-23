# SimpleDHT

Simple, Stable and Fast Arduino Temp & Humidity Sensors for 
[DHT11 etc](http://learn.adafruit.com/dht).

1. Simple: Simple C++ code with lots of comments.
1. Stable: Strictly follow the standard DHT protocol.
1. Fast: Support 0.5HZ or 1HZ sampling rate.

## Usage

To use this library:

1. Download the zip from specified version: https://github.com/winlinvip/SimpleDHT/releases
2. Import to Arduino: Arduino => Sketch => Include Library => Add .ZIP Library...
3. Open example: Arduino => File => Examples => Simple DHT sensor library => DHT11Default
4. Connect the DHT11 and Upload program to Arduino.
5. Open the Serial Window of Arduino IDE, we got the result as following.

```
=================================
Sample DHT11...
Sample OK: 19 *C, 31 %
=================================
Sample DHT11...
Sample OK: 19 *C, 31 %
=================================
```

> Remark: For DHT11, no more than 1 Hz sampling rate (once every second).

## Examples

This library including the following examples:

1. DHT11Default: To sample the temperature and humidity.
1. DHT11WithRawBits: To sample the temperature and humidity, output the 40 raw bits.


## Links

1. [adafruit/DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)
1. [Arduino #4469: Add SimpleDHT library.](https://github.com/arduino/Arduino/issues/4469)

Winlin 2016.1