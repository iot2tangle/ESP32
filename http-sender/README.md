# ESP32 with I2T Sensors Stack  --  HTTP Protocol

ESP32 is one of the microcontrollers for *IoT applications* par excellence. It is widely used for both educational and industrial development due to its great versatility, reliability and low cost. At *I2T* we wanted to add it due to its extensive use in the development community.

# Setting up your ESP32 with the I2T Sensors Stack

This is the list of Sensors/Modules that you can connect and it will be recognized immediately.
- ***BME280*** (*Bosch*) - Temperature, Humidity and Pressure sensor. -> Connected by *I2C Bus* via: *GPIO33/SDA* and *GPIO32/SCL* --- Be careful with the supply of this sensor, the BM280 is powered with 3.3V, if your module does not have a voltage regulator (some modules do not have it) the sensor can be damaged if you supply 5V.
- ***MPU6050*** (*InvenSense-TDK*) - Acelerometer and Gyroscope 6-axis. -> Connected by *I2C Bus* via: *GPIO33/SDA* and *GPIO32/SCL*.
- ***BH1750*** (*ROHM*) - Ambient Light Sensor. -> Connected by *I2C Bus* via: *GPIO33/SDA* and *GPIO32/SCL*.
- ***Generic Adjustable Sound Sensor with digital output*** (like *KY038 Module*) - -> Digital Signal on *GPIO21*, *GPIO22* to GND (to enable sound data collection).
- Also, you can connect a ***Green LED*** in *GPIO2* that blink when the data is sent to the Tangle, and a ***Red LED*** in *GPIO15* that will Blink in a certain way when it detects certain errors (totally optional)

## Connecting the sensors

The following diagram explains how each sensor of our stack must be connected to the ESP32 pins. The "NodeMCU-32s" development board has been used in this diagram, which contains the ESP32 microcontroller. However, any development board that contains the ESP32 microcontroller can be used.

![I2T Sensors Stack on ESP32](https://iot2tangle.io/assets/screenshots/ESP32-I2T.png)

**It is not necessary to have all the sensors listed here**, the code is able to detect which sensors were connected. In the case of not connecting any sensor, the only real data that will be displayed on the Tangle will be the Internal Temperature of *ESP32*.

***IMPORTANT NOTE:*** *Espressif has deprecated the ESP32's internal temperature sensor a few years ago, as it has proven not to be a very accurate measurement. However we will use it as a minimum unit of information to be able to send data to the Tangle without having sensors connected. Please keep this in mind, so this value should not be taken into account for critical applications.*

# Download Firmware on ESP32
This repository uses the ***Iot2Tangle C Core devices*** adapted for ***ESP32-FreeRTOS*** offered in the official *Espressif Toolchain ESP-IDF SDK*. Once the SDK is installed you will have all the tools to compile and download the program on your ESP32.


## 1) Install ESP-IDF SDK:
### Windows:
The easiest way to install ESP-IDF and their prerequisites is to download the ESP-IDF Tools installer from this URL:
<https://dl.espressif.com/dl/esp-idf-tools-setup-2.3.exe>

Just follow the steps and you will have the official *Espressif SDK Toolchain* installed on your computer.

To check other methods, the following page is suggested: 
<https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/windows-setup.html>

### Linux and macOS:
Prerequisites of ESP-IDF SDK:
```
sudo apt update
sudo apt install git wget flex bison gperf python python-pip python-setuptools cmake ninja-build ccache libffi-dev libssl-dev
```
It is recommended to install the stable version: ESP-IDF v4.1, you can download it from here:
```
git clone -b v4.1 --recursive https://github.com/espressif/esp-idf.git
```
Now install the SDK, this may take a while:
```
cd ~/esp-idf
./install.sh
. ./export.sh
```
After doing this last step do not close the shell, as we will compile and flash from here. If you close the shell you will have to do the previous step again.

## 2) Download the Iot2Tangle ESP32 Repository and go to the 'http-sender' folder:
You can download the repository directly from Github, or from shell or Command Prompt with the following command:
```
git clone https://github.com/iot2tangle/ESP32.git
cd ESP32/http-sender
```
## 3) Edit the file config.h
The *config.h* file must be opened and modified, this file is in the directory *'ESP32/http-sender/main'* of the repository.

This step is very important if you want to make a connection to the gateway. Your *WiFi Credentials*, the *address* and *port* that will have the *I2T Streams HTTP Gateway* or *Keepy* running, the *Device Id*, and others configurations. The *Id Name Device* you define here must be between the devices you set in on the *Gateway configuration file*. 
```
const char* id_name = "ESP32-HTTP";

/* Network Configuration */
const char* ssid_WiFi = "mySSID";
const char* pass_WiFi = "myPASS";

/* HTTP Endpoint Configuration */
const char* address = "192.168.1.131/sensor_data";    /* Endpoint address (HTTP), must NOT include 'http://xxx' or 'tcp://xxx' */
int port = 8080;

/* Enable Sensors */
bool isEnable_TemperatureIntern = true;
bool isEnable_TemperatureExtern = true;	   /* true: Enable  --  false: Disable */
bool isEnable_Humidity = true;
...

/* Interval of time */
long interval = 30;    /* Time in seconds between */
```
## 4) Compile and Download the Firmware:
Remembering to have the ***ESP-IDF Toolchain*** open, and you make sure you are at the root of the *http-sender* folder run the following command:
```
idf.py build
```
If the compilation was correct it should read: *Project build complete*.

Now make sure you have ESP32 connected to your computer, and know what COM port it is connected to. (You can see this in 'Device Manager'). 

Then run the following command that will start flashing the firmware. (You will probably have to press the reset button on your ESP32 development board, even several times for it to recognize the board.)
```
idf.py -p COM1 flash    # COM1 is an Windows port example, you must put your port. In Linux /dev/ttyUSB0 is an example, and in macOS: '/dev/cu' 
```

Upon completion, the firmware is downloaded to your ESP32. If the *I2T Streams HTTP Gateway* is configured correctly (we will explain this next), ***you will be sending data to Tangle via Streams***.

# Debugging
If configured correctly, *ESP32* should be sending data to the gateway automatically. However, you may want to verify that it is running on *ESP32*.

The code continuously sends information out the **serial port**, so it can read the serial port to see what is happening and detect errors.

You can use the 'Arduino Serial Monitor' for this, but we recommend using the following software:
## Windows:
Open *Command Prompt*.

Configure the Baud Rate of the port to 115200 bps:
```
mode COM1: baud=115200
```
Read the serial port:
```
copy COM1: con:
```
## Linux and macOS:
Install *cu Monitor*. It is an excellent shell monitor and very useful.
```
sudo apt install cu
```
Run *cu Monitor*:
```
cu -l /dev/ttyUSB0 -s 115200
```


The following screenshot is a reading of the *Serial Port*, you should see something like this:

![Raspberry with BME280 sending data to the Tangle](https://i.postimg.cc/cH6TWpXP/Screenshot-from-2020-10-16-11-33-05.png)


# Setting up the Streams HTTP Gateway

## Preparation

Install Rust if you don't have it already. More info about Rust here https://www.rust-lang.org/tools/install

```
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

Make sure you also have the build dependencies installed, if not run:  

```
sudo apt update
sudo apt install build-essential pkg-config libssl-dev  
```

## Installing the Streams Gateway
Get the Streams Gateway repository
https://github.com/iot2tangle/Streams-http-gateway

```
git clone https://github.com/iot2tangle/Streams-http-gateway
```

Navigate to the root of **Streams-http-gateway** directory and edit the **config.json** file to define yours *device names*, *endpoint*, *port*, you can also change the IOTA Full Node used, among others.

## Start the Streams Server

### Sending messages to the Tangle

Run the Streams Gateway:  

```
cargo run --release  
```
This will compile and start the *Streams HTTP Gateway*. Note that the compilation process may take from 3 to 25 minutes (Pi3 took us around 15/25 mins, Pi4 8 mins and VPS or desktop machines will generally compile under the 5 mins) depending on the device you are using as host.
You will only go through the compilation process once and any restart done later will take a few seconds to have the Gateway working.

Once started, the ***Channel Id*** will be displayed, and the gateway will be open waiting for data to send to the Tangle.

![Streams Gateway receiving data](https://i.postimg.cc/zfz0tbWz/Screenshot-from-2020-10-16-11-44-59.png)
*The Channel Id that will allow subscribers to access the channel data.*

### Reading messages from the Tangle

You can read the received messages directly from the **I2T Explorer**: https://explorer.iot2tangle.io/ using the Channel Id printed by the Gateway in shell.   

![I2T Explorer](https://i.postimg.cc/wTNf7dgp/Screenshot-from-2020-10-16-11-46-16.png)


*For inquiries, improvements or errors detected, please start an issue in this repository.*
