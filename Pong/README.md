# Arduino Pong (1-Player LCD Game)

This project is a simple, retro-inspired Pong game built using an **Arduino**, an **I2C 16x2 LCD display**, and **two physical buttons**. You control the left paddle while the right paddle is controlled by a basic AI. Scores are displayed on-screen, and your **high score is saved** to EEPROM between sessions.

> Ideal for beginners learning LCDs, input handling, and game logic on Arduino.

## Components Used

- Arduino Uno
- 16x2 I2C LCD (I2C address 0x27 or 0x3F)
- 2 x Push Buttons (Control up/down movement)
- Jumper Wires & Breadboard

## Controls

| Button | Action            | Arduino Pin |
|--------|-------------------|-------------|
| Up     | Move paddle up    | `D2`        |
| Down   | Move paddle down  | `D3`        |

> Buttons are wired between the digital pin and GND, using the Arduino's `INPUT_PULLUP` mode.

## Features

- 1-player Pong gameplay on a 16x2 LCD
- AI-controlled right paddle
- EEPROM stores high score after resets
- 2-button physical control
- Simple hardware and code

## Wiring Guide

### LCD Wiring (I2C)
| LCD Pin | Arduino Pin |
|---------|-------------|
| VCC     | 5V          |
| GND     | GND         |
| SDA     | A4          |
| SCL     | A5          |

### Buttons
| Button Function | Arduino Pin | Other End |
|-----------------|-------------|-----------|
| Up              | D2          | GND       |
| Down            | D3          | GND       |

> No need for external resistors — the code uses internal pull-up resistors (`INPUT_PULLUP`).

## Setup Instructions

1. Connect the LCD and buttons as per the wiring tables above.
2. Open `arduino_pong.ino` in the Arduino IDE.
3. Ensure the **LiquidCrystal_I2C** and **EEPROM** libraries are installed.
4. Upload the sketch to your Arduino.
5. Open Serial Monitor (optional) for debug logs (9600 baud).
6. Play the game! Try to beat your high score.

## Notes & Tips

- LCD address may vary: Try `0x27` or `0x3F` depending on your I2C module.
- This version supports only 2 vertical positions due to LCD size (16x2). Upgrade to a **20x4 LCD** or **OLED** to expand the game space.
- AI paddle uses simple tracking — you can improve it for a challenge!
- EEPROM saves high score at address `0`. Reset EEPROM manually if needed.

## Possible Upgrades

- Add OLED or TFT display for a higher resolution game
- Add sound feedback/music with a buzzer
- Save top 3 or 5 scores in EEPROM
- Add restart/pause/reset buttons
- 2-player version using 4 buttons


