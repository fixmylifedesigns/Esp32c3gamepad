#include <Arduino.h>
#include <BleGamepad.h> // https://github.com/lemmingDev/ESP32-BLE-Gamepad

// Define pins for each button
#define BUTTON_PIN_1 0
#define BUTTON_PIN_2 1
#define BUTTON_PIN_3 2
#define BUTTON_PIN_4 3
#define BUTTON_PIN_5 4
#define BUTTON_PIN_6 5
#define BUTTON_PIN_7 6
#define BUTTON_PIN_8 7
#define BUTTON_PIN_9 8
#define BUTTON_PIN_10 9
#define BUTTON_PIN_11 10

BleGamepad bleGamepad("StealthWork Pad", "Espressif", 100);

// Track the previous state of each button
int previousButtonState[11] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};

// Define pin numbers and corresponding button mappings
const int buttonPins[11] = {BUTTON_PIN_1, BUTTON_PIN_2, BUTTON_PIN_3, BUTTON_PIN_4, BUTTON_PIN_5,
                            BUTTON_PIN_6, BUTTON_PIN_7, BUTTON_PIN_8, BUTTON_PIN_9, BUTTON_PIN_10, BUTTON_PIN_11};
const int buttonMapping[11] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5,
                               BUTTON_6, BUTTON_7, BUTTON_8, BUTTON_9, BUTTON_10, BUTTON_11};

void setup() {
    // Configure each button pin as input with pull-up resistor
    for (int i = 0; i < 11; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }

    // Initialize BLE gamepad
    bleGamepad.begin();
}

void loop() {
    if (bleGamepad.isConnected()) {
        // Check each button
        for (int i = 0; i < 11; i++) {
            int currentButtonState = digitalRead(buttonPins[i]);

            if (currentButtonState != previousButtonState[i]) {
                if (currentButtonState == LOW) {
                    bleGamepad.press(buttonMapping[i]); // Press button
                } else {
                    bleGamepad.release(buttonMapping[i]); // Release button
                }
                previousButtonState[i] = currentButtonState;
            }
        }
    }
}
