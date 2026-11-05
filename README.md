<p align="center"><sub>BCA188 · LABORATORY ACTIVITY 08</sub></p>
<h1 align="center">Wired Communication</h1>
<p align="center">UART / I²C / SPI</p>
<p align="center"><strong>ESP32 · Arduino IDE · Laboratory Documentation</strong></p>

## Objective

Verify UART, I²C, and SPI wired communication using an ESP32 board and Arduino IDE.

## Pin Assignments

| Signal | GPIO used |
|---|---:|
| UART TX | 17 |
| UART RX | 18 |
| I²C SDA | 21 |
| I²C SCL | 20 |
| SPI SCK | 12 |
| SPI MOSI | 11 |
| SPI MISO | 13 |
| SPI CS | 10 |

## Wiring Diagrams

The supplied photos show the UART and SPI loopback jumpers and an OLED connected for the I²C scan.

### UART Loopback

<img width="1024" height="768" alt="UART Loopback Circuit Diagram" src="https://github.com/user-attachments/assets/64eadc40-5701-4b34-9415-b7aecd2fc1fd" />

Connect GPIO17 (TX) to GPIO18 (RX) with a jumper.

<a id="i2c-wiring"></a>

### I²C scanner with OLED

<img width="1024" height="768" alt="I2c Scanner Circuit Diagram" src="https://github.com/user-attachments/assets/7a862e29-2d1d-4534-89a0-c2e4d5bc8111" />

Connect the OLED SDA to GPIO21, SCL to GPIO20, VCC to 3V3, and GND to GND. Check the module pin labels before powering it.

<a id="spi-wiring"></a>

### SPI Loopback

<img width="1024" height="768" alt="SPI Loopback Circuit Diagram" src="https://github.com/user-attachments/assets/2ff0e04e-ba7f-4462-90eb-c3adbc019825" />

Connect GPIO11 (MOSI) to GPIO13 (MISO) with a jumper. The sketch also uses GPIO12 for SCK and GPIO10 for CS.


## Test Results

| Test | Expected | Observed |
|---|---|---|
| UART with jumper | `PING` is received/echoed about once per second. | PING received successfully |
| UART without jumper | No loopback `PING` is received. | No PING received |
| I²C with module | Scanner reports the module's responding address (often `0x3C` for an OLED). | Device detected at 0x3C |
| I²C without module | `No I2C devices found`. | No I2C device found |
| SPI with jumper | Received byte is `0xA5`. | 0xA5 received successfully |
| SPI without jumper | Received byte differs from `0xA5` or is unstable. | 0xFF and 0x00 received |
| Sketch USB serial at 9600, monitor at 115200 | Output is unreadable or garbled due to baud mismatch. | Unreadable characters appeared |
| Sketch USB serial at 9600, monitor at 9600 | Output is readable. | Repeated PING messages appeared |

## Serial Monitor Evidence

<a id="uart-wiring"></a>

### UART Loopback (with Jumper Wires)

<img width="1917" height="1017" alt="Screenshot 2026-11-05 165623" src="https://github.com/user-attachments/assets/f494ad40-75ec-45fa-9c3e-dd4a40613212" />

With the UART jumper connected, `PING` was received successfully about once per second.

### UART Loopback (without Jumper Wires)

<img width="1917" height="1020" alt="Screenshot 2026-11-05 170123" src="https://github.com/user-attachments/assets/2c4cbfcc-d167-4ead-90da-ab58f04b1382" />

With the UART jumper removed, no `PING` was received.

### I²C Scanner (with Jumper Wires)

<img width="1917" height="1017" alt="Screenshot 2026-11-05 171600" src="https://github.com/user-attachments/assets/9d31270c-3638-4556-bb18-8851bd166b3f" />

With the I²C module connected, the scanner detected a device at `0x3C`.

### I²C Scanner (without Jumper Wires)

<img width="1917" height="1020" alt="Screenshot 2026-11-05 171652" src="https://github.com/user-attachments/assets/b8f81af5-6208-4e5f-8340-af90235aad53" />

With the I²C module disconnected, no I²C device was found.

<a id="spi-wiring"></a>

### SPI Loopback (with Jumper Wires)

<img width="1917" height="1017" alt="Screenshot 2026-11-05 173317" src="https://github.com/user-attachments/assets/c4ce7aa1-33d6-48f0-8760-b67efcaf5384" />

With the SPI jumper connected, `0xA5` was received successfully.

### SPI Loopback (without Jumper Wires)

<img width="1917" height="1018" alt="Screenshot 2026-11-05 173421" src="https://github.com/user-attachments/assets/f95dbb96-66fd-46a0-ae7b-c3f290481875" />

With the SPI jumper removed, the received values were `0xFF` and `0x00`.

### Sketch at 9600, monitor at 115200 (UART Loopback)

<img width="1917" height="962" alt="Screenshot 2026-11-05 174204" src="https://github.com/user-attachments/assets/9457a8d8-3c2c-45ff-84d4-6e6d3901c674" />

With the sketch USB serial set to 9600 baud and the monitor at 115200 baud, unreadable characters appeared.

### Sketch at 9600, monitor at 9600 (UART Loopback)

<img width="1917" height="1017" alt="Screenshot 2026-11-05 165623" src="https://github.com/user-attachments/assets/9f86615c-c4b9-4865-b062-d7b0056b1f91" />

With both the sketch USB serial and monitor set to 9600 baud, repeated `PING` messages appeared.

## Questions

1. **Why does UART need both sides to use the same baud rate, while SPI uses a clock line?**  
   UART has no separate clock, so transmitter and receiver must agree on the bit timing (baud rate) to sample each bit correctly. SPI's clock line lets the controller provide timing for each transfer.

2. **Why can two devices with the same address not share one I²C bus?**  
   The controller selects an I²C device by its address, so duplicate addresses make both devices respond to the same request and their signals can collide. They need different addresses, an I²C multiplexer, or separate buses.

3. **Why is CS set HIGH between SPI transfers?**  
   CS is active LOW, so setting it HIGH deselects the device between transfers. This marks the end of one transaction and helps prevent a device from treating unrelated clock activity as part of its transfer.







