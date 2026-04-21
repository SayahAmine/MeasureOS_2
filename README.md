# MeasureOS_2 - Mini OS Version

## Description
This project is a mini operating system simulation written in C.  
It monitors a patient’s temperature using data sent from an Arduino Uno and reacts based on predefined thresholds.

---

## Objective
Simulate a simple RTOS-like system with:
- modular structure
- kernel-style processing
- real-time event handling

---

## System Architecture

The project is divided into modules:

- **main.c** → system start (boot)
- **Kernel.c** → core logic (decision making)
- **serial.c** → communication with Arduino (COM port)
- **sensors.c** → temperature parsing and detection
- **injector.c** → treatment action (Inject_Trait)
- **events.h** → event structure

---

## How it works

Arduino sends temperature values like:<img width="1920" height="1008" alt="Screenshot 2026-04-19 225801" src="https://github.com/user-attachments/assets/cfdd3976-90cb-4094-9a98-97a074c79531" />
