# Smart Drone Hangar - IoT Assignment 2

## Overview
The **Smart Drone Hangar** is an IoT system designed to automate the storage, maintenance, and deployment of a drone. The system consists of two main components communicating via a Serial connection:
1. **Drone Hangar (Arduino)**: The physical unit controlling sensors, actuators, and valid states.
2. **Drone Remote Unit (PC/Java)**: A dashboard for remote monitoring and control.

## System Architecture

### 1. Drone Hangar (`src/drone-hangar`)
- **Platform**: Arduino / PlatformIO
- **Components**:
  - **Sensors**: Sonar (Distance), PIR (Presence), Temperature Sensor.
  - **Actuators**: Servo Motor (Door), LEDs (Status indicators), LCD Display.
- **Functionality**:
  - Manages the "Smart Hangar" state machine (Rest, Take Off, Out, Landing, Alarm).
  - Monitors temperature for overheating (Alarm state).
  - Reports status to the Remote Unit.

### 2. Drone Remote Unit (`src/drone-remote-unit`)
- **Platform**: Java (Swing)
- **Functionality**:
  - Provides a Graphical User Interface (GUI) for the operator.
  - Sends commands (`Take Off`, `Land`).
  - Displays real-time telemetry (Temperature, Distance) and system state.

## Getting Started

### Prerequisites
- **Hardware**: Arduino board (Uno/Mega) with required sensors and actuators.
- **Software**: 
  - Visual Studio Code with PlatformIO (for Arduino firmware).
  - Java Development Kit (JDK 8+) and an IDE (for the Remote Unit).

### Installation & Run

1. **Firmware (Arduino)**:
   - Navigate to `src/drone-hangar`.
   - Open the project in PlatformIO.
   - Upload the code to your Arduino.

2. **Remote Unit (PC)**:
   - Navigate to `src/drone-remote-unit`.
   - Compile and run the Java application.
   - **Note**: Ensure the correct Serial Port (e.g., `COM3`) is configured in the Java code before running.

## Serial Communication
The two units communicate via a custom ASCII protocol over UART (9600 baud). The Remote Unit acts as the conceptual "Dashboard," while the Hangar executes logic and reports sensor data.
See `src/drone-remote-unit/README.md` for protocol details.