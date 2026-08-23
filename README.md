# TFCS-1: Teensy Flight Computer & Climate Suite

[![Platform](https://img.shields.io/badge/Platform-Teensy%204.1-orange.svg)](#hardware)
[![Status](https://img.shields.io/badge/Status-Active%20Development-yellow.svg)](#status)
[![Age](https://img.shields.io/badge/Built%20By-16%20Year%20Old-blue.svg)](#author)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](#license)

&gt; **WARNING: Active Development**
&gt; Expect breaking changes to hardware wiring and software builds as this project evolves through rapid field-testing.

&gt; **AI Transparency Disclosure**
&gt; All system architecture, hardware selection, circuit design, and physical builds are 100% designed and wired by me. AI was used only as a sounding board for code formatting, debugging, and documentation polish. The solder and flight logic are entirely human-built.

**TFCS-1** is an open-source flight controller and environmental sensing platform built around the **Teensy 4.1**. It combines high-rate flight control with real-time atmospheric data logging for experimental aircraft and environmental monitoring.

---

## Table of Contents

- [Why I Built This](#why-i-built-this)
- [Story / Behind the Scenes](#story--behind-the-scenes)
- [Current Status](#current-status)
- [Hardware](#hardware)
- [Control Surfaces](#control-surfaces)
- [Software](#software)
- [Setup](#setup)
- [Telemetry](#telemetry)
- [Dev Log](#dev-log)
- [Challenges & Fixes](#challenges--fixes)
- [Roadmap](#roadmap)
- [Equipment Status](#equipment-status)
- [Contributing](#contributing)
- [Author](#author)
- [License](#license)

---

## Why I Built This

I am a 16-year-old maker obsessed with flight. I did not start with a kit or a pre-built flight controller. I started with a soldering iron, a breadboard, and the determination to understand every wire and every line of code that keeps a plane in the air.

This project exists because:
- I want to **learn** flight controller tuning, sensor fusion, and embedded systems from first principles
- I want to **open-source** every finding, failure, and fix so the next builder does not start from zero
- I believe the best way to learn is to build, break, and rebuild -- one crash at a time

Schematics, PCB designs, flight videos, and full telemetry logs are coming soon.

---

## Story / Behind the Scenes

**The Beginning**
The Teensy 4.1 arrived from my tutor -- a 600MHz beast I had been reading about for months. The first time the orange LED blinked, I knew this was real. Then came the ICM-20948, the fancy 9-DOF IMU that was supposed to be the heart of the system. It did not work. I2C scanner found it at 0x68, but the moment I tried to read data, it hung. No pull-up resistors, maybe a logic level issue, maybe just inexperience. I spent hours staring at wires that refused to talk.

**The Breakthrough**
I switched to the MPU-6050. Cheap, common, and suddenly -- it just worked. Data flowed. Numbers moved when I tilted the board. I connected the first servo and watched a control surface respond to my hands. That moment, seeing physics turn into servo motion, is when TFCS-1 became more than a project. It became a flight controller.

**The Reality Check**
Not everything worked. Pin 8 was dead for servos. The ICM-20948 still sits on my desk, waiting for 4.7k resistors. I salvaged wings from an old RC plane, pulled servos from crashed airframes, and learned that "working" in electronics means "working after the 47th try." Every buzz, every jitter, every frozen I2C bus taught me something.

**Why Open Source?**
Because I learned from open-source projects. Because someone else out there is 16 years old, staring at a breadboard, wondering why their sensor won't respond. This is for them. This is for the builders who learn by breaking things.

---

## Current Status

| Module | Status | Notes |
|--------|--------|-------|
| MPU-6050 Roll + Pitch | [x] Done | Working reliably |
| Elevator servo | [x] Done | Pin 5, 40-140 deg |
| Rudder servo | [x] Done | Pin 6, 60-120 deg |
| Aileron servos | [x] Done | Pin 9 & 10, 40-140 deg |
| Low-pass filter (ALPHA=0.15) | [x] Done | Removes jitter |
| Deadband (0.8 deg) | [x] Done | Stops servo buzzing |
| Serial telemetry | [x] Done | 115200 baud |
| Flight control logic | [x] Done | Roll + Pitch stabilization |
| Teensy 4.1 integration | [~] In Progress | Borrowed unit |
| ICM-20948 9-DOF fusion | [~] In Progress | Needs debugging |
| SD card logging | [ ] Coming Soon | High-speed CSV |
| GPS (NEO-M8N) | [ ] Coming Soon | Position tracking |
| FPV (5.8GHz) | [ ] Coming Soon | Camera + VTX |
| Custom PCB | [ ] Coming Soon | KiCad design |

**Test Platform:** E-flite Apprentice S1E (1500mm wingspan, 840kv motor)

---

## Hardware

### Compute & Avionics

| Component | Model | Specs | Status |
|-----------|-------|-------|--------|
| Primary Controller | Teensy 4.1 | 600MHz ARM Cortex-M7, 1MB RAM | **BORROWED** |
| Backup Controller | Arduino Uno R3 | 16MHz ATmega328P | Owned |
| Current IMU | MPU-6050 | 6-DOF (Accel + Gyro) | Owned |
| Future IMU | ICM-20948 | 9-DOF (Accel + Gyro + Mag) | **BORROWED** |
| GPS Module | NEO-M8N | UART, 25Hz update | Owned |
| Barometer | BMP390 | I2C, +/-0.5m accuracy | **BORROWED** |

### Actuators

| Component | Pin | Range | Status |
|-----------|-----|-------|--------|
| Left Aileron | 9 | 40-140 deg | Owned |
| Right Aileron | 10 | 40-140 deg | Owned |
| Elevator | 5 | 40-140 deg | Owned |
| Rudder | 6 | 60-120 deg | Owned |
| ESC | - | 30A w/ BEC | Owned |

### Power

| Component | Specs | Status |
|-----------|-------|--------|
| UBEC | 7A, 5V output | Owned |
| Battery | 3S-4S LiPo | Need to buy |
| Power Distribution | Custom board | Coming Soon |

### Future Additions

- [ ] FPV Camera + VTX (5.8GHz)
- [ ] MicroSD Card Module
- [ ] OLED Display
- [ ] Custom PCB

---

## Control Surfaces

| Axis | Surface | Pin | Range | Response |
|------|---------|-----|-------|----------|
| Pitch | Elevator | 5 | 40-140 deg | Nose Down -&gt; UP |
| Roll | Left Aileron | 9 | 40-140 deg | Tilt Left -&gt; UP |
| Roll | Right Aileron | 10 | 40-140 deg | Tilt Left -&gt; DOWN |
| Yaw | Rudder | 6 | 60-120 deg | Tilt Left -&gt; Left |

**Neutral position for all servos:** 90 deg

---

## Software

### Current Features

| Feature | Implementation | Status |
|---------|----------------|--------|
| I2C Communication | Wire library @ 400kHz | Done |
| Angle Calculation | Roll/Pitch from accelerometer | Done |
| Digital Filtering | Low-pass filter (ALPHA = 0.15) | Done |
| Deadband | 0.8 degree threshold | Done |
| Servo Control | 4 servos (Ailerons, Elevator, Rudder) | Done |
| Telemetry Output | Serial Monitor @ 115200 baud | Done |

### Control Loop

| Parameter | Value |
|-----------|-------|
| Loop Rate | 50Hz (20ms) |
| Filter | Exponential Moving Average |
| Alpha | 0.15 |
| Deadband | 0.8 deg |
| Telemetry Baud | 115200 |

### Key Code Snippet

```cpp
// Exponential Moving Average Filter
filteredPitch = (ALPHA * rawPitch) + ((1.0 - ALPHA) * filteredPitch);

// Deadband to prevent servo buzzing
if (abs(filteredPitch) &lt; 0.8) elevatorPos = 90;

// Map to servo positions
elevatorPos = map(filteredPitch, -20, 20, 140, 40);
