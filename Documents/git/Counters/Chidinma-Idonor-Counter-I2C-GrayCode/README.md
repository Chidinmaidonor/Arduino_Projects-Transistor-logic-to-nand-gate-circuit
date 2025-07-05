# Counters and I2C Lab

This project demonstrates the use of a 4-bit counter displayed on a 7-segment display using an I2C IO Expander (PCF8574AN). It includes conversion of binary count to Gray code.

## Contents

- `counter.c`: Main logic for counter and Gray code conversion
- `i2c_display.c/h`: I2C interface code for driving 7-segment display
- `images/`: Placeholder for wiring diagram

## Setup

1. Wire your breadboard as described in the PDF
2. Flash the microcontroller with the `counter.c` logic
3. Connect the IO expander via I2C as shown

## Procedure
Hardware Setup
1. Place Components

- Insert the 7-segment display and PCF8574AN IO Expander on the breadboard.

- Connect the resistor array (1kΩ) in series with the display segments to limit current.

2. Wiring

- Connect the PCF8574AN to your microcontroller using I²C (typically SDA and SCL pins).

- Wire the 7-segment display according to the pinout (see lab handout diagrams).

- Ensure the IO expander outputs connect to the display through the resistor pack.

3. Upload Code

- Compile and flash counter.c along with i2c_display.c/h to your microcontroller.

- Use switch or button inputs (if applicable) to start the counter.

## Software Testing

1. Basic Binary Count Test

- Set switch A OFF.

- Verify the 7-segment display increments in hexadecimal (0–F).

- Use a known binary-to-7seg lookup to confirm correct output.

2. Gray Code Test

- Enable Gray code logic by calling binary_to_gray() instead of raw binary.

- Confirm only one bit changes between successive output states.

- Cross-check with the Gray code table provided in the lab.

3. I²C Communication Check

- Probe SDA/SCL lines with a logic analyzer or oscilloscope.

- Ensure correct addressing and data is being sent to PCF8574AN.

4. Edge Cases

- Confirm correct behavior at wraparound (from 0xF to 0x0).

- Test system power-up and reset conditions.



