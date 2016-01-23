# simple-dht

Simple Arduino library for DHT11, etc Temp &amp; Humidity Sensors http://www.ladyada.net/learn/sensors/dht.html

Supports Fast Sample(about 200ms interval).

## Usage

To use this library:

1. Download the zip: https://github.com/winlinvip/simple-dht/archive/master.zip
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

Winlin 2016.1