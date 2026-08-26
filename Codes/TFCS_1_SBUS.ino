/*
 * TFCS-1: Teensy Flight Computer & Climate Suite
 * SBUS TO ARDUINO (RADIO LINK)
 * 
 * PIN D3
 * 
 * Built by Rithish - 16-year-old maker
 * GitHub: github.com/R1th1shwork/TFCS-1
 */

#include <sbus.h>

SBUS sbus;

void setup() {
  Serial.begin(115200);
  
  // Pin 3 used for SBUS input without external inverter
  sbus.begin(3, sbusNonBlocking);
  
  Serial.println("=== SBUS TEST STARTED ===");
  Serial.println("Move sticks and flip switches!");
  Serial.println("-----------------------------------");
}

void loop() {
  // Check for an active receiver signal
  if (sbus.hasSignal()) {
    // fdivitto/sbus outputs rescaled pulse widths (988µs - 2012µs)
    uint16_t ch1 = sbus.getChannel(1);
    uint16_t ch2 = sbus.getChannel(2);
    uint16_t ch3 = sbus.getChannel(3);
    uint16_t ch4 = sbus.getChannel(4);
    uint16_t ch5 = sbus.getChannel(5);
    uint16_t ch6 = sbus.getChannel(6);
    
    Serial.print("CH1:"); Serial.print(ch1);
    Serial.print(" CH2:"); Serial.print(ch2);
    Serial.print(" CH3:"); Serial.print(ch3);
    Serial.print(" CH4:"); Serial.print(ch4);
    Serial.print(" CH5:"); Serial.print(ch5);
    Serial.print(" CH6:"); Serial.println(ch6);
  } else {
    Serial.println("NO SIGNAL / RECEIVER DISCONNECTED");
  }
  
  delay(20);
}