# TFCS-1: Teensy Flight Computer & Climate Suite

[![Platform](https://img.shields.io/badge/Platform-Teensy%204.1-orange.svg)](#hardware)
[![Status](https://img.shields.io/badge/Status-Active%20Development-yellow.svg)](#status)
[![Age](https://img.shields.io/badge/Built%20By-16%20Year%20Old-blue.svg)](#author)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](#license)

> **WARNING: Active Development**
> Expect breaking changes to hardware wiring and software builds as this project evolves through rapid field-testing.

> **AI Transparency Disclosure**
> All system architecture, hardware selection, circuit design, and physical builds are 100% designed and wired by me. AI was used only as a sounding board for code formatting, debugging, and documentation polish. The solder and flight logic are entirely human-built.

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
| Pitch | Elevator | 5 | 40-140 deg | Nose Down -> UP |
| Roll | Left Aileron | 9 | 40-140 deg | Tilt Left -> UP |
| Roll | Right Aileron | 10 | 40-140 deg | Tilt Left -> DOWN |
| Yaw | Rudder | 6 | 60-120 deg | Tilt Left -> Left |

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
if (abs(filteredPitch) < 0.8) elevatorPos = 90;

// Map to servo positions
elevatorPos = map(filteredPitch, -20, 20, 140, 40);
```

---

## Setup

### 1. Install Libraries

```cpp
#include <Wire.h>    // I2C Communication
#include <Servo.h>   // Servo Control
```

### 2. Upload

- Select board: Arduino Uno or Teensy 4.1
- Select correct COM port
- Upload
- Open Serial Monitor at 115200 baud

### 3. Test Procedure

| Test | Expected Behavior |
|------|-------------------|
| Hold board level | All servos at 90 deg |
| Tilt nose down | Elevator goes UP (40 deg) |
| Tilt nose up | Elevator goes DOWN (140 deg) |
| Tilt left | Left aileron UP, Right aileron DOWN |
| Tilt right | Left aileron DOWN, Right aileron UP |

---

## Telemetry

```
P:0.0 deg (Elev:90 deg) | R:0.0 deg (Rudd:90 deg) | A:90 deg
P:-5.2 deg (Elev:77 deg) | R:0.0 deg (Rudd:90 deg) | A:77 deg
P:10.1 deg (Elev:65 deg) | R:0.0 deg (Rudd:90 deg) | A:65 deg
```

**Key:**
- P: Filtered Pitch Angle (degrees)
- Elev: Elevator Position (0-180)
- R: Filtered Roll Angle (degrees)
- Rudd: Rudder Position (0-180)
- A: Aileron Position (0-180)

---

## Dev Log

| Log | Milestone |
|-----|-----------|
| #1 | Teensy 4.1 powered on. Orange LED blinked. ICM-20948 failed to respond. |
| #2 | ICM-20948 still dead. Found at 0x68 but hangs on read. Need 4.7k pull-up resistors. |
| #3 | Switched to MPU-6050. Worked first try. Servos move when board tilts. |
| #4 | MPU-6050 streaming roll and pitch data. Numbers moving on Serial Monitor. |
| #5 | Both wing servos working on pins 9 and 10. Smooth 40-90-140 deg movement. |
| #6 | Salvaged wings from old RC plane. Servos tested and working. |
| #7 | Flight controller ALIVE. Roll data drives ailerons correctly. Pin 8 dead, pins 9/10 confirmed. |
| #8 | Rudder and elevator control logic mapped. Full 3-axis control planned. |
| #9 | Traveling. Planned power system: ESC BEC -> servos, UBEC -> Teensy 4.1. |

---

## Challenges & Fixes

| Challenge | Solution |
|-----------|----------|
| ICM-20948 not working | Switched to MPU-6050 |
| Servo jitter | Added low-pass filter (ALPHA 0.15) |
| Servo buzzing at level | Added deadband (0.8 deg) |
| Pin 8 not working with servo | Switched to Pin 5, 6, 9, 10 |
| MPU not responding | Fixed wiring, added debug code |
| Servos moving same direction | Used mirror mounting logic |
| I2C hanging | Added pull-up resistors |

---

## Roadmap

### Immediate
- [ ] Teensy 4.1 full integration
- [ ] ICM-20948 9-DOF sensor fusion
- [ ] SD card data logging
- [ ] GPS integration (NEO-M8N)
- [ ] FPV system (5.8GHz)

### Future
- [ ] Custom PCB design
- [ ] Full 6-axis sensor fusion (Madgwick/Mahony)
- [ ] MAVLink telemetry protocol
- [ ] Waypoint navigation
- [ ] Ground Station (Android/PC)
- [ ] AI-assisted flight tuning

---

## Equipment Status

| Component | Status | Source |
|-----------|--------|--------|
| Teensy 4.1 | **BORROWED** | Tutor (3 months) |
| ICM-20948 | **BORROWED** | Tutor (3 months) |
| BMP390 | **BORROWED** | Tutor (3 months) |
| MPU-6050 | Owned | - |
| Arduino Uno | Owned | - |
| NEO-M8N GPS | Owned | - |
| E-flite Apprentice S1E | Owned | - |
| Servos (4x) | Owned | From old plane |
| 7A UBEC | Owned | - |
| ESC | Owned | - |
| Final Airframe | Funding Requested | Awaiting approval |

> **Special Thanks:** A huge thank you to my tutor for lending me the expensive components (Teensy 4.1, ICM-20948, BMP390). Without their support, this project would not be possible.

---

## Contributing

This is open-source and contributions are welcome.

**How to contribute:**
1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push and open a Pull Request

**Areas needing help:**
- Testing on different hardware
- Documentation improvements
- PCB design
- Sensor fusion algorithms
- Telemetry protocols

---

## Author

**Rithish** -- 16-year-old maker with a passion for flight and embedded systems

- GitHub: github.com/yourusername
- Project: github.com/yourusername/TFCS-1

**Acknowledgments:**
- My Tutor -- For lending critical components
- The Arduino Community -- For open-source libraries and support
- The Teensy Community -- For the incredible Teensy platform

---

## License

This project is licensed under the MIT License.

---

> **Disclaimer:** This project is for educational and experimental purposes only. Always test flight hardware thoroughly before actual flight operations. The authors are not responsible for any damages or injuries resulting from the use of this hardware or software.

---

*Built with passion, powered by curiosity, and tested on borrowed equipment.*
*Fly safe, have fun, and learn something new.*

**Last Updated:** August 2026
