#include <LoRa.h>
#include <SPI.h>

const int cs_pin = 4; 
const int reset_pin = 2;
const int irq_pin = 22; // DIO0 on HOPE RF LORA MODULE 

// message counter
byte message_count = 0;

void setup() {
   Serial.begin(115200);

   // enable irq hardware interrupt pin

   
   LoRa.setPins(cs_pin, reset_pin, irq_pin);
   Serial.println("LORA send test");

   if(!LoRa.begin(868E6)) {
    Serial.println("Lora failed to start");
   } else {
    Serial.println("Lora started OK!");
   }

}

void loop() {

  Serial.println("sending packet: ");
  Serial.println(message_count);

  // send packet
  LoRa.beginPacket();
  LoRa.print("Packet ");
  LoRa.print(message_count);
  LoRa.endPacket();

  message_count++;

  // 3 second delay
  delay(3000);
  

}
