# TFCS-1: Teensy Flight Computer & Climate Suite

[![Platform](https://img.shields.io/badge/Platform-Teensy%204.1-orange.svg)](#hardware)
[![Status](https://img.shields.io/badge/Status-Active%20Development-yellow.svg)](#status)
[![Age](https://img.shields.io/badge/Built%20By-16%20Year%20Old-blue.svg)](#author)

> **⚠️ WARNING: Active Development**
> Expect breaking changes to hardware wiring and software builds as this project evolves through rapid field-testing.

> **🤖 AI Transparency Disclosure**
> All system architecture, hardware selection, circuit design, and physical builds are 100% designed and wired by me. AI was used only as a sounding board for code formatting, debugging, and documentation polish. The solder and flight logic are entirely human-built.

**TFCS-1** is an open-source flight controller and environmental sensing platform built around the **Teensy 4.1**. It combines high-rate flight control with real-time atmospheric data logging for experimental aircraft and environmental monitoring.

- **GitHub:** [github.com/R1th1shwork/TFCS-1](https://github.com/R1th1shwork/TFCS-1)
- **Stardance:** [stardance.hackclub.com/projects/49798](https://stardance.hackclub.com/projects/49798)

---

## 📸 Project Assets

### Images & Media

| File | Description |
|------|-------------|
| `ten.png` | Teensy 4.1 microcontroller - the brain of TFCS-1 |
| `rf.jpeg` | RadioLink R12F SBUS receiver test |
| `icm.jpeg` | ICM-20948 9-DOF IMU (borrowed) |
| `schematics.jpeg` | Wiring diagram for the flight controller |

### Videos

| File | Description |
|------|-------------|
| `TFCS-1_Stardance_Ailerons.mp4` | Aileron servo demo (Stardance submission) |
| `ailerons test.mp4` | Aileron servo test footage |

> **📁 Full Video Demos:** [Google Drive Folder](https://drive.google.com/drive/folders/199b-1cK7TjypQ-vlO30ZAJLWgoHDL5SH)

### Firmware

| File | Description |
|------|-------------|
| `TFCS-1_All_Surfaces.ino` | Full flight controller code (Ailerons + Elevator + Rudder) |
| `TFCS_1_SBUS.ino` | RadioLink SBUS receiver test code |

---

## 📋 Table of Contents

- [Why I Built This](#why-i-built-this)
- [Story / Behind the Scenes](#story--behind-the-scenes)
- [Current Status](#current-status)
- [Hardware](#hardware)
- [Control Surfaces](#control-surfaces)
- [Software](#software)
- [Setup](#setup)
- [Telemetry](#telemetry)
- [Challenges & Fixes](#challenges--fixes)
- [Roadmap](#roadmap)
- [Future Funding & BOM](#future-funding--bom)
- [Equipment Status](#equipment-status)
- [Contributing](#contributing)
- [Author](#author)

---

## Why I Built This

I am a 16-year-old maker obsessed with flight. I did not start with a kit or a pre-built flight controller. I started with a soldering iron, a breadboard, and the determination to understand every wire and every line of code that keeps a plane in the air.

This project exists because:
- I want to **learn** flight controller tuning, sensor fusion, and embedded systems from first principles
- I want to **open-source** every finding, failure, and fix so the next builder does not start from zero
- I believe the best way to learn is to build, break, and rebuild — one crash at a time

---

## Story / Behind the Scenes

### The Beginning

The Teensy 4.1 arrived from my tutor — a 600MHz beast I had been reading about for months. The first time the orange LED blinked, I knew this was real. Then came the ICM-20948, the fancy 9-DOF IMU that was supposed to be the heart of the system. It did not work. I2C scanner found it at `0x68`, but the moment I tried to read data, it hung. No pull-up resistors, maybe a logic level issue, maybe just inexperience. I spent hours staring at wires that refused to talk.

### The Breakthrough

I switched to the MPU-6050. Cheap, common, and suddenly — it just worked. Data flowed. Numbers moved when I tilted the board. I connected the first servo and watched a control surface respond to my hands. That moment, seeing physics turn into servo motion, is when TFCS-1 became more than a project. It became a flight controller.

### The Reality Check

Not everything worked. Pin 8 was dead for servos. The ICM-20948 still sits on my desk, waiting for 4.7k resistors. I salvaged wings from an old RC plane, pulled servos from crashed airframes, and learned that "working" in electronics means "working after the 47th try." Every buzz, every jitter, every frozen I2C bus taught me something.

### Why Open Source?

Because I learned from open-source projects. Because someone else out there is 16 years old, staring at a breadboard, wondering why their sensor won't respond. This is for them. This is for the builders who learn by breaking things.

---

## Current Status

| Module | Status | Notes |
|--------|--------|-------|
| MPU-6050 Roll + Pitch | ✅ Done | Working reliably |
| Elevator servo | ✅ Done | Pin 5, 40-140 deg |
| Rudder servo | ✅ Done | Pin 6, 60-120 deg |
| Aileron servos | ✅ Done | Pin 9 & 10, 40-140 deg |
| Low-pass filter (ALPHA=0.15) | ✅ Done | Removes jitter |
| Deadband (0.8 deg) | ✅ Done | Stops servo buzzing |
| Serial telemetry | ✅ Done | 115200 baud |
| Flight control logic | ✅ Done | Roll + Pitch stabilization |
| RadioLink SBUS Receiver | ✅ Done | All 6 channels reading |
| Teensy 4.1 integration | 🔄 In Progress | Borrowed unit |
| ICM-20948 9-DOF fusion | 🔄 In Progress | Needs debugging |
| SD card logging | ⏳ Coming Soon | High-speed CSV |
| GPS (NEO-M8N) | ⏳ Coming Soon | Position tracking |
| FPV (5.8GHz) | ⏳ Coming Soon | Camera + VTX |
| Custom PCB | ⏳ Coming Soon | KiCad design |

**Test Platform:** E-flite Apprentice S1E (1500mm wingspan, 840kv motor)

> **Note:** The Apprentice is heavily damaged after a crash and cannot be flown. It is currently being used as a test body for bench experiments only.

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
| RadioLink Receiver | R12F | SBUS, 12 channels | Owned |
| RadioLink Transmitter | T12D | 12 channels | Owned |

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
| Battery | 4S 3000mAh | 🔜 Need to buy |
| Power Distribution | Custom board | Coming Soon |

### Future Additions

- [ ] FPV Camera + VTX (5.8GHz)
- [ ] MicroSD Card Module
- [ ] OLED Display
- [ ] Custom PCB
- [ ] Airspeed Sensor (MS4525DO)
- [ ] Professional Barometer (BMP390/MS5611)

---

## Control Surfaces

| Axis | Surface | Pin | Range | Response |
|------|---------|-----|-------|----------|
| Pitch | Elevator | 5 | 40-140 deg | Nose Down → UP |
| Roll | Left Aileron | 9 | 40-140 deg | Tilt Left → UP |
| Roll | Right Aileron | 10 | 40-140 deg | Tilt Left → DOWN |
| Yaw | Rudder | 6 | 60-120 deg | Tilt Left → Left |

**Neutral position for all servos:** 90°

---

## Software

### Current Features

| Feature | Implementation | Status |
|---------|----------------|--------|
| I2C Communication | Wire library @ 400kHz | Done |
| Angle Calculation | Roll/Pitch from accelerometer | Done |
| Digital Filtering | Low-pass filter (ALPHA = 0.15) | Done |
| Deadband | 0.8° threshold | Done |
| Servo Control | 4 servos (Ailerons, Elevator, Rudder) | Done |
| Telemetry Output | Serial Monitor @ 115200 baud | Done |
| SBUS Receiver | RadioLink R12F, 6 channels | Done |

### Control Loop

| Parameter | Value |
|-----------|-------|
| Loop Rate | 50Hz (20ms) |
| Filter | Exponential Moving Average |
| Alpha | 0.15 |
| Deadband | 0.8° |
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
#include <sbus.h>    // SBUS Receiver
```

### 2. Upload

1. Select board: **Arduino Uno** or **Teensy 4.1**
2. Select correct COM port
3. Upload
4. Open Serial Monitor at **115200 baud**

### 3. Test Procedure

| Test | Expected Behavior |
|------|-------------------|
| Hold board level | All servos at 90° |
| Tilt nose down | Elevator goes UP (40°) |
| Tilt nose up | Elevator goes DOWN (140°) |
| Tilt left | Left aileron UP, Right aileron DOWN |
| Tilt right | Left aileron DOWN, Right aileron UP |

---

## Telemetry

```text
P:0.0 deg (Elev:90 deg) | R:0.0 deg (Rudd:90 deg) | A:90 deg
P:-5.2 deg (Elev:77 deg) | R:0.0 deg (Rudd:90 deg) | A:77 deg
P:10.1 deg (Elev:65 deg) | R:0.0 deg (Rudd:90 deg) | A:65 deg
```

**Key:**
- `P`: Filtered Pitch Angle (degrees)
- `Elev`: Elevator Position (0-180)
- `R`: Filtered Roll Angle (degrees)
- `Rudd`: Rudder Position (0-180)
- `A`: Aileron Position (0-180)

---

## Challenges & Fixes

| Challenge | Solution |
|-----------|----------|
| ICM-20948 not working | Switched to MPU-6050 |
| Servo jitter | Added low-pass filter (ALPHA 0.15) |
| Servo buzzing at level | Added deadband (0.8°) |
| Pin 8 not working with servo | Switched to Pin 5, 6, 9, 10 |
| MPU not responding | Fixed wiring, added debug code |
| Servos moving same direction | Used mirror mounting logic |
| I2C hanging | Added pull-up resistors |
| SBUS receiver not reading | Installed sbus library, used pin 3 |

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
- [ ] Airspeed sensor integration
- [ ] Professional barometer (BMP390/MS5611)

---

## Future Funding & BOM

With funding from Stardance, my sensor suite will become a beast. The funding will help me purchase high-quality components to fully test and validate the Teensy 4.1 flight controller in real flight conditions.

### Full BOM

| # | Item | Description | Qty | Price (AED) | Price (USD) | Link |
|---|------|-------------|-----|-------------|-------------|------|
| 1 | SLONWAKE 1W VTX + 1500TVL Camera | 5.8GHz 48CH FPV Transmitter | 1 | 151.95 | 41.36 | 🔗 |
| 2 | GY-63 MS5611 Barometer | High Precision Air Pressure Sensor | 1 | 16.69 | 4.54 | 🔗 |
| 3 | MS4525DO Airspeed Sensor | Differential Pressure Module w/ Pitot Tube | 1 | 107.19 | 29.18 | 🔗 |
| 4 | 4S 3000mAh LiPo Battery | 14.8V 60C RC Battery w/ XT60 | 1 | 141.86 | 38.62 | 🔗 |
| 5 | SX1278 LoRa Ra-01 Module | 433MHz Long-range Telemetry (Pack of 2) | 2 | 19.60 | 5.34 | 🔗 |
| 6 | BSS138 Logic Level Converter | Bi-Directional 4-Channel 3.3V-5V | 1 | 10.00 | 2.72 | 🔗 |
| 7 | MPU-9250 9-Axle IMU | Gyro + Accelerometer + Magnetometer | 1 | 20.00 | 5.44 | 🔗 |
| 8 | BMP280 Barometer | Temp + Humidity + Pressure (3.3V) | 1 | 6.02 | 1.64 | 🔗 |
| 9 | AliExpress Shipping | Shipping Fee | 1 | 32.28 | 8.79 | - |
| 10 | UAE Import Tax & Fees | Estimated Import Tax + Clearance | 1 | 40.00 | 10.90 | - |
| | **TOTAL ITEMS** | | | **545.59** | **148.57** | |
| | **SHIPPING + TAX** | | | **72.28** | **19.69** | |
| | **GRAND TOTAL** | | | **617.87** | **168.26** | |

*Exchange Rate: 1 USD = 3.6725 AED*

### What This Funding Will Unlock

- Complete Teensy 4.1 flight controller with long-range FPV
- Full sensor suite (IMU, barometer, airspeed, telemetry)
- Real flight testing and validation
- Open-source release of all firmware and schematics

---

## Equipment Status

| Component | Status | Source |
|-----------|--------|--------|
| Teensy 4.1 | **BORROWED** | Tutor (3 months) |
| ICM-20948 | **BORROWED** | Tutor (3 months) |
| MPU-6050 | Owned | - |
| Arduino Uno | Owned | - |
| NEO-M8N GPS | Owned | - |
| E-flite Apprentice S1E | **BROKEN** | Crashed, used for bench testing |
| Servos (4x) | Owned | From old plane |
| 7A UBEC | Owned | - |
| ESC | Owned | - |
| RadioLink T12D + R12F | Owned | Recently purchased |

**Special Thanks:** A huge thank you to my tutor for lending me the expensive components (Teensy 4.1, ICM-20948). Without their support, this project would not be possible.

---

## 🛩️ Testing Plan

Once the flight controller is fully assembled and tested on the bench, I will borrow a friend's RC plane to suit this all up and test it in real flight conditions. If everything goes according to plan, I will post a video of the flight. And hopefully, it won't crash lol.

---

## Contributing

This is open-source and contributions are welcome.

### How to Contribute

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push and open a Pull Request

### Areas Needing Help

- Testing on different hardware
- Documentation improvements
- PCB design
- Sensor fusion algorithms
- Telemetry protocols

---

## Author

**Rithish** — 16-year-old maker with a passion for flight and embedded systems

- **GitHub:** [github.com/R1th1shwork](https://github.com/R1th1shwork)
- **Project:** [github.com/R1th1shwork/TFCS-1](https://github.com/R1th1shwork/TFCS-1)
- **Stardance:** [stardance.hackclub.com/projects/49798](https://stardance.hackclub.com/projects/49798)

---

## Acknowledgments

- **My Tutor** — For lending critical components
- **The Arduino Community** — For open-source libraries and support
- **The Teensy Community** — For the incredible Teensy platform

---

## Disclaimer

> This project is for educational and experimental purposes only. Always test flight hardware thoroughly before actual flight operations. The authors are not responsible for any damages or injuries resulting from the use of this hardware or software.

---

<p align="center">
  <i>Built with passion, powered by curiosity, and tested on borrowed equipment.</i><br>
  <b>Fly safe, have fun, and learn something new.</b>
</p>

<p align="right"><i>Last Updated: August 2026</i></p>
