/*
 * TFCS-1: SBUS + MPU + PID (Self Correcting)
 * MPU reads tilt, SBUS reads sticks, PID corrects
 * 
 * Pins:
 * MPU: SDA→A4, SCL→A5, 3.3V, GND
 * SBUS: Pin 3
 * Servos: Elevator→5, Rudder→6, L Aileron→9, R Aileron→10
 */

#include <Wire.h>
#include <Servo.h>
#include <sbus.h>

// ===== SBUS =====
SBUS sbus;

// ===== SERVOS =====
Servo elevator;
Servo rudder;
Servo leftAil;
Servo rightAil;

// ===== MPU =====
#define MPU_ADDR 0x68

// ===== VARIABLES =====
float roll, pitch;
int rollPID, pitchPID;
int stickAIL, stickELE, stickRUD, stickTHR;

// ===== PID GAINS =====
float Kp_roll = 2.5;
float Ki_roll = 0.0;
float Kd_roll = 0.5;

float Kp_pitch = 2.5;
float Ki_pitch = 0.0;
float Kd_pitch = 0.5;

// ===== PID MEMORY =====
float rollError_prev = 0;
float pitchError_prev = 0;
float rollIntegral = 0;
float pitchIntegral = 0;

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  // --- SBUS ---
  sbus.begin(3, sbusNonBlocking);

  // --- SERVOS ---
  elevator.attach(5);
  rudder.attach(6);
  leftAil.attach(9);
  rightAil.attach(10);
  elevator.write(90);
  rudder.write(90);
  leftAil.write(90);
  rightAil.write(90);

  // --- MPU ---
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(100);

  Serial.println("=== TFCS-1 STABILIZED MODE ===");
  Serial.println("MPU + SBUS + PID");
  Serial.println("-----------------------------------");
}

// ===== LOOP =====
void loop() {
  // ===== 1. READ MPU =====
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  if (Wire.available() >= 6) {
    int16_t ax = Wire.read() << 8 | Wire.read();
    int16_t ay = Wire.read() << 8 | Wire.read();
    int16_t az = Wire.read() << 8 | Wire.read();

    roll = atan2(ay, az) * 180 / PI;
    pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180 / PI;
  }

  // ===== 2. READ SBUS =====
  if (sbus.hasSignal()) {
    stickAIL = sbus.getChannel(1);   // Aileron
    stickELE = sbus.getChannel(2);   // Elevator
    stickTHR = sbus.getChannel(3);   // Throttle
    stickRUD = sbus.getChannel(4);   // Rudder
  }

  // ===== 3. CONVERT STICKS TO TARGET ANGLES =====
  float targetRoll = map(stickAIL, 300, 1700, -30, 30);
  float targetPitch = map(stickELE, 300, 1700, -20, 20);

  // ===== 4. PID CALCULATION (ROLL) =====
  float rollError = targetRoll - roll;
  rollIntegral += rollError * 0.02;
  rollIntegral = constrain(rollIntegral, -10, 10);
  float rollDerivative = (rollError - rollError_prev) / 0.02;
  rollError_prev = rollError;

  rollPID = Kp_roll * rollError + Ki_roll * rollIntegral + Kd_roll * rollDerivative;
  rollPID = constrain(rollPID, -30, 30);

  // ===== 5. PID CALCULATION (PITCH) =====
  float pitchError = targetPitch - pitch;
  pitchIntegral += pitchError * 0.02;
  pitchIntegral = constrain(pitchIntegral, -10, 10);
  float pitchDerivative = (pitchError - pitchError_prev) / 0.02;
  pitchError_prev = pitchError;

  pitchPID = Kp_pitch * pitchError + Ki_pitch * pitchIntegral + Kd_pitch * pitchDerivative;
  pitchPID = constrain(pitchPID, -20, 20);

  // ===== 6. CALCULATE SERVO POSITIONS =====
  int elevPos = 90 + pitchPID;
  elevPos = constrain(elevPos, 20, 160);

  int leftAilPos = 90 + rollPID;
  leftAilPos = constrain(leftAilPos, 20, 160);

  int rightAilPos = 90 - rollPID;
  rightAilPos = constrain(rightAilPos, 20, 160);

  int rudPos = map(stickRUD, 300, 1700, 40, 140);
  rudPos = constrain(rudPos, 30, 150);

  // ===== 7. DEADBAND (Stops buzzing) =====
  if (abs(roll) < 0.8) {
    leftAilPos = 90;
    rightAilPos = 90;
  }
  if (abs(pitch) < 0.8) {
    elevPos = 90;
  }

  // ===== 8. MOVE SERVOS =====
  elevator.write(elevPos);
  rudder.write(rudPos);
  leftAil.write(leftAilPos);
  rightAil.write(rightAilPos);

  // ===== 9. TELEMETRY =====
  Serial.print("R:");
  Serial.print(roll, 1);
  Serial.print(" P:");
  Serial.print(pitch, 1);
  Serial.print(" | T_R:");
  Serial.print(targetRoll, 1);
  Serial.print(" T_P:");
  Serial.print(targetPitch, 1);
  Serial.print(" | PID_R:");
  Serial.print(rollPID, 1);
  Serial.print(" PID_P:");
  Serial.print(pitchPID, 1);
  Serial.print(" | E:");
  Serial.print(elevPos);
  Serial.print(" L:");
  Serial.print(leftAilPos);
  Serial.print(" R:");
  Serial.print(rightAilPos);
  Serial.print(" Rud:");
  Serial.println(rudPos);

  delay(20); // 50Hz
}