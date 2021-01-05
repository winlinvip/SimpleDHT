# SimpleDHT

## Description

An Arduino library for the DHT series of low-cost temperature/humidity sensors.

You can find DHT11 and DHT22 tutorials [here](https://learn.adafruit.com/dht).

## Installation

### First Method

![image](https://user-images.githubusercontent.com/36513474/68069796-09e62200-fd87-11e9-81e0-dc75e38efed0.png)

1. In the Arduino IDE, navigate to Sketch > Include Library > Manage Libraries
1. Then the Library Manager will open and you will find a list of libraries that are already installed or ready for installation.
1. Then search for SimpleDHT using the search bar.
1. Click on the text area and then select the specific version and install it.

### Second Method

1. Navigate to the [Releases page](https://github.com/winlinvip/SimpleDHT/releases).
1. Download the latest release.
1. Extract the zip file
1. In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library

## Usage

To use this library:

1. Open example: Arduino => File => Examples => SimpleDHT => DHT11Default
1. Connect the DHT11 and upload the program to Arduino.
1. Open the Serial Window of Arduino IDE, we got the result as follows.

```Cpp
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

## Features

- ### Simple

    Simple C++ code with lots of comments.

- ### Stable

    Strictly follow the standard DHT protocol.

- ### Fast

    Support 0.5HZ(DHT22) or 1HZ(DHT11) sampling rate.

- ### Compatible

    SimpleDHT sensor library is compatible with multiple low-cost temperatures and humidity sensors like DHT11 and DHT22. A few examples are implemented just to demonstrate how to modify the code for different sensors.

- ### MIT License

    DHT sensor library is open-source and uses one of the most permissive licenses so you can use it on any project.

  - Commercial use
  - Modification
  - Distribution
  - Private use

## Functions

- read()
- setPinInputMode()
- setPin()
- getBitmask()
- getPort()
- levelTime()
- bits2byte()
- parse()
- read2()
- sample()

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

One of the SimpleDHT examples is the following:

- ### DHT22Integer

```Cpp
#include <SimpleDHT.h>

int pinDHT22 = 2;
SimpleDHT22 dht22(pinDHT22);

void setup() {
  Serial.begin(115200);
}

void loop() {

  Serial.println("=================================");
  Serial.println("Sample DHT22...");

  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(2000);
    return;
  }

  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" RH%");

  delay(2500);
}
```

## Links

1. [adafruit/DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)
1. [Arduino #4469: Add SimpleDHT library.](https://github.com/arduino/Arduino/issues/4469)
1. [DHT11 datasheet and protocol.](https://akizukidenshi.com/download/ds/aosong/DHT11.pdf)
1. [DHT22 datasheet and protoocl.](http://akizukidenshi.com/download/ds/aosong/AM2302.pdf)

Winlin 2016.1

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell others about this library
- Contribute new protocols

Please read [CONTRIBUTING.md](https://github.com/winlinvip/SimpleDHT/blob/master/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Credits

The author and maintainer of this library is Winlin <winlin@vip.126.com>.

Based on previous work by:

- t-w
- O. Santos
- P. H. Dabrowski
- per1234
- P. Rinn
- G. M. Vacondio
- D. Faust
- C. Stroie
- Samlof
- Agha Saad Fraz

## License

This library is licensed under [MIT](https://github.com/winlinvip/SimpleDHT/blob/master/LICENSE).
