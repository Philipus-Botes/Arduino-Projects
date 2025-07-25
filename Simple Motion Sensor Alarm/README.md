# Arduino Motion Sensor Alarm System

A simple Arduino-based alarm system using a **PIR motion sensor** and **buzzer**, with a **reset button** that stops the alarm and re-primes the system after a **20-second exit delay**.

## Components Used

Arduino Uno
- PIR Motion Sensor
- Buzzer
- Push Button (to reset the alarm)
- Jumper Wires & Breadboard

## How It Works

- When powered on, the system is **armed**.
- If **motion is detected**, the **buzzer sounds** and a message is printed to Serial Monitor.
- Press the **reset button** to:
  - Stop the alarm
  - Prime the system again after a **20-second exit delay**

## Wiring

### PIR Sensor

| PIR Pin | Arduino Pin |
|---------|-------------|
| VCC     | 5V          |
| GND     | GND         |
| OUT     | D2          |

### Buzzer

| Buzzer Pin | Arduino Pin |
|------------|-------------|
| + (VCC)    | D3          |
| - (GND)    | GND         |

### Reset Button

| Button Pin | Arduino Pin |
|------------|-------------|
| One leg    | D4          |
| Other leg  | GND         |

> No resistor needed for button if `INPUT_PULLUP` is used in code.

## Upload Instructions

1. Open `motion_alarm.ino` in the Arduino IDE.
2. Connect your components as per the wiring table.
3. Select the correct board and port from **Tools > Board / Port**.
4. Click **Upload**.
5. Open **Serial Monitor** at 9600 baud to view messages.

## Features

- Motion detection via PIR sensor
- Buzzer alert when motion is detected
- Reset button halts alarm and arms system after a 20s delay
- Serial output logs for monitoring
- Simple & reliable logic

## Possible Future Upgrades

- Add LED for visual feedback
- Add keypad or RFID for secure disarm
- Save system state using EEPROM
- Send alert via WiFi/LoRa module (IoT expansion)
- Add OLED screen for user interface