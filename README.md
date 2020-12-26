# ESP32 - IOT2TANGLE

**ESP32** is one of the microcontrollers for *IoT applications* par excellence. Created and manufactured by *Espressif*, it is widely used for both educational and industrial development due to its great versatility, reliability and low cost. At *I2T* we wanted to add it due to its extensive use in the development community.

In this repository you will find explanations and step by step for the development of a system that every certain time interval (which you will set) will collect data from 5 sensors (including internal sensor), this data package will be sent to a special gateway designed by *IOT2TANGLE* that you will have on the local network. This gateway will be in charge of adding these packages to **Tangle Network of IOTA**, through *Streams*.

## I2T Sensors Stack

*IOT2TANGLE* provides with code to integrate the *ESP32* and a give set of generic sensors (I2T sensor's stack). These are just suggested sensors and you can always add some other peripherals required by your project, however the sensors listed here are fully compatible and will be automatically detected when you connect them.

**It is not necessary to have all the sensors listed here**, the code is able to detect which sensors were connected. In the case of not connecting any sensor, the only real data that will be displayed on the Tangle will be the **Internal Temperature** of ESP32.

This is the list of Sensors/Modules that you can connect and it will be recognized immediately:
- ***BME280*** (Bosch) - Temperature, Humidity and Pressure sensor.
- ***MPU6050*** (InvenSense-TDK) - Acelerometer and Gyroscope 6-axis.
- ***BH1750*** (ROHM) - Ambient Light Sensor.
- ***Generic Adjustable Sound Sensor with digital output*** (like *KY038 Module*)
- Also, you can connect a ***Green LED*** that blink when the data is sent to the Tangle, and a ***Red LED*** that will Blink in a certain way when it detects certain errors (totally optional).

## Available connectivity
- **[HTTP-sender](https://github.com/iot2tangle/ESP32/tree/main/http-sender)** -- ESP32 will send the sensors data through HTTP to **[I2T HTTP Gateway](https://github.com/iot2tangle/Streams-http-gateway)** or **[Keepy](https://github.com/iot2tangle/Keepy)**
- **[HTTP-receiver](https://github.com/iot2tangle/ESP32/tree/main/http-receiver)** -- ESP32 will receive the sensors data through HTTP from **[Keepy](https://github.com/iot2tangle/Keepy)** and performs actions based on the data received (for now it is optimized only to work with Keepy).
- **[MQTT-sender](https://github.com/iot2tangle/ESP32/tree/main/mqtt-sender)** -- ESP32 will send the sensors data through MQTT to **[I2T MQTT Gateway](https://github.com/iot2tangle/Streams-mqtt-gateway)** or **[Keepy](https://github.com/iot2tangle/Keepy)**
