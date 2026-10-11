#include <SPI.h>
#include <LoRa.h>

// LoRa Pins
#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 26

void setup() {
  Serial.begin(115200);

  Serial.println("Base Station Receiver Ready!");

  // Start LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed! Check wiring.");
    while (1);
  }
  
  Serial.println("Listening for Emergency Signals...");
  Serial.println("============================================");
}

void loop() {
  // Check if a radio packet arrived from the helmet
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    Serial.println("\n[ALERT] INCOMING EMERGENCY SIGNAL:");
    
    // Print out the exact message received over the air
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    Serial.println("\n----------------------------------");
  }
}