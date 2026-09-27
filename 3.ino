/*
 * Project: SIG Workshop - Experiment 3
 * Title: Analog Read (ADC Interfacing)
 * Description: Reads variable voltage from an analog source (such as a potentiometer
 *              or analog sensor) using the microcontroller's Analog-to-Digital
 *              Converter (ADC) and outputs raw and voltage values via Serial.
 * 
 * Hardware Setup:
 *   - Potentiometer Terminal 1: Connected to 5V (or 3.3V for 3.3V microcontrollers)
 *   - Potentiometer Wiper (Center Pin): Connected to Analog Pin A0 (or GPIO 34 on ESP32)
 *   - Potentiometer Terminal 2: Connected to GND
 */

// Pin Definitions
const uint8_t ANALOG_PIN = A0;

// Serial Communication Baud Rate
const unsigned long SERIAL_BAUD_RATE = 9600;

// Microcontroller Operating Reference Voltage (5.0V for Uno, 3.3V for ESP32/ESP8266)
const float REFERENCE_VOLTAGE = 5.0;

// ADC Resolution (10-bit: 1023.0 for Arduino Uno; 12-bit: 4095.0 for ESP32)
const float ADC_MAX_VALUE = 1023.0;

// Sampling Interval
const unsigned long SAMPLE_INTERVAL_MS = 250;

void setup() {
  // Initialize serial communication for data logging
  Serial.begin(SERIAL_BAUD_RATE);
}

void loop() {
  // Read raw 10-bit integer from the ADC (range: 0 to 1023)
  int rawValue = analogRead(ANALOG_PIN);

  // Convert raw digital reading to corresponding physical voltage
  float voltage = (rawValue * REFERENCE_VOLTAGE) / ADC_MAX_VALUE;

  // Print formatted readings to Serial Monitor
  Serial.print("Raw ADC Value: ");
  Serial.print(rawValue);
  Serial.print(" | Measured Voltage: ");
  Serial.print(voltage, 2);
  Serial.println(" V");

  // Delay before the next measurement sample
  delay(SAMPLE_INTERVAL_MS);
}
