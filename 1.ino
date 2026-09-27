/*
 * Project: SIG Workshop - Experiment 1
 * Title: Basic LED Blink
 * Description: Demonstrates basic digital output control by toggling an LED on and off
 *              at 1-second intervals.
 * 
 * Hardware Setup:
 *   - Microcontroller (Arduino Uno / ESP32 / ESP8266)
 *   - LED anode connected to Pin 2 (through a 220-330 ohm current limiting resistor)
 *   - LED cathode connected to GND
 *   (Note: Pin 2 is also commonly the built-in LED on many ESP32 development boards)
 */

// Pin definition
const uint8_t LED_PIN = 2;

// Blink interval in milliseconds
const unsigned long BLINK_INTERVAL_MS = 1000;

void setup() {
  // Initialize digital pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Turn the LED ON (HIGH voltage level)
  digitalWrite(LED_PIN, HIGH);
  delay(BLINK_INTERVAL_MS);

  // Turn the LED OFF (LOW voltage level)
  digitalWrite(LED_PIN, LOW);
  delay(BLINK_INTERVAL_MS);
}
