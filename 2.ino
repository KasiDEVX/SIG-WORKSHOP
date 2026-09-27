/*
 * Project: SIG Workshop - Experiment 2
 * Title: Push Button Toggle with Software Debounce
 * Description: Toggles the state of an LED each time a momentary push button is pressed.
 *              Uses non-blocking software debouncing to filter out mechanical button noise.
 * 
 * Hardware Setup:
 *   - Button connected between Pin 4 and GND (uses internal pull-up resistor; active LOW)
 *   - LED connected to Pin 2 (through a 220-330 ohm resistor to GND)
 */

// Pin Definitions
const uint8_t BUTTON_PIN = 4;
const uint8_t LED_PIN = 2;

// State Variables
bool ledState = false;          // Current state of the LED (false = LOW, true = HIGH)
int buttonState = HIGH;         // Current debounced reading of the input pin
int lastButtonState = HIGH;     // Previous raw reading from the input pin

// Debounce Timing Parameters
unsigned long lastDebounceTime = 0;             // Timestamp of the last raw state transition
const unsigned long DEBOUNCE_DELAY_MS = 50;     // Debounce filter threshold (milliseconds)

void setup() {
  // Configure button pin with internal pull-up (reads HIGH when unpressed, LOW when pressed)
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Configure LED pin as digital output
  pinMode(LED_PIN, OUTPUT);

  // Apply initial LED state
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);
}

void loop() {
  // Read current physical state of the button
  int reading = digitalRead(BUTTON_PIN);

  // Check if the physical button switch state changed (due to noise or pressing)
  if (reading != lastButtonState) {
    // Reset the debouncing timer
    lastDebounceTime = millis();
  }

  // Once the reading has been stable for longer than the debounce delay, process the state
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY_MS) {
    // If the button state has truly changed
    if (reading != buttonState) {
      buttonState = reading;

      // Trigger only on the press event (transition to LOW for active-LOW circuit)
      if (buttonState == LOW) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? HIGH : LOW);
      }
    }
  }

  // Save the current reading for the next loop cycle
  lastButtonState = reading;
}
