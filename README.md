# SIG Embedded Systems Workshop

A repository containing beginner to intermediate firmware experiments and microcontroller sketches designed for the Special Interest Group (SIG) Embedded Systems Workshop.

---

## Overview

This repository provides clean, modular, and well-documented C++ Arduino sketches demonstrating foundational digital input/output operations, event handling, and noise filtering on microcontrollers (Arduino Uno, ESP32, ESP8266, or compatible boards).

---

## Included Sketches

### 1. Basic LED Blink (`1.ino`)
- **Objective**: Introduce basic digital output interfacing, GPIO configuration, and microcontroller timing.
- **Behavior**: Drives a GPIO pin to alternate between digital HIGH and LOW states at a 1000 ms periodic interval, cycling an LED on and off.
- **Key Concepts**:
  - GPIO output mode configuration (`OUTPUT`)
  - Digital state driving (`HIGH` / `LOW`)
  - Blocking execution timing (`delay`)

### 2. Push Button Toggle with Software Debounce (`2.ino`)
- **Objective**: Read physical momentary switch inputs reliably without false triggers from mechanical contact bounce.
- **Behavior**: Toggles the LED power state each time the user presses a momentary push button. Subsequent presses switch the LED between active and inactive states.
- **Key Concepts**:
  - Active-LOW input with internal pull-up resistor (`INPUT_PULLUP`)
  - Non-blocking timing checks (`millis`)
  - Mechanical noise filtering with a 50 ms debounce window
  - State edge detection (triggering specifically on the falling edge / press transition)

---

## Hardware Requirements

| Component | Quantity | Purpose |
| :--- | :---: | :--- |
| Microcontroller Board (Arduino / ESP32 / ESP8266) | 1 | Main control unit |
| Light Emitting Diode (LED) | 1 | Visual output indicator |
| Current-Limiting Resistor (220Ω - 330Ω) | 1 | Protects the LED from excessive current |
| Momentary Tactile Push Button | 1 | Physical user input |
| Solderless Breadboard | 1 | Circuit prototyping surface |
| Jumper Wires | Several | Interconnecting pins and breadboard rails |

---

## Circuit Connection Reference

### Experiment 1: LED Blink Wiring

| Component Terminal | Microcontroller Connection | Notes |
| :--- | :--- | :--- |
| LED Anode (Long Leg) | GPIO Pin 2 | Via 220Ω current-limiting resistor |
| LED Cathode (Short Leg) | GND (Ground) | Direct connection to ground rail |

> **Note**: Pin 2 also corresponds to the on-board user LED on many standard ESP32 development modules.

### Experiment 2: Push Button & LED Wiring

| Component | Pin / Terminal | Target Connection | Circuit Logic |
| :--- | :--- | :--- | :--- |
| **Push Button** | Terminal A | GPIO Pin 4 | Digital input line |
| **Push Button** | Terminal B | GND (Ground) | Pulls line LOW when pressed |
| **LED** | Anode (+) | GPIO Pin 2 (via 220Ω) | Controlled output line |
| **LED** | Cathode (-) | GND (Ground) | Common circuit return |

---

## Theory of Operation

### Software Debouncing
Mechanical switches contain spring-loaded metal contacts. When pressed or released, these contacts physically bounce against one another for several milliseconds before establishing a steady electrical connection. To a high-speed microcontroller clock, this rapid bouncing looks like dozens of rapid button presses within a fraction of a second.

The debouncing algorithm filters this behavior:
1. Detects an initial change in voltage level on the input pin.
2. Starts a software timer reference using the system clock counter.
3. Ignores further fluctuations until the signal remains steady for at least the specified threshold duration (50 milliseconds).
4. Commits the stable state change and toggles the LED output only once per physical press.

### Internal Pull-Up Resistors
Using the microcontroller's internal pull-up eliminates the need for external pull-up resistors on the breadboard:
- **Button Idle (Unpressed)**: The internal resistor holds the pin steadily at HIGH (3.3V / 5V).
- **Button Active (Pressed)**: Pressing the button bridges the pin directly to GND, pulling the reading to LOW.

---

## Getting Started in Arduino IDE

1. **Open the Project**: Launch the Arduino IDE desktop application and open either `1.ino` or `2.ino`.
2. **Select Board**: Navigate through the top application menu to **Tools** > **Board** and choose your connected microcontroller model.
3. **Select Communication Port**: Under **Tools** > **Port**, highlight the serial communication port assigned to your plugged-in development board.
4. **Compile and Flash**: Click the **Verify** checkmark icon to validate the code, followed by the **Upload** arrow icon to transfer the binary firmware onto the target board.
5. **Observe**: Verify physical operation on the breadboard or on-board indicators.
