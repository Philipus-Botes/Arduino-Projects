# Arduino Morse Code Reader

A simple Morse code input and translation system using an Arduino Uno, a 16x2 I2C LCD, and two push buttons. The user inputs Morse code using one button (short press for dot `.` and long press for dash `-`), and presses a second button to submit and translate it into English.

If the translated phrase is too long for the screen, the message will scroll automatically. Pressing the submit button again resets the system for new Morse input.

## Features

- Single-button Morse input with press duration detection
- Real-time display of Morse input
- Translation to English using second button
- Auto-scroll display for long text
- Reset and re-translate with one click

## Components Used

- Arduino Uno (or compatible)
- 16x2 I2C LCD Display
- 2x Push Buttons
- Breadboard & Jumper Wires
- USB Cable (for programming and serial monitor)

## Wiring Guide

| Component         | Arduino Pin     | Notes                        |
|------------------|------------------|------------------------------|
| Morse Button      | Digital Pin 2     | Use `INPUT_PULLUP` mode      |
| Submit Button     | Digital Pin 3     | Use `INPUT_PULLUP` mode      |
| I2C LCD - VCC     | 5V                | Power supply                 |
| I2C LCD - GND     | GND               | Ground                       |
| I2C LCD - SDA     | A4                | I2C Data                     |
| I2C LCD - SCL     | A5                | I2C Clock                    |

## Usage

1. Upload the sketch to your Arduino.
2. Open the Serial Monitor (9600 baud) to observe debug messages (optional).
3. Press the Morse button briefly for dot (`.`), hold for dash (`-`).
4. After entering characters, press the submit button to translate.
5. Press submit again to reset and start a new message.

## Notes

- A space is added automatically between characters.
- Unknown Morse symbols are replaced with `?`.
- LCD display scrolls automatically if the translated message exceeds 16 characters.