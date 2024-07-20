# HOPE-RFM95W-LORA-TESTS
LORA transmission tests codes 

This codes have been tested using ESP32WROOM dev board. They use VSPI for SPI and HOPE-RFM95W Lora
Modules pictured below. 
The connections are almost similar if using other LORA modules such as the Adafruit RFM9x modules.

![HOPERF-LORA-MODULE](./imgs/hoperf-lora.jpg)

## Needed libraries
1. Lora library by Sandeep Mistry (https://github.com/sandeepmistry/arduino-LoRa)

## Hardware setup
Connect the LORA modules to ESP32 as follows:


|LORA|ESP32|
|---|---|
|3V3|3V3|
|GND|GND|
|MOSI|23|
|MISO|19|
|SCK|18|
|NSS(CS)|4|
|RESET|2|
|DIO0|22|

These connections can be similar for the transmitter and the receiver. 
Note: NSS(CS) can be choosen to be any pin. The DIO0 pin is the IRQ pin that MUST be capable 
of hardware interrupt. 

## Tests done 
### 1. Simple packet send and receive
This tests very basic sending and receiving. The transmitter sends a packet with a message
count. 
The receiver parses the received packet and prints out on the serial monitor.

