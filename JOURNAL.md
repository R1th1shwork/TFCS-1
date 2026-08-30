# TFCS-1 Project Journal

**Project:** TFCS-1: Teensy Flight Computer & Climate Suite  
**Author:** Rithish (16-year-old maker)  
**Total Time Spent:** ~10 hours 17 minutes (logged)

---

## 📖 About This Journal

This journal documents the complete journey of building TFCS-1 - from unboxing the Teensy 4.1 to finalizing the BOM for Stardance submission. Every dev log represents a real session of work, including successes, failures, and lessons learned.

---

## Dev Log #15 - MPU + SBUS + PID Code Ready!

**Date:** August 30, 2026  
**Time Spent:** 39m  
**✅ Checklist:**
- [x] Full MPU + SBUS + PID code written
- [x] Code uploaded to GitHub
- [x] MB102 power supply researched
- [ ] Aileron testing (tomorrow)

**Details:**  
Wrote and uploaded the full MPU + SBUS + PID code to GitHub. Got roll and pitch data from MPU, sticks from RadioLink, and PID corrections calculated. Tomorrow I'll test it properly with just the ailerons to check if the self-correcting actually works. Also did some research on the MB102 power supply and the Uno to see if it helps with bench testing. Just research for now, nothing tested yet. But good progress overall. More testing tomorrow.

---

## Dev Log #14 - Mercury OS Planning (Travel Mode)

**Date:** August 29, 2026  
**Time Spent:** 18m  
**✅ Checklist:**
- [x] Mercury OS planned out
- [x] Failsafe priority system designed
- [x] Notes taken for all features
- [ ] Code implementation (pending)

**Details:**  
Traveling right now so no hardware today, had to work with my phone but I used the time to plan out my own FC OS called Mercury and also how safefail priority is a main thing. Just planned out and took notes but the plans and the direction is solid. The OS will handle failsafe first, then flight control, sensor fusion, telemetry, logging, and housekeeping in a priority-based system.

---

## Dev Log #13 - Shifted Focus & Resubmitted!

**Date:** August 28, 2026  
**Time Spent:** ~45m  
**✅ Checklist:**
- [x] Project direction shifted from airframe to flight controller
- [x] BOM completely redesigned
- [x] README updated with new focus
- [x] JOURNAL updated
- [x] KiCad schematic uploaded
- [x] Funding resubmitted for $147.50 USD

**Details:**  
After reading the Stardance feedback, I completely shifted my project direction. Instead of building an airframe, I am now focusing entirely on the flight controller itself. I updated everything - BOM, README, journal, schematic, code. Just resubmitted the funding request for $147.50 USD. This funding will help me build a proper Teensy 4.1 flight controller with IMU, airspeed, barometer, telemetry and FPV. I really hope this gets approved. Fingers crossed.

---

## Dev Log #12 - Finalizing Everything For Submission!

**Date:** August 27, 2026  
**Time Spent:** 40m 55s  
**✅ Checklist:**
- [x] BOM finalized with all components
- [x] Prices in both AED and USD
- [x] Sensor list locked in

**Details:**  
Busy day today! Got the final BOM ready with all components, links, and prices in both AED and USD. Total comes to ~$147.50 USD including shipping and import tax. Finally locked in the sensor list: MPU-9250 for orientation, BMP280 and MS5611 for altitude, MS4525DO for airspeed, and the SLONWAKE 1W VTX for long-range FPV. Also got the logic level converter from Noon to safely connect everything to the Teensy. Tomorrow is the big day - gotta upload everything to GitHub for the Stardance submission. Need to add the BOM CSV, the README, the journal, and the demo videos. Still need to figure out the CAD/STEP file situation and the wiring diagram. Feeling good about where the project is at. One more push and it's done!

---

## Dev Log #11 - Radio Receiver Is Alive!

**Date:** August 26, 2026  
**Time Spent:** 21m  
**✅ Checklist:**
- [x] RadioLink receiver wired up
- [x] SBUS signal to pin 3
- [x] All 6 channels reading in Serial Monitor

**Details:**  
Finally got the RadioLink receiver working with the Arduino! Connected the SBUS signal to pin 3 and got all 6 channels showing up in the Serial Monitor. Aileron, Elevator, Throttle, Rudder, and switches all reading properly. Took forever to figure out the wiring and the right library but it's done now. Next step is merging the MPU data with the radio input so the flight controller can correct my sticks and keep the plane stable. Both systems work separately, now just gotta combine them. Feels good to finally have a real transmitter.

---

## Dev Log #10 - Funding Submitted!

**Date:** August 25, 2026  
**Time Spent:** 49m 50s  
**✅ Checklist:**
- [x] Stardance funding request submitted
- [x] $260 USD requested
- [x] BOM ready

**Details:**  
Just submitted the Stardance funding request for $260 USD. This is it man. If it gets approved, the dream build becomes real. Xfly X1300 airframe, 4S battery, motor, ESC, servos - everything I need. Teensy 4.1 and ICM-20948 are already borrowed from my tutor. The Apprentice is wrecked anyway so the X1300 will be the real deal. Been working on this for weeks. Soldering, coding, troubleshooting, failing, fixing, learning. This is the moment it all comes together. Fingers crossed.

---

## Dev Log #9 - README Done, Video Tomorrow, BOM Ready!

**Date:** August 24, 2026  
**Time Spent:** 53m  
**✅ Checklist:**
- [x] GitHub README updated
- [x] BOM list finalized
- [x] Dev logs removed from README

**Details:**  
Finally got the GitHub README fully updated, cleaned it up, removed the old dev logs, added the BOM as a future funding plan for Stardance, mentioned the Apprentice is broken and just a test body now, and put in notes about schematics and code coming soon. Also finalized the BOM list with all components and links in both AED and USD. Tomorrow I'm filming the Stardance demo video showing the bench setup with the MPU-6050 data streaming and servos moving. Feeling pretty good about where this project is heading. Just need to film that video and then we can focus on the Teensy 4.1 integration and getting everything on the actual airframe.

---

## Dev Log #8 - Back in Action

**Date:** August 23, 2026  
**Time Spent:** 1h 17m  
**✅ Checklist:**
- [x] Uno coded for rudder + ailerons
- [x] Both surfaces responding to MPU
- [x] README updated

**Details:**  
Back home finally! Got back to work on the TFCS-1. Coded the Uno to work with rudder and ailerons together - both control surfaces responding to MPU data now. Still need to test them all together on the actual airframe but the code logic is solid. Also updated the README on GitHub with all the project details, hardware specs, dev logs, and the whole story behind this build. Feels good to have proper documentation now. Next step is testing everything together on the bench and then moving to the Teensy 4.1 integration.

---

## Dev Log #7 - Travel Mode

**Date:** August 22, 2026  
**Time Spent:** 25m  
**✅ Checklist:**
- [x] Power system planned
- [x] ESC BEC → servos
- [x] UBEC → Teensy

**Details:**  
Traveling right now so no hardware today. But honestly still made progress. Planned out the whole power system - ESC BEC will power the servos and UBEC will power the Teensy. Both from the same battery with all grounds tied together. Got the code ready to test once I'm back home. Everything is planned out, just need to actually build it when I return. Really really want that plane man. Let's see.

---

## Dev Log #6 - Research Day

**Date:** August 21, 2026  
**Time Spent:** 27m  
**✅ Checklist:**
- [x] Researched airframes
- [x] X1300 identified as target

**Details:**  
Kinda felt off today so I didn't work on it much but I did some research on the airframe which I wanna actually test my systems on... TAAAADAA X1300 looks cool right?

---

## Dev Log #5 - Flight Controller Is Alive!

**Date:** August 20, 2026  
**Time Spent:** 42m  
**✅ Checklist:**
- [x] MPU-6050 reading roll data
- [x] Both wing servos working
- [x] Left wing UP on left tilt
- [x] Right wing DOWN on left tilt

**Details:**  
WE DID IT! The flight controller is officially WORKING! MPU-6050 is reading roll data and both wing servos move exactly how they should. Tilt left and left wing goes UP, right wing goes DOWN. Tilt right and left wing goes DOWN, right wing goes UP. It's beautiful watching them fight to keep the board level. Finally figured out the servo pin thing - pins 9 and 10 are the way to go, pin 8 was dead for some reason. Both servos get the same signal but since they're physically mirrored on the plane, one goes up and the other goes down. That's actually genius lol. Spent way too long on this but it's finally done.

---

## Dev Log #4 - Salvaged Wings!

**Date:** August 19, 2026  
**Time Spent:** 32m 53s  
**✅ Checklist:**
- [x] Wings salvaged from old plane
- [x] Left wing on pin 9
- [x] Right wing on pin 10
- [x] 40-90-140 deg movement

**Details:**  
Pulled out the wings from my old RC plane that's been sitting in the garage forever. Took the servos off them and tested both sides - left and right wings working smooth on pins 9 and 10. 90° neutral, 40° up, 140° down. No binding or breaking. Tomorrow we're adding the MPU to make them actually respond to the plane tilting. Old plane parts getting a new brain.

---

## Dev Log #3 - Data Is Flowing!

**Date:** August 18, 2026  
**Time Spent:** 21m  
**✅ Checklist:**
- [x] MPU-6050 working
- [x] Roll and pitch data streaming
- [x] Serial Monitor showing data

**Details:**  
I GOT DATA! MPU-6050 is streaming roll and pitch like crazy on the Serial Monitor. No servos yet but the numbers are moving when I tilt the board so that's a huge W. Next step is gonna be connecting this thing to the actual plane and seeing if the Uno can handle powering the servos without burning itself out lol. But for now we got data and that's what matters.

---

## Dev Log #2 - The Resistor Reality Check

**Date:** August 17, 2026  
**Time Spent:** 20m  
**✅ Checklist:**
- [x] ICM-20948 found at 0x68
- [x] Still hangs on read

**Details:**  
Came back today, tried the ICM again, still doesn't work without resistors. Spent like 15 minutes on it, ran the scanner, sensor shows up at 0x68 but still hangs when I try to read data. Same problem as yesterday. Need those 4.7kΩ pull-up resistors. Gonna order them and try again later. At least the Teensy still works lol.

---

## Dev Log #1 - A Brand New Day

**Date:** August 16, 2026  
**Time Spent:** 1h 7m  
**✅ Checklist:**
- [x] Teensy 4.1 unboxed and tested
- [x] Orange LED blinking
- [x] Serial Monitor working

**Details:**  
So today was the first real day of the TFCS-1 project and honestly it was a mix of hype and headache lol. I finally got my hands on a Teensy 4.1 from an old tutor of mine who lent it to me for a few weeks which is insane because this is literally the microcontroller I've been dreaming about for months. Plugged it in, got the orange LED blinking, uploaded a test sketch, and saw my messages pop up in the Serial Monitor so I know the board is alive and working which felt amazing. Then I tried wiring up the ICM-20948 IMU that he also lent me and uh yeah that didn't go so well. The I2C scanner couldn't find anything no matter what address I tried or how many times I rewired it. Tried it on an Arduino Uno first to avoid frying the Teensy and still nothing. Might be dead, might need a logic level converter, might just be my bad wiring I don't even know anymore lol. But you know what the Teensy works and that's what matters right now. Gonna take a break, sleep on it, and figure out the sensor stuff tomorrow.

---

## 📊 Summary

| Category | Total |
|----------|-------|
| **Total Time Logged** | ~10 hours 17 minutes |
| **Dev Log Entries** | 15 |
| **Days Worked** | 15 days |
| **Key Milestones** | Teensy working, MPU-6050 working, Servos working, RadioLink working, BOM finalized, Project shift complete, Mercury OS planned |

---

## 🎯 Key Milestones Achieved

| Milestone | Dev Log | Date |
|-----------|---------|------|
| Teensy 4.1 powered on | #1 | Aug 16 |
| ICM-20948 troubleshooting | #1, #2 | Aug 16-17 |
| MPU-6050 working | #3 | Aug 18 |
| Servos responding | #4, #5 | Aug 19-20 |
| RadioLink receiver working | #11 | Aug 26 |
| BOM finalized | #12 | Aug 27 |
| Project shift & resubmitted | #13 | Aug 28 |
| Mercury OS planned | #14 | Aug 29 |
| MPU + SBUS + PID code ready | #15 | Aug 30 |

---

## 💡 Lessons Learned

1. **Always check voltage levels** - Teensy is 3.3V, not 5V tolerant!
2. **Pull-up resistors matter** - ICM-20948 needs 4.7kΩ on SDA/SCL
3. **Test individual components first** - Debug one thing at a time
4. **Document everything** - Dev logs help track progress
5. **Ask for help** - My tutor lending me parts made this possible
6. **Failure is part of learning** - The ICM didn't work, but switching to MPU-6050 got results
7. **Listen to feedback** - Shifting project direction based on Stardance feedback was the right call
8. **Plan before coding** - Mercury OS planning saved time and confusion

---

## 🙏 Acknowledgments

- **My Tutor** - For lending me the Teensy 4.1, ICM-20948, and other components
- **The Arduino Community** - For open-source libraries and support
- **The Teensy Community** - For the incredible Teensy platform

---

*Built with passion, powered by curiosity, and tested on borrowed equipment.*  
*Fly safe, have fun, and learn something new.*

---

**Last Updated:** August 30, 2026
