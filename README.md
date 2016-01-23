# simple-dht

Simple, Stable and Fast Arduino Temp & Humidity Sensors for [DHT11 etc](http://www.ladyada.net/learn/sensors/dht.html).

1. Simple: Simple pure C code with lots of comments.
1. Stable: Strictly follow the standard DHT protocol.
1. Fast: Supports fast sample every 200ms+.

## Usage

To use this library:

1. Download the zip from specified version: https://github.com/winlinvip/simple-dht/releases
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

> Remark: We can sample the DHT11 every 200ms+.

## Examples

This library including the following examples:

1. DHT11Default: To sample the temperature and humidity every 200ms.
1. DHT11WithRawBits: To sample the temperature and humidity, output the 40 raw bits every 200ms.


## Similar Projects

1. [adafruit/DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)
1. [Arduino #4469: Add SimpleDHT library.](https://github.com/arduino/Arduino/issues/4469)

Winlin 2016.1