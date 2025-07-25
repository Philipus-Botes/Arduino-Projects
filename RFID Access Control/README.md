# RFID Access Control System (Arduino)

This Arduino project uses an **RFID reader** to control access, log attempts, and provide visual/auditory feedback using an RGB LED and buzzer.

## Components Used

- Arduino Uno (or compatible)
- MFRC522 RFID Reader
- RFID Tags (key fobs/cards)
- RGB LED (common anode)
- Buzzer (passive or active)
- Jumper wires & breadboard
- Optional: Keypad, relay, SD module

## Pin Configuration

| Component        | Arduino Pin |
|------------------|-------------|
| MFRC522 SDA      | 10          |
| MFRC522 RST      | 9           |
| MFRC522 MOSI     | 11 (SPI)    |
| MFRC522 MISO     | 12 (SPI)    |
| MFRC522 SCK      | 13 (SPI)    |
| Buzzer           | 6           |
| RGB LED Red      | 3 (PWM)     |
| RGB LED Green    | 5 (PWM)     |
| RGB LED Blue     | 4 (PWM)     |

> This project assumes a **common anode** RGB LED. If you're using a **common cathode** LED, remove `255 -` from the `analogWrite()` lines in `setRGB()`.

## Features

- Logs each scanned RFID tag UID to the Serial Monitor
- Compares against a list of authorized UIDs
- Provides feedback via:
  - Blue = Ready
  - Green + single beep = Access Granted
  - Red + two beeps = Access Denied
- Easily expandable for:
  - Keypad (for 2FA)
  - Relay or servo (to control locks)
  - SD card (to store logs)

## Setup Instructions

1. Connect the hardware components as per the pin table.
2. Open the Arduino IDE and upload `rfid_access_control.ino` to your board.
3. Open the Serial Monitor at **9600 baud**.
4. Scan RFID tags to test access control.
5. Add your tag’s UID to the `authorizedUIDs[]` array in the sketch.

## Customization

- **Add authorized UIDs:** Replace the sample UIDs in the `authorizedUIDs[]` array with your own.
- **Use a relay module:** Control actual electronic locks or gates by connecting a relay to a digital pin.
- **Two-factor authentication:** Add a keypad to require both a tag and PIN code.
- **Logging to SD card:** Use an SD card module to store timestamped logs for auditing.

## Security Notice

This is a **basic prototype**. For real-world applications:
- Avoid relying solely on UIDs (they can be cloned).
- Use encrypted or dynamic token-based systems.
- Add physical tamper-proofing.
- Consider watchdogs and fallback authentication.