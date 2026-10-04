# ESP32 Live Distance Dashboard

This project uses ESP32 and an HC-SR04 ultrasonic sensor to measure distance.

## Components

- ESP32
- HC-SR04 Ultrasonic Sensor

## Pin Connections

HC-SR04 → ESP32

VCC → 5V
TRIG → GPIO 5
ECHO → GPIO 18
GND → GND

## Features

- Measures distance
- Connects to WiFi
- ESP32 web server
- Live distance dashboard
- Serial Monitor output

## Working

The HC-SR04 sensor measures the distance.
The ESP32 displays the distance on a web page.
The dashboard automatically refreshes every 1 second.

## Author

SELVASH

## Wokwi Simulation

https://wokwi.com/projects/476927786616947713
