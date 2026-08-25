/*
 * TFCS-1: Teensy Flight Computer & Climate Suite
 * Full Flight Control - Ailerons, Rudder, Elevator
 * 
 * MPU-6050 IMU reads roll and pitch angles
 * Servos respond to stabilize the aircraft
 * 
 * Pin Mapping:
 * - Pin 5:  Elevator  (Pitch Control)
 * - Pin 6:  Rudder    (Yaw Control)
 * - Pin 9:  Left Aileron  (Roll Control)
 * - Pin 10: Right Aileron (Roll Control)
 * 
 * Built by Rithish - 16-year-old maker
 * GitHub: github.com/R1th1shwork/TFCS-1
 */

#include <Wire.h>
#include <Servo.h>

#define MPU_ADDR 0x68

// Servo objects
Servo elevator;     // Pin 5
Servo rudder;       // Pin 6
Servo leftAileron;  // Pin 9
Servo rightAileron; // Pin 10

// Raw angles from IMU
float rawPitch = 0.0;
float rawRoll = 0.0;

// Filtered angles (smooth, no jitter)
float filteredPitch = 0.0;
float filteredRoll = 0.0;

// Low-Pass Filter Alpha (0.0 to 1.0)
// Lower = smoother but slower response
// Higher = faster response but more jitter
const float ALPHA = 0.15;

// Max tilt angles for full servo deflection
const float MAX_PITCH = 20.0;  // degrees
const float MAX_ROLL = 30.0;   // degrees

// Servo positions
int elevatorPos = 90;
int rudderPos = 90;
int leftAileronPos = 90;
int rightAileronPos = 90;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  
  // Attach servos to pins
  elevator.attach(5);
  rudder.attach(6);
  leftAileron.attach(9);
  rightAileron.attach(10);
  
  // Center all servos
  elevator.write(90);
  rudder.write(90);
  leftAileron.write(90);
  rightAileron.write(90);
  
  // Wake up MPU-6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  
  delay(100);
  
  // Check if MPU is connected
  Wire.beginTransmission(MPU_ADDR);
  if (Wire.endTransmission() == 0) {
    Serial.println("✅ MPU-6050 FOUND!");
  } else {
    Serial.println("❌ MPU-6050 NOT FOUND!");
    Serial.println("Check: 5V, GND, A4(SDA), A5(SCL)");
    while (1) {}  // Stop here
  }
  
  Serial.println("=== TFCS-1 FLIGHT CONTROLLER ===");
  Serial.println("Elevator  : Pin 5  (Pitch)");
  Serial.println("Rudder    : Pin 6  (Yaw)");
  Serial.println("Left Aileron : Pin 9  (Roll)");
  Serial.println("Right Aileron: Pin 10 (Roll)");
  Serial.println("-----------------------------------");
  Serial.println("Tilt the board to see servos move!");
  Serial.println("-----------------------------------");
}

void loop() {
  // Read accelerometer data (6 bytes from 0x3B)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);
  
  if (Wire.available() >= 6) {
    int16_t ax = Wire.read() << 8 | Wire.read();
    int16_t ay = Wire.read() << 8 | Wire.read();
    int16_t az = Wire.read() << 8 | Wire.read();
    
    // Calculate raw angles in degrees
    rawPitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
    rawRoll  = atan2(ay, az) * 180.0 / PI;
    
    // Apply low-pass filter to remove jitter
    filteredPitch = (ALPHA * rawPitch) + ((1.0 - ALPHA) * filteredPitch);
    filteredRoll  = (ALPHA * rawRoll)  + ((1.0 - ALPHA) * filteredRoll);
    
    // ===== ELEVATOR (Pitch Control) =====
    // Nose down → Elevator goes UP (40°)
    // Nose up   → Elevator goes DOWN (140°)
    elevatorPos = map(filteredPitch, -MAX_PITCH, MAX_PITCH, 140, 40);
    elevatorPos = constrain(elevatorPos, 20, 160);
    
    // ===== RUDDER (Yaw Control - Reduced Range) =====
    // Tilt left  → Rudder turns left (60°)
    // Tilt right → Rudder turns right (120°)
    rudderPos = map(filteredRoll, -MAX_ROLL, MAX_ROLL, 60, 120);
    rudderPos = constrain(rudderPos, 50, 130);
    
    // ===== AILERONS (Roll Control) =====
    // Tilt left  → Left UP (40°), Right DOWN (140°)
    // Tilt right → Left DOWN (140°), Right UP (40°)
    leftAileronPos = map(filteredRoll, -MAX_ROLL, MAX_ROLL, 40, 140);
    leftAileronPos = constrain(leftAileronPos, 20, 160);
    
    rightAileronPos = map(filteredRoll, -MAX_ROLL, MAX_ROLL, 140, 40);
    rightAileronPos = constrain(rightAileronPos, 20, 160);
    
    // ===== DEADBAND (Stops servo buzzing when level) =====
    if (abs(filteredPitch) < 0.8) elevatorPos = 90;
    if (abs(filteredRoll) < 0.8) {
      rudderPos = 90;
      leftAileronPos = 90;
      rightAileronPos = 90;
    }
    
    // ===== MOVE SERVOS =====
    elevator.write(elevatorPos);
    rudder.write(rudderPos);
    leftAileron.write(leftAileronPos);
    rightAileron.write(rightAileronPos);
    
    // ===== TELEMETRY =====
    Serial.print("P:");
    Serial.print(filteredPitch, 1);
    Serial.print("° (E:");
    Serial.print(elevatorPos);
    Serial.print("°)  R:");
    Serial.print(filteredRoll, 1);
    Serial.print("° (A_L:");
    Serial.print(leftAileronPos);
    Serial.print(" A_R:");
    Serial.print(rightAileronPos);
    Serial.print(" Rudd:");
    Serial.print(rudderPos);
    Serial.println("°)");
  } else {
    Serial.println("⚠️ Waiting for MPU data...");
  }
  
  delay(20);  // 50Hz update rate
}