# AUTOCAN_Smart-EV-Health-Monitoring-Battery-Management-System-Using-CAN-Communication

## Table of Contents

1. [SYSTEM ARCHITECTURE](#1-SYSTEM-ARCHITECTURE)
2. [Project Overview](#2-Project-Overview)
3. [Node 1 – Voltage and Current Monitoring](#3-node-1--voltage-and-current-monitoring-node)
   - [Hardware Components](#31-hardware-components)
   - [Working Principle](#32-working-principle)
   - [ADC Configuration](#33-adc-configuration)
   - [CAN Data Transmission](#34-can-data-transmission)
   - [Software Implementation](#35-software-implementation)
   - [Node Function](#36-node-function)
4. [Node 2 – Temperature Monitoring and CAN Transmission](#4-node-2--temperature-monitoring-and-can-transmitter)
   - [Hardware Components](#41-hardware-components)
   - [Working Principle](#42-working-principle)
   - [ADC Configuration](#43-adc-configuration)
   - [Temperature-Based Fan Control](#44-temperature-based-fan-control)
   - [CAN Communication](#45-can-communication)
   - [Software Implementation](#46-software-implementation)
   - [Node Function](#47-node-function)
5. [Node 3 – CAN Reception, Data Processing and LCD Display](#5-node-3--can-receiver-data-processing-and-lcd-display)
   - [Hardware Components](#51-hardware-components)
   - [Working Principle](#52-working-principle)
   - [CAN Data Reception](#53-can-data-reception)
   - [Power Calculation](#54-power-calculation)
   - [Fan Status Monitoring](#55-fan-status-monitoring)
   - [LCD Display](#56-lcd-display--204)
   - [Software Implementation](#57-software-implementation)
   - [Node Function](#58-node-function)

## 1. SYSTEM ARCHITECTURE:


<img width="428" height="429" alt="image" src="https://github.com/user-attachments/assets/207ae018-bb4e-4e58-99ed-296f89141ee5" />


## 2. Project Overview

**AUTOCAN SMART** is a CAN-based EV health monitoring and battery management system designed to monitor important electrical and thermal parameters of an electric vehicle.

The system uses three LPC2129-based nodes communicating through the Controller Area Network (CAN) protocol:

- **Node 1 – Voltage and Current Monitoring:** Acquires voltage and current measurements using ADC interfaces and transmits the data over CAN.
- **Node 2 – Temperature Monitoring:** Measures temperature using an LM35 sensor, controls the cooling fan based on a predefined threshold, and transmits temperature data over CAN.
- **Node 3 – Central Monitoring Unit:** Receives data from both nodes, calculates electrical power, monitors fan status, and displays the system parameters on a 20×4 LCD.

The project demonstrates distributed embedded system design, sensor interfacing, ADC-based data acquisition, CAN communication, and real-time monitoring using ARM7 microcontrollers.


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

## 4. Node 2 – Temperature Monitoring and CAN Transmitter

### 4.1 Hardware Components

- **Microcontroller:** LPC2129 Development Board (ARM7)
- **Temperature Sensor:** LM35
- **ADC:** Built-in 10-bit ADC of LPC2129
- **Cooling System:** DC Fan Motor
- **Communication:** CAN Protocol

### 4.2 Working Principle

This node monitors the temperature of the system using an LM35 temperature sensor and activates the cooling mechanism when the temperature exceeds a predefined threshold.

The operation is as follows:

1. The LM35 generates an analog voltage proportional to the measured temperature.
2. The analog output is connected to the LPC2129's internal ADC.
3. The 10-bit ADC converts the analog voltage into a digital value.
4. The ADC reading is converted into a temperature value in degrees Celsius.
5. The measured temperature is compared against a predefined threshold of 30°C.
6. When the temperature exceeds 30°C, the GPIO output connected to the cooling control circuit is activated.
7. The temperature information is transmitted to the other nodes through the CAN network.

### 4.3 ADC Configuration

The LPC2129's built-in 10-bit ADC is used for temperature measurement.

| Parameter | Configuration |
|---|---|
| ADC Resolution | 10 bits |
| ADC Output Range | 0–1023 |
| Reference Voltage | 3.3 V |
| Temperature Sensor | LM35 |
| Measurement Channel | ADC Channel 2 |

The ADC conversion is implemented in `adc.c`.

### 4.4 Temperature-Based Fan Control

The measured temperature is compared against a threshold of 30°C.

| Temperature Condition | GPIO P0.8 | GPIO P0.9 |
|---|---|---|
| Temperature > 30°C | LOW | HIGH |
| Temperature ≤ 30°C | HIGH | HIGH |

When the temperature exceeds the threshold, the output at P0.8 is driven LOW, controlling the cooling mechanism through the connected driver circuit.

### 4.5 CAN Communication

After measuring the temperature, the LPC2129 transmits the temperature information through its second CAN controller (CAN2).

| CAN Parameter | Configuration |
|---|---|
| CAN Controller | CAN2 |
| CAN Identifier | 0x102 |
| Frame Type | Data Frame |
| DLC | 8 Bytes |
| TDA | Temperature Value |
| TDB | 0 |
| Transmission | Periodic |

The temperature value is assigned to the CAN data register TDA, while TDB is set to zero.

**CAN Data Frame Structure:**

| TDA (4 Bytes) | TDB (4 Bytes) |
|---|---|
| Temperature Value | 0 |

### 4.6 Software Implementation

| Source File | Functionality |
|---|---|
| `MAIN.c` | Main application, temperature monitoring and fan control |
| `adc.c` | Internal ADC configuration and temperature conversion |
| `cantx_driver.c` | CAN initialization and data transmission |
| `delay_ms.c` | Timer-based delay generation |
| `project_header.h` | Header files, data types and function declarations |

### 4.7 Node Function

Node 2 continuously monitors the system temperature, controls the cooling mechanism based on the predefined temperature threshold and transmits the measured temperature through the CAN network.

This enables the other nodes to receive temperature information and incorporate it into the overall EV health monitoring system.

## 5. Node 3 – CAN Receiver, Data Processing and LCD Display

### 5.1 Hardware Components

- **Microcontroller:** LPC2129 Development Board (ARM7)
- **Display:** 20×4 LCD Display
- **Communication:** CAN Protocol
- **Interface:** GPIO-based LCD interfacing

### 5.2 Working Principle

Node 3 acts as the central monitoring unit of the system. It receives sensor information from the other two nodes through CAN communication, processes the received data and displays the system parameters on a 20×4 LCD.

The operation is as follows:

1. Initializes the CAN receiver and LCD interface.
2. Continuously monitors the CAN bus for incoming messages.
3. Identifies the transmitting node using the CAN message identifier.
4. Extracts voltage, current and temperature information from the received CAN data frames.
5. Calculates electrical power using the received voltage and current values.
6. Determines the cooling fan status based on the received temperature.
7. Displays all monitored parameters on the 20×4 LCD.

### 5.3 CAN Data Reception

The LPC2129's second CAN controller (CAN2) is configured to receive messages from both transmitting nodes.

The receiver identifies incoming messages using their CAN identifiers.

| Transmitting Node | CAN ID | Received Information |
|---|---|---|
| Node 1 | 0x101 | Voltage and Current |
| Node 2 | 0x102 | Temperature |

The received data is extracted from the CAN reception registers (C2RDA and C2RDB) and stored in the corresponding variables for further processing.

### 5.4 Power Calculation

After receiving the voltage and current measurements from Node 1, the microcontroller calculates electrical power.

**Power = Voltage × Current**

The calculated power value is displayed on the LCD.

### 5.5 Fan Status Monitoring

The receiver also monitors the temperature information received from Node 2.

Based on the received temperature, the fan status is determined using the following condition:

| Temperature Condition | Fan Status |
|---|---|
| Temperature > 30°C | ON |
| Temperature ≤ 30°C | OFF |

This allows the user to monitor the cooling system status directly from the central display unit.

### 5.6 LCD Display – 20×4

A 20×4 LCD is interfaced with the LPC2129 using GPIO pins.

The display presents four important parameters simultaneously:

| LCD Row | Display Information |
|---|---|
| Row 1 | Temperature and Fan Status |
| Row 2 | Voltage |
| Row 3 | Current |
| Row 4 | Calculated Power |

**Example LCD Output:**

```text
TEMP:35C  FAN:ON

VOLTAGE:12.0V

CURRENT:1.5mA

POWER:18.0W
```


### 5.7 Software Implementation

The firmware is organized into modular source files.

| Source File | Functionality |
|---|---|
| `main_rx.c` | Main application, CAN data processing, power calculation and LCD updates |
| `canrx_driver.c` | CAN initialization and message reception |
| `lcd_header.h` | LCD initialization, command, data and display functions |
| `UART_header.h` | UART configuration and serial communication utility functions |
| `delay_ms.c` | Timer-based delay generation |
| `rx_project_header.h` | Header files, data types and function declarations |

### 5.8 Node Function

Node 3 serves as the central monitoring and display unit of AUTOCAN SMART.

It collects voltage, current and temperature information from the transmitting nodes, calculates electrical power, monitors the cooling fan status and presents the processed information through a 20×4 LCD.

This provides a centralized interface for observing the operating conditions of the EV monitoring system.


