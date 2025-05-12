# Ethernet Temperature Logger with ThingSpeak Integration

This Arduino-based project reads temperature data from a sensor, calculates the values in both Celsius and Fahrenheit, and uploads the results to [ThingSpeak](https://thingspeak.com/) using an Ethernet connection. A button press allows users to choose which temperature format to send to ThingSpeak.

---

## 📋 Features
- 📡 Ethernet connectivity using the W5100 Ethernet Shield
- 🌡️ Temperature reading using an analog sensor
- 📈 Data logging to ThingSpeak Cloud
- 🔘 Button to toggle between Celsius and Fahrenheit reporting
- 🖨️ Serial output for real-time temperature monitoring

---

## 🛠️ Hardware Components
- Arduino Board (Uno, Mega, etc.)
- W5100 Ethernet Shield
- Temperature Sensor (e.g., Thermistor or TMP36)
- Push Button
- Resistors and Jumper Wires
- MicroSD Card (Optional, for expansion)

---

## 📦 Libraries Used
- [Ethernet](https://www.arduino.cc/en/Reference/Ethernet)
- [ThingSpeak](https://github.com/mathworks/thingspeak-arduino)

---

## 🔌 Pin Configuration

| Component       | Pin        |
|-----------------|------------|
| Temperature Sensor | A0 (Analog Pin 0) |
| Button           | Digital Pin 8 |
| Ethernet Shield  | SPI Pins (CS on Pin 10) |
| SD Card (Optional) | CS on Pin 4  |

---

## 📖 Code Overview

- Reads analog temperature sensor value.
- Converts reading to Celsius and Fahrenheit using the Steinhart-Hart equation.
- Sends temperature data to ThingSpeak fields:
    - Field 1: Fahrenheit
    - Field 2: Celsius
    - Field 3: Conditional (C or F based on button state)
- Maintains Ethernet connection and retries if disconnected.

---

## 🚀 How to Use

1. Clone or download this repository.
2. Open the Arduino sketch in the Arduino IDE.
3. Add a `secrets.h` file in the same directory with your ThingSpeak credentials:

```cpp
#define SECRET_CH_ID  YOUR_CHANNEL_ID
#define SECRET_WRITE_APIKEY  "YOUR_API_KEY"
