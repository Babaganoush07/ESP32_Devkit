# DOIT ESP32 DEVKIT V1


## Table of Contents
* [General Info](#general-information)
* [Pinout](#pinout)
* [Setup](#setup)


## General Information
- The ESP32 is dual core, this means it has 2 processors.
- It has Wi-Fi and bluetooth built-in.
- It runs 32 bit programs.
- The clock frequency can go up to 240MHz and it has a 512 kB RAM.
- This particular board has 36 pins, 18 in each row.
- It also has wide variety of peripherals available, like: capacitive touch, ADCs, DACs, UART, SPI, I2C and much more.
- It comes with built-in hall effect sensor and built-in temperature sensor.


## Technologies Used
- [Adruino 1.8.19](https://www.arduino.cc/en/software)


## Pinout
-![ESP32-Pinout](https://user-images.githubusercontent.com/94538153/223725777-4693c948-2b97-420d-b9cb-a7c165306482.png)


## Setup
- Purchasing a Devkit: [Amazon](https://www.amazon.com/ESP32-WROOM-32-Development-ESP-32S-Bluetooth-Arduino/dp/B084KWNMM4)
- In Arduino IDE Preferences, in the Additional Boards Manager URLs textbox enter

`https://dl.espressif.com/dl/package_esp32_index.json`


- Select the board: Tools -> Boards Manager and search `ESP32`. Select the `ESP32 by Espressif Systems`.
