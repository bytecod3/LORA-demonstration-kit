/**
This code implements LORA transmission whith deep sleep when not sending data. 
The ESP wakes up after a predefined period of time to read the temperature sensor and 
transmit this data to a lora receiver

Here we use a timer wake up method

By doing this we prolong the battery life powering our project 

*/

#include <LoRa.h>
#include <SPI.h>

const int cs_pin = 4; 
const int reset_pin = 2;
const int irq_pin = 22; // DIO0 on HOPE RF LORA MODULE 

char msg_buffer[20]; // to hold the message to be transmitted
int data; // actual sensor data (0, 1)

#define US_TO_S_CONVERSION_FACTOR 1E6
#define SLEEP_TIME                10 // sleep time in seconds

/**
Initialize LORA
**/
uint8_t init_lora() {
  LoRa.setPins(cs_pin, reset_pin, irq_pin);
  Serial.println("LORA deep sleep test");

  if(!LoRa.begin(868E6)) {
    Serial.println("Lora failed to start");
    return 0;
  } else {
    Serial.println("Lora started OK!");
    return 1;
  }

}

/**
tell us why we woke up
**/
void get_wake_up_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer");
  }

}

/**
  Send LORA packet
**/
RTC_DATA_ATTR int message_count;
void transmit_lora_packet() { 
  Serial.println("sending packet: ");
  Serial.println(message_count);

  // compose packet 
  sprintf(msg_buffer, "%d, %d\n", message_count, data);

  // send packet
  LoRa.beginPacket();
  LoRa.print(msg_buffer);
  LoRa.endPacket();

  message_count++;
}

void setup() {
  Serial.begin(115200);

  // init the LORA modules 
  uint8_t lora_status = init_lora();

  // init sensor pins
  pinMode(4, INPUT);

  // read the sensor every time we wake up
  if(lora_status) {
    int sensor_value = digitalRead(4);
    
    // transmit the value to receiver
    transmit_lora_packet(); 
    delay(3000);
  } else {
    Serial.println(F("Lora failed to start"));
  }
  
  // why did we wake up?
  get_wake_up_reason();

  // configure the wake up source
  esp_sleep_enable_timer_wakeup(SLEEP_TIME*US_TO_S_CONVERSION_FACTOR);

  Serial.println("[Going to sleep]");
  esp_deep_sleep_start();


}

void loop() {}
