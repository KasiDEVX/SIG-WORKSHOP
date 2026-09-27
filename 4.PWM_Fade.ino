/*
 * Project: SIG Workshop - Experiment 4
 * Title: PWM Fade (Pulse Width Modulation)
 * Description: Smoothly fades an LED between minimum and maximum brightness using
 *              hardware Pulse Width Modulation (PWM) duty cycle control.
 * 
 * Hardware Setup:
 *   - LED Anode (Long Leg): Connected to PWM-capable Pin 9 (through a 220-330 ohm resistor)
 *   - LED Cathode (Short Leg): Connected to GND
 *   (Note: Pin 9 is PWM-enabled on Arduino Uno; on ESP32, use any PWM-capable GPIO like Pin 2)
 */

// Pin Definitions (must be a PWM-capable pin, marked with ~ on Arduino boards)
const uint8_t LED_PIN = 9;

// Brightness and Fading Configuration
int brightness = 0;              // Current LED brightness level (0 = Off, 255 = Full Brightness)
int fadeAmount = 5;              // Increment step for brightness change per cycle
const unsigned long FADE_STEP_DELAY_MS = 30; // Delay between brightness steps (controls fade speed)

void setup() {
  // Configure the PWM pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Set LED brightness by outputting an 8-bit PWM duty cycle (0 to 255)
  analogWrite(LED_PIN, brightness);

  // Adjust brightness for the next iteration
  brightness += fadeAmount;

  // Reverse fading direction at lower and upper brightness boundaries
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }

  // Brief pause to establish human-visible fade animation speed
  delay(FADE_STEP_DELAY_MS);
}
