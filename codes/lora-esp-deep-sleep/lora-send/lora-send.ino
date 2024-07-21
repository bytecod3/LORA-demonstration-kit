/**
This code implements LORA transmission whith deep sleep when not sending data. 
The ESP wakes up after a predefined period of time to read the temperature sensor and 
transmit this data to a lora receiver

Here we use a timer wake up method

By doing this we prolong the battery life powering our project 

*/

#include <LoRa.h>
#include <SPI.h>

const int cs_pin = 27; 
const int reset_pin = 2;
const int irq_pin = 22; // DIO0 on HOPE RF LORA MODULE 

// save vars to RTC memory so that they do not get wiped
RTC_DATA_ATTR int message_counter = 0;
RTC_DATA_ATTR int boot_count = 0;

char msg_buffer[20]; // to hold the message to be transmitted
int data = 34; // actual sensor data (0, 1)

#define US_TO_S_CONVERSION_FACTOR 1E6
#define SLEEP_TIME                10 // sleep time in seconds

/**
Initialize LORA
**/
void init_lora() {
  LoRa.setPins(cs_pin, reset_pin, irq_pin);
  Serial.println("LORA send test");

  if(!LoRa.begin(868E6)) {
  Serial.println("Lora failed to start");
  } else {
  Serial.println("Lora started OK!");
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
  // compose packet 
  sprintf(msg_buffer, "%d, %d\n", message_count, data);

  // SEND DATA
  Serial.print("sending packet: ");
  Serial.println(message_count);
  LoRa.beginPacket();
  LoRa.print("Packet ");
  LoRa.print(msg_buffer);
  LoRa.endPacket();

  message_count++;

  // give some time for the packet to send 
  delay(2000);
}

void setup() {
  Serial.begin(115200);

  init_lora();

  // init sensor pins
  // pinMode(4, INPUT);

  transmit_lora_packet();

  // increment boot number with every boot
  boot_count++;
  Serial.println("Boot number: " + String(boot_count));
  // why did we wake up?
  get_wake_up_reason();

  // configure the wake up source
  esp_sleep_enable_timer_wakeup(SLEEP_TIME*US_TO_S_CONVERSION_FACTOR);

  Serial.println("[Going to sleep]");
  esp_deep_sleep_start();

}

void loop() {
  
}
