# Helmet Crash Detection and Emergency Alert System

## About the Project

An IoT-based helmet crash detection prototype that uses an MPU6050 accelerometer and LoRa wireless communication to detect potential crashes and transmit emergency alerts to a base station.

## Hardware Components

* ESP32 development boards
* MPU6050 accelerometer and gyroscope
* LoRa transmitter and receiver modules
* GPS module
* Power supply and supporting electronic components

## How It Works

1. The MPU6050 measures acceleration.
2. The transmitter calculates the acceleration magnitude.
3. When the configured threshold is exceeded, an emergency message is generated.
4. LoRa transmits the alert to the receiver.
5. The receiver displays the emergency message in the Serial Monitor.

## Project Files

* `helmet_transmitter.ino` — Helmet transmitter code
* `base_station_receiver.ino` — Base station receiver code
* `helmet_system.jpeg` — Project photograph
* `transmitter_hardware.jpeg` — Hardware photograph
* `hardware_setup.jpeg` — Hardware setup photograph

 Software Requirements

* Arduino IDE
* Adafruit MPU6050 library
* Adafruit Unified Sensor library
* LoRa library

## Current Limitations

The current implementation uses predefined location coordinates rather than live GPS data. The crash-detection threshold is experimental and requires further testing to reduce false alerts. This prototype is not a certified safety device.

## Future Improvements

* Integrate live GPS coordinates
* Add receiver acknowledgement and retransmission
* Improve crash-detection reliability
* Add emergency notifications
