# ESP8266 Losant IoT Platform - DHT22 and Photoresistor

This project demonstrates the use of an ESP8266 microcontroller with the Losant IoT platform to monitor environmental data. The device measures temperature and humidity using a DHT22 sensor and light intensity using a photoresistor, and sends this data to Losant for visualization and monitoring.

## Features
- **Temperature and Humidity Monitoring**: Uses a DHT22 sensor to gather temperature (in Celsius and Fahrenheit) and humidity data.
- **Light Intensity Monitoring**: Reads light levels using a photoresistor connected to the ESP8266.
- **IoT Connectivity with Losant**: Sends the sensor data to Losant's IoT platform for real-time data visualization and monitoring.

## Requirements
### Hardware
- ESP8266 board (e.g., NodeMCU)
- DHT22 sensor
- Photoresistor
- Resistor (10kΩ for photoresistor, if needed)
- Jumper wires

### Software
- [Arduino IDE](https://www.arduino.cc/en/software)
- [Losant Library](https://github.com/Losant/losant-mqtt-arduino) for connecting to Losant IoT platform
- [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library) for reading data from the DHT22

## Circuit Diagram
1. **DHT22 Sensor**:
   - Connect the DHT22 **Data Pin** to **D7 (GPIO 5)** on the ESP8266.
   - Connect **VCC** to **3.3V** on the ESP8266.
   - Connect **GND** to **GND** on the ESP8266.

2. **Photoresistor**:
   - Connect one leg of the photoresistor to **A0** on the ESP8266.
   - Connect the other leg of the photoresistor to **3.3V**.
   - (Optional) Place a 10kΩ resistor between A0 and GND for better accuracy.

## Setup Instructions

1. **Install Libraries**: In Arduino IDE, install the following libraries:
   - **DHT Sensor Library** by Adafruit
   - **Losant Library**

2. **Update WiFi Credentials**: Replace `WIFI_SSID` and `WIFI_PASSWORD` with your WiFi credentials:
   ```cpp
   const char* WIFI_SSID = "Your_SSID";
   const char* WIFI_PASSWORD = "Your_PASSWORD";
   ```

3. **Add Losant Device Credentials**: Replace `LOSANT_DEVICE_ID`, `LOSANT_ACCESS_KEY`, and `LOSANT_ACCESS_SECRET` with your Losant device credentials:
   ```cpp
   const char* LOSANT_DEVICE_ID = "Your_Device_ID";
   const char* LOSANT_ACCESS_KEY = "Your_Access_Key";
   const char* LOSANT_ACCESS_SECRET = "Your_Access_Secret";
   ```

4. **Upload Code**: Connect your ESP8266 to your computer and upload the code provided in `main.ino`.

## Code Overview

- **WiFi Connection**: The `connectWiFi()` function connects the ESP8266 to your WiFi network.
- **Losant Connection**: The `connectLosant()` function establishes a connection to the Losant platform.
- **Sensor Data Collection**:
  - **DHT22** sensor measures temperature and humidity.
  - **Photoresistor** measures light intensity.
- **Data Transmission**: The device sends sensor data to Losant using `device.sendState(root)`.
- **Reconnect Logic**: In case of a WiFi or Losant disconnection, the `reconnect()` function re-establishes connections.

## Example Output

The data sent to Losant includes:
- `humidity`: Humidity level from DHT22 sensor.
- `tempC`: Temperature in Celsius.
- `tempF`: Temperature in Fahrenheit.
- `lightIntensity`: Light level from the photoresistor.

## Losant Dashboard

In Losant, you can create a dashboard to visualize:
- **Temperature** (°C or °F)
- **Humidity** (%)
- **Light Intensity**

Use the Losant platform to set up alerts, triggers, and other IoT features based on your device's data.

