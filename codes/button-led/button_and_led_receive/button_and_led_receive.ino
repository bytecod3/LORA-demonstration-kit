/*
 * This sketch receives data from LORA transmitter 
  * receives and displys message packet from lora
  * based upon DroneBot workshop code 
  * DroneBot Workshop 2023
  * https://dronebotworkshop.com
  * Author - Edwin Mwiti
  * July 20 2024
*/

#include <LoRa.h>
#include <SPI.h>

const int cs_pin = 25; 
const int reset_pin = 14;
const int irq_pin = 22; // DIO0 on HOPE RF LORA MODULE - pin must have hardware interrupt

// led connection
int led = 4;

// receive message variables
String contents = "";
String button_press = "button pressed";
bool recv_button_state;

// message counter
byte message_count = 0;

void setup() {
   Serial.begin(115200);

   pinMode(led, OUTPUT);
   
   LoRa.setPins(cs_pin, reset_pin, irq_pin);
   Serial.println("LORA receive test");

   if(!LoRa.begin(868E6)) {
    Serial.println("Lora failed to start");
   } else {
    Serial.println("Lora started OK!");
   }

}

void loop() {

  // parse packet
  int pkt_sz = LoRa.parsePacket();
  if(pkt_sz) {
    // received packet
    Serial.print("[Received pkt] ");

    // Read packet
    while(LoRa.available()) {
      contents += (char) LoRa.read();
    }

    // Print RSSI of the packet
    Serial.print(" [RSSI]");
    Serial.println(LoRa.packetRssi());

    // toggle button state 
    if(contents.equals(button_press)) {
      recv_button_state = !recv_button_state;
    }

    // drive LED
    if(recv_button_state == true) {
      digitalWrite(led, HIGH);
      Serial.println("[LED ON]");
    } else {
      digitalWrite(led, LOW);
      Serial.println("[LED OFF]");
    }

    // reset the message
    contents = "";

  }

}
