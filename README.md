# SIG Embedded Systems Workshop

A repository containing beginner to intermediate firmware experiments and microcontroller sketches designed for the Special Interest Group (SIG) Embedded Systems Workshop.

---

## Overview

This repository provides clean, modular, and well-documented C++ Arduino sketches demonstrating foundational digital and analog input/output operations, event handling, signal filtering, analog-to-digital conversion, and pulse width modulation on microcontrollers (Arduino Uno, ESP32, ESP8266, or compatible boards).

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

### 3. Analog Read (`3.ino`)
- **Objective**: Measure continuous analog electrical signals using the microcontroller's onboard Analog-to-Digital Converter (ADC).
- **Behavior**: Reads the variable voltage produced by a potentiometer divider, converts the digital quantization levels into real-world voltage values, and logs the measurements over the Serial connection.
- **Key Concepts**:
  - Analog input sampling (`analogRead`)
  - ADC quantization and resolution (10-bit: 0 to 1023)
  - Voltage conversion math based on operating reference voltage
  - Serial monitor telemetry transmission (`Serial.begin`, `Serial.print`)

### 4. PWM Fade (`4.ino`)
- **Objective**: Simulate variable analog output voltage using digital Pulse Width Modulation (PWM) to control actuator intensity.
- **Behavior**: Smoothly increases and decreases an LED's perceived brightness from fully dark to full luminosity in a continuous breathing loop.
- **Key Concepts**:
  - Pulse Width Modulation duty cycle control (`analogWrite`)
  - 8-bit resolution brightness scale (0 to 255)
  - Direction inversion algorithm for cyclic boundaries
  - Frame delay animation timing

---

## Hardware Requirements

| Component | Quantity | Purpose |
| :--- | :---: | :--- |
| Microcontroller Board (Arduino Uno / ESP32 / ESP8266) | 1 | Main control unit |
| Light Emitting Diode (LED) | 1 | Visual output indicator |
| Current-Limiting Resistor (220Ω - 330Ω) | 1 | Protects the LED from excessive current |
| Momentary Tactile Push Button | 1 | Physical digital input switch |
| Rotary Potentiometer (10kΩ recommended) | 1 | Variable analog voltage source |
| Solderless Breadboard | 1 | Circuit prototyping surface |
| Jumper Wires | Several | Interconnecting pins and breadboard rails |

---

## Circuit Connection Reference

### Experiment 1: LED Blink Wiring

| Component Terminal | Microcontroller Connection | Notes |
| :--- | :--- | :--- |
| LED Anode (Long Leg) | GPIO Pin 2 | Via 220Ω current-limiting resistor |
| LED Cathode (Short Leg) | GND (Ground) | Direct connection to ground rail |

> **Note**: Pin 2 corresponds to the on-board user LED on many standard ESP32 development modules.

### Experiment 2: Push Button & LED Wiring

| Component | Pin / Terminal | Target Connection | Circuit Logic |
| :--- | :--- | :--- | :--- |
| **Push Button** | Terminal A | GPIO Pin 4 | Digital input line |
| **Push Button** | Terminal B | GND (Ground) | Pulls line LOW when pressed |
| **LED** | Anode (+) | GPIO Pin 2 (via 220Ω) | Controlled output line |
| **LED** | Cathode (-) | GND (Ground) | Common circuit return |

### Experiment 3: Potentiometer (Analog Read) Wiring

| Component | Pin / Terminal | Target Connection | Description |
| :--- | :--- | :--- | :--- |
| **Potentiometer** | Outer Terminal 1 | 5V (or 3.3V) | High reference voltage rail |
| **Potentiometer** | Center Wiper Pin | Analog Pin A0 | Variable analog voltage output |
| **Potentiometer** | Outer Terminal 2 | GND (Ground) | Low reference ground rail |

> **Note**: For ESP32 boards, connect the wiper to an ADC-capable GPIO (such as GPIO 34 or GPIO 36).

### Experiment 4: PWM Fade LED Wiring

| Component Terminal | Microcontroller Connection | Notes |
| :--- | :--- | :--- |
| LED Anode (Long Leg) | PWM Pin 9 | Via 220Ω resistor (marked with `~` on Uno) |
| LED Cathode (Short Leg) | GND (Ground) | Direct connection to ground rail |

> **Note**: On ESP32 boards, hardware PWM is supported across any standard digital GPIO (such as GPIO 2 or GPIO 18).

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

### Analog-to-Digital Conversion (ADC)
Microcontrollers are digital devices operating on binary 0s and 1s, but real-world signals (sound, light, position) are continuous and analog.
- An **ADC** measures the continuous incoming voltage and maps it to a discrete digital value.
- An Arduino Uno uses a 10-bit ADC, partitioning the 0V to 5V input range into 1024 discrete steps (0 through 1023).
- Each discrete step represents approximately 4.88 millivolts (5.0V / 1024).

### Pulse Width Modulation (PWM)
Standard microcontrollers lack native Digital-to-Analog Converters (DAC) on most pins. To simulate variable voltages (e.g., dimming an LED or throttling motor speed), **PWM** switches a digital pin rapidly between full ON and full OFF at a high frequency.
- The ratio of the ON time relative to the total cycle time is known as the **duty cycle**.
- An 8-bit PWM scale ranges from 0 (0% duty cycle, completely off) to 255 (100% duty cycle, fully on).
- Because human eyes perceive high-speed light flicker as an average intensity, varying the duty cycle smoothly changes the perceived brightness.

---

## Getting Started in Arduino IDE

1. **Open the Project**: Launch the Arduino IDE desktop application and open any desired experiment sketch (`1.ino`, `2.ino`, `3.ino`, or `4.ino`).
2. **Select Board**: Navigate through the top application menu to **Tools** > **Board** and choose your connected microcontroller model.
3. **Select Communication Port**: Under **Tools** > **Port**, highlight the serial communication port assigned to your plugged-in development board.
4. **Compile and Flash**: Click the **Verify** checkmark icon to validate the code, followed by the **Upload** arrow icon to transfer the binary firmware onto the target board.
5. **View Serial Telemetry (Experiment 3)**: Open **Tools** > **Serial Monitor** (or click the magnifying glass icon in the top right corner) and set the baud rate dropdown to **9600 baud** to view real-time ADC readings.
