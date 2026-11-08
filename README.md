# ESP32 Based Voting Machine

A simple educational Electronic Voting Machine (EVM) prototype built using an ESP32 development board, an I2C 16x2 LCD, push buttons, and indicator LEDs.

## Project overview

The prototype allows a voter to select one of three candidates using buttons. The ESP32 stores vote counts in RAM and displays confirmation and vote totals on the LCD.

> **Prototype status:** The Arduino sketch compiled, but the latest upload did not pass flash verification (MD5 mismatch). The I2C scanner uploaded and booted, but did not detect an I2C device. The LCD wiring/address and the flash-upload issue still require troubleshooting. This is an educational prototype, not a certified election system.

## Hardware

- ESP32 DevKit board (30-pin)
- 16x2 LCD with I2C interface
- 4 push buttons (3 candidate selections + results)
- 3 LEDs with 220–330 Ω current-limiting resistors
- Breadboard and jumper wires
- USB data cable

## Pin connections

| Component | ESP32 GPIO |
|---|---:|
| LCD SDA | 21 |
| LCD SCL | 22 |
| Candidate 1 button | 18 |
| Candidate 2 button | 19 |
| Candidate 3 button | 23 |
| Results button | 25 |
| Candidate 1 LED | 26 |
| Candidate 2 LED | 27 |
| Candidate 3 LED | 32 |

Buttons are configured with `INPUT_PULLUP`; connect the other button terminal to GND. Connect each LED through a resistor. Confirm your particular module’s pin labels before powering it.

## Firmware

Open `firmware/ESP32_EVM.ino` in Arduino IDE. Select the appropriate ESP32 board and port. The sketch uses the `LiquidCrystal_I2C` library and expects LCD address `0x27`.

## Behavior

- Startup: displays an EVM-ready prompt
- Candidate button: increments that candidate's vote count and briefly indicates the selection
- Results button: displays the vote totals
- Counts are volatile RAM values and reset when the ESP32 restarts

## Development notes

Latest test observations:
- I2C scanner booted and completed, but no address was printed.
- Main EVM sketch compiled successfully.
- Upload failed during flash verification with an MD5 mismatch after a flash-chip communication warning.

See `evidence/development-output.txt` for the recorded output.

## Limitations and future work

- Resolve I2C/LCD detection and verify the display.
- Investigate flash communication and upload verification.
- Test button debouncing and all vote/result states on hardware.
- Add persistent storage only after core operation is stable.
- A real election system would require security, auditability, accessibility, and independent certification beyond this prototype.

## License

Educational project. Add a license if you want to define reuse terms.
