# AUTOCAN_Smart-EV-Health-Monitoring-Battery-Management-System-Using-CAN-Communication

##SYSTEM ARCHITECTURE:


<img width="428" height="429" alt="image" src="https://github.com/user-attachments/assets/207ae018-bb4e-4e58-99ed-296f89141ee5" />


## 3. Node 1 – Voltage and Current Monitoring Node

### 3.1 Hardware Components

- **Microcontroller:** LPC2129 Development Board (ARM7)
- **Voltage Sensor:** Voltage Sensor Module
- **Current Sensor:** ACS712 Current Sensor Module
- **External ADC:** MCP3204 (12-bit SPI ADC)
- **Communication:** CAN Protocol

### 3.2 Working Principle

This node is responsible for monitoring the voltage and current parameters of the electrical system.

Two different ADCs are used to acquire the sensor readings:

**1. Voltage Measurement**

- The voltage sensor module provides an analog output proportional to the measured voltage.
- This output is connected to the LPC2129's built-in 10-bit ADC.
- The microcontroller converts the ADC reading into a corresponding voltage value using the voltage conversion formula.

**2. Current Measurement**

- The ACS712 current sensor measures the current flowing through the electrical load.
- To obtain higher measurement resolution, an external MCP3204 12-bit ADC is used instead of the LPC2129's internal ADC.
- The ACS712 analog output is connected to Channel 3 of the MCP3204.
- The MCP3204 communicates with the LPC2129 through the SPI interface.
- The acquired ADC value is converted into the corresponding current value.

### 3.3 ADC Configuration

| Parameter | Voltage Measurement | Current Measurement |
|---|---|---|
| Sensor | Voltage Sensor Module | ACS712 |
| ADC | LPC2129 Internal ADC | MCP3204 |
| Resolution | 10-bit | 12-bit |
| Interface | Internal ADC | SPI |
| Input Channel | LPC2129 ADC input | MCP3204 Channel 3 |

### 3.4 CAN Data Transmission

After acquiring and converting both measurements, the LPC2129 transmits the voltage and current values through the CAN network.

Since both measurements are represented as 32-bit floating-point values (4 bytes each), they are assigned to the two CAN data registers.

| CAN Parameter | Configuration |
|---|---|
| CAN Controller | CAN2 |
| CAN Identifier | 0x101 |
| Frame Type | Data Frame |
| DLC | 8 Bytes |
| Data Register 1 | TDA – Voltage (4 Bytes) |
| Data Register 2 | TDB – Current (4 Bytes) |
| Transmission Interval | 1 Second |

**CAN Data Frame Structure:**

| TDA (4 Bytes) | TDB (4 Bytes) |
|---|---|
| Voltage Value (Float) | Current Value (Float) |

This allows both voltage and current measurements to be transmitted within a single CAN data frame.

### 3.5 Software Implementation

The firmware is divided into modular source files:

| Source File | Functionality |
|---|---|
| `MAIN.c` | Main application, sensor data acquisition and CAN transmission |
| `adc.c` | Internal ADC conversion and MCP3204 ADC interfacing |
| `spi.c` | SPI initialization and data communication with MCP3204 |
| `cantx_driver.c` | CAN initialization and transmission |
| `delay_ms.c` | Timer-based delay generation |
| `project_header.h` | Header files, data types and function declarations |

### 3.6 Node Function

Node 1 continuously acquires voltage and current measurements using the respective ADCs, converts them into floating-point values and transmits both parameters through the CAN communication network.

The transmitted information can be received by the other nodes for further processing and EV health monitoring.


