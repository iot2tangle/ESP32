# ESP32 I2T Receiver --  HTTP Protocol

This code will allow you to ***collect information/data from the Tangle (Streams Channel)*** that was or is being sent from a *sending device* and then ***decode the json data*** and *save it in variables*. This will allow you to ***execute actions according to the data*** that you are "sensing" in the *sending device*.

**Currently the code is optimized to work by requesting data to *Keepy*.** <https://github.com/iot2tangle/Keepy>

A simple example to illustrate the idea: *Your sending device measures ambient temperature in your garden, and sends that data to Tangle, and you will have another device inside your house reading that json data from tangle, and at a certain temperature a relay is activated that turns on the mechanism of closing the windows of your house.*

This is just an example, the code is prepared to receive any type of data and *you will have to write your code for the activation of the outputs/relays according to the conditions you need* (it is not difficult at all and there are very useful examples for it in it code).


# Setting up your ESP32

*4 GPIO ESP32 pins* have been defined for the *outputs*. The *outputs* are **Boolean: 1 or 0 (3.3V or 0V in voltage)**. Any device that takes advantage of these *outputs* can be connected, but without a doubt the ones that bring out the most potential to the application are the ***relays***.

The default *ESP32 Outputs GPIOs* are:
**Output/Relay 1 -> GPIO26  --  Output/Relay 2 -> GPIO27  --  Output/Relay 3 -> GPIO14  --  Output/Relay 4 -> GPIO12**

![ESP32 receiver Hardware connections](https://iot2tangle.io/assets/screenshots/ESPReceiver.png)

It is quite possible that an external 5V source is needed to power the relays, as development boards generally do not have enough power to power a relay

**IMPORTANT:** The moment you start using Relays is when, ***for your safety, you should pay close attention to their electrical connections***. Whenever you are going to make changes to the connection make sure you have disconnected the AC connector, otherwise there may be a risk of electrocution. The following link from *Panasonic* company has safety tips when handling Relays. [Relays Cautions for Use - Panasonic](https://www3.panasonic.biz/ac/e/control/relay/cautions_use/index.jsp)

# Download Firmware on ESP32
This repository uses the ***Iot2Tangle C Core receiver devices*** adapted for ***ESP32-FreeRTOS*** offered in the official *Espressif Toolchain ESP-IDF SDK*. Once the SDK is installed you will have all the tools to compile and download the program on your ESP32.

Remember that for ESP32 to be taking data **you must have a Keepy instance running on some endpoint that ESP32 can reach**.

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

### 2) Download the Iot2Tangle ESP32 Repository and go to the 'http-receiver' folder:
You can download the repository directly from Github, or from shell or Command Prompt with the following command:
```
git clone https://github.com/iot2tangle/ESP32.git
cd ESP32/http-receiver
```
### 3) Edit the file config.h
The *config.h* file must be opened and modified, this file is in the directory *'ESP32/http/main'* of the repository.

This step is very important if you want to make a connection to the gateway. Your *WiFi Credentials*, the *address* and *port* that will have the *I2T Keepy Host* running, the *Device Id*, and others configurations. The *Id Name Device* you define here must be between the devices you set in on the *Gateway configuration file*. 
```
/* Device */
const char* id_name = "ESP32-Receiver";

/* Network Configuration */
const char* ssid_WiFi = "mySSID";
const char* pass_WiFi = "myPASS";

/* HTTP Endpoint Configuration */
const char* address = "YOUR_KEEPY_HOST/messages/last";  /* Endpoint address (HTTP), must NOT include 'http://xxx' or 'tcp://xxx', and must include '/messages/last' for using in I2T Keepy*/
int port = 3002;

/* Enable Relays */
bool isEnable_Relay_1 = true;
bool isEnable_Relay_2 = true;	/*			true: Enable  --  false: Disable			*/
bool isEnable_Relay_3 = true;
bool isEnable_Relay_4 = true;

/* Interval of time */
long interval = 15;    /* Time in seconds between */
```
### 4) Edit the *'action()' function* of the file *'main/core/lib.c'* to define the actions you want to perform.
For example:
```
float temperature = atof(j->sensor[1].value[0]);  // atof() function converts string to float
printf("Temperature Sensor Example       -> ");
if (temperature > 35.0)   // If temperature is greater than 35 Celsius degrees, Turn on Refrigeration Equipment
{
  set_relay_GPIO(0, 1);  // Put in HIGH RELAY 1
  printf("High Temperature detected: Turning ON the Refrigeration Equipment\n\n");
}
```
### 5) Compile and Download the Firmware:
Remembering to have the ***ESP-IDF Toolchain*** open, and you make sure you are at the root of the *http-receiver* folder run the following command:
```
idf.py build
```
If the compilation was correct it should read: *Project build complete*.

Now make sure you have ESP32 connected to your computer, and know what COM port it is connected to. (You can see this in 'Device Manager'). 

Then run the following command that will start flashing the firmware. (You will probably have to press the reset button on your ESP32 development board, even several times for it to recognize the board.)
```
idf.py -p COM1 flash    # COM1 is an Windows port example, you must put your port. In Linux /dev/ttyUSB0 is an example, and in macOS: '/dev/cu' 
```
Upon completion, the firmware is downloaded to your ESP32. If the *Keepy* is configured correctly ***you will reading data from Tangle via Streams and executing actions from there***.


# Debugging
## Open Serial Monitor
If configured correctly, *ESP32* should be getting data from ***Keepy*** automatically. However, you may want to verify that it is running on *ESP32*.

The code continuously sends information out the **serial port**, so it can read the serial port to see what is happening and detect errors.

You can use the 'Arduino Serial Monitor' for this, but we recommend using the following software:
### Windows:
Open *Command Prompt*.

Configure the Baud Rate of the port to 115200 bps:
```
mode COM1: baud=115200
```
Read the serial port:
```
copy COM1: con:
```
### Linux and macOS:
Install *cu Monitor*. It is an excellent shell monitor and very useful.
```
sudo apt install cu
```
Run *cu Monitor*:
```
cu -l /dev/ttyUSB0 -s 115200
```
The following screenshot is a reading of the *Serial Port*, you should see something like this:

![ESP32 receiver Serial Monitor](https://i.postimg.cc/m2zhLhPr/Screenshot-from-2020-11-12-12-20-21.png)

## Send Harcoded Json to Keepy to see ESP32 reactions

You can run the available examples quickly by sending the following json which will activate all 4 relays:

```curl --location --request POST 'YOUR-KEEPY-HOST:3002/messages' --header 'Content-Type: application/json' --data-raw '{"iot2tangle":[{"sensor":"Internal","data":[{"InternalTemperature":"47.24"}]},{"sensor":"Environmental","data":[{"Temperature":"62.3"},{"Humidity":"34.2"},{"Pressure":"998.20"}]},{"sensor":"Acoustic","data":[{"SoundLevel":"High"}]},{"sensor":"Light","data":[{"Light":"32"}]},{"sensor":"Accelerometer","data":[{"X":"3.98"},{"Y":"0.06"},{"Z":"9.20"}]},{"sensor":"Gyroscope","data":[{"X":"0.40"},{"Y":"-0.43"},{"Z":"-0.05"}]}],"device": "ESP32-Receiver","timestamp": "1601653408"}'```

and the following command will deactivate them since it changes the values of the sensors:

```curl --location --request POST 'YOUR-KEEPY-HOST:3002/messages' --header 'Content-Type: application/json' --data-raw '{"iot2tangle":[{"sensor":"Internal","data":[{"InternalTemperature":"47.24"}]},{"sensor":"Environmental","data":[{"Temperature":"12.5"},{"Humidity":"81.2"},{"Pressure":"998.20"}]},{"sensor":"Acoustic","data":[{"SoundLevel":"Low"}]},{"sensor":"Light","data":[{"Light":"32"}]},{"sensor":"Accelerometer","data":[{"X":"0.58"},{"Y":"0.06"},{"Z":"9.20"}]},{"sensor":"Gyroscope","data":[{"X":"0.40"},{"Y":"-0.43"},{"Z":"-0.05"}]}],"device": "ESP32-Receiver","timestamp": "1601653413"}'```

# Json Accepted example

```{"iot2tangle":[{"sensor":"Internal","data":[{"InternalTemperature":47.24}]},{"sensor":"Environmental","data":[{"Temperature":"25.7"},{"Humidity":"34.2"},{"Pressure":"998.20"}]},{"sensor":"Accelerometer","data":[{"X":"3.98"},{"Y":"0.06"},{"Z":"9.20"}]},{"sensor":"Acoustic","data":[{"SoundLevel":"Low"}]}],"device": "ESP-HTTP","timestamp": "1601653408"}```

# Limitations of the Json Decoding
The ***I2T Json Decoder*** uses a very simple and widely used in Embedded Systems *Json library for C* called ***jsmn*** <https://github.com/zserge/jsmn>.
It is a very powerful tool and offers many decoding options and compatibility with all kinds of *C types*.

However, we have decided to use only some of its features and make a very simple decoder, so that it is very easy to modify. That is why our code decoder has the following limitations that must be met for correct code operation:
- Must be in ***IOT2TANGLE Json Standart format***. [Wiki/The-I2T-Json-standard](https://github.com/iot2tangle/Keepy/wiki/The-I2T-Json-standard)
- Limited to *10 sensors* and *16 values for each sensor*. Although this can be expanded very easily if necessary.
- ***Sensor values must always be strings***. That is, they must be enclosed in quotes (**"**). Then, they can be easily converted to integer, float or boolean as you can see in the examples.
- ***Arrays of any kind will not be recognized***. Although the library allows to read arrays, it has not been implemented because it would complicate the code too much and it can be added very easily for a particular application.
- Sensor data will be saved ONLY if the *sensor json object* has the label **"sensor"**.
- The *sensor objects* should be all together, and you should not put another *json object* in between because it will not give a good sensor reading.
- Preferably the batch of *sensor objects* should be the last ones, just before the 'device' label.


*For inquiries, improvements or errors detected, please start an issue in this repository.*
