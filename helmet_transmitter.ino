#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <LoRa.h>

Adafruit_MPU6050 mpu;
unsigned long lastCrashTime = 0;

// LoRa Pins
#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 26

void setup() {
  Serial.begin(115200);
  
  // Start MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050!");
    while (1) { delay(10); } 
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  
  // Start LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed! Check wiring.");
    while (1); 
  }
  
  Serial.println("Helmet Transmitter Ready!");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  // Calculate total G-force
  float accMag = sqrt(a.acceleration.x * a.acceleration.x + 
                      a.acceleration.y * a.acceleration.y + 
                      a.acceleration.z * a.acceleration.z);
                      
  // If a hard crash happens (Magnitude > 25)
  if (accMag > 25.0 && millis() - lastCrashTime > 10000) {
    Serial.println("CRASH DETECTED! Transmitting via LoRa...");
    
    // Build the emergency payload with UVCE coordinates
    String message = "EMERGENCY! Crash Detected.\n";
    message += "Location Name: MARVEL lab, UVCE, KR circle\n";
    message += "Coordinates: 12°58'28.1\"N 77°35'08.5\"E\n";
    message += "Google Maps: https://maps.google.com/?q=12.974472,77.585694";
    
    // Wirelessly transmit the payload
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();
    
    Serial.println("Transmission Sent!");
    lastCrashTime = millis();
  }
}