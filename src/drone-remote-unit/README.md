# Drone Remote Unit (DRU)

## Description
This is the PC-based subsystem for the Smart Drone Hangar project. It communicates with the Arduino subsystem via serial port.

## Requirements
- Java Development Kit (JDK) 8 or higher.
- `jSerialComm` library (or similar) for serial communication.

## Setup
1. Open the project in your favorite IDE (IntelliJ, Eclipse, VS Code).
2. Add `jSerialComm` to your project dependencies.
3. Configure the serial port in `DroneRemoteUnit.java` (default is "COM3").

## Running
Run the `com.drone.hangar.Main` class.

## Features
- **Take Off**: Sends "TO" command to the hangar.
- **Land**: Sends "LD" command to the hangar.
- **Status**: Displays the current state of the drone and the hangar.
