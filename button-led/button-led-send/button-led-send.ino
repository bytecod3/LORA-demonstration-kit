  #include <LoRa.h>
#include <SPI.h>

const int cs_pin = 4; 
const int reset_pin = 2;
const int irq_pin = 22; // DIO0 on HOPE RF LORA MODULE 

// message counter
byte message_count = 0;

// push button variables 
int button_pin = 14;
int send_button_state;

void setup() {
   Serial.begin(115200);

   pinMode(button_pin, INPUT);
   
   LoRa.setPins(cs_pin, reset_pin, irq_pin);
   Serial.println("LORA send test");

   if(!LoRa.begin(868E6)) {
    Serial.println("Lora failed to start");
   } else {
    Serial.println("Lora started OK!");
   }

}

void loop() {

  // read button
  send_button_state = digitalRead(button_pin);

  if(send_button_state == LOW) {
    // send packet
    LoRa.beginPacket();
    LoRa.print("button pressed");
    LoRa.endPacket();
    message_count++;
    Serial.print("sending packet: ");
    Serial.println(message_count);
    delay(500);

  }

}
