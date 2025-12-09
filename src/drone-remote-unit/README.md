# Drone Remote Unit (DRU)

## Description
The **Drone Remote Unit (DRU)** is a Java-based desktop application (Swing) that serves as the dashboard for the Smart Drone Hangar. It communicates with the Arduino-based Hangar subsystem via Serial Port (UART).

This application allows the user to:
- Monitor the status of the Drone and the Hangar.
- View real-time telemetry (Distance, Temperature).
- Send commands to the Hangar (Take Off, Land).
- Receive alerts (Alarm state).

## Requirements
- **Java Development Kit (JDK)**: Version 8 or higher.
- **Maven/Gradle** (optional, for dependency management) or manual library management.
- **Library**: `jSerialComm` (version 2.x or later) is used for serial communication.

## Project Structure
The source code is located in `src/main/java`.
- `com.drone.hangar.DroneRemoteUnit`: Main GUI class (JFrame). Handles UI updates and event listeners.
- `com.drone.hangar.SerialComm`: Handles Serial port connection and data transmission/reception.
- `com.drone.hangar.Main`: Entry point of the application.

## Setup & Configuration

1. **Import the Project**: Open the `drone-remote-unit` folder in your IDE (IntelliJ IDEA, Eclipse, VS Code).
2. **Dependencies**: Ensure `com.fazecast.jSerialComm` is added to your project's classpath. Use Maven/Gradle or download the JAR manually.
3. **Serial Port Configuration**: 
   - Open `src/main/java/com/drone/hangar/DroneRemoteUnit.java`.
   - Locate the line `serialComm.connect("COM5");`.
   - **Update "COM5"** to match the serial port where your Arduino is connected (e.g., "COM3", "/dev/ttyACM0").

## Running the Application
Run the `com.drone.hangar.Main` class.
The GUI should appear, attempting to connect to the specified Serial Port.

## Serial Protocol
The DRU and the Smart Hangar communicate using a simple ASCII-based protocol over UART (9600 baud).

### Commands Sent (PC -> Arduino)
| Command | Description |
| :--- | :--- |
| `TO` | **Take Off**: Requests the Hangar to open the roof and release the drone. |
| `LD` | **Land**: Requests the Hangar to accept a landing drone. |

### Messages Received (Arduino -> PC)
| Message | Description |
| :--- | :--- |
| `TAKE OFF` | Hangar is executing the take-off sequence. |
| `DRONE OUT` | The drone has successfully left the hangar. |
| `LANDING` | The drone is landing. |
| `DRONE INSIDE` | The drone is safely inside the hangar (Rest state). |
| `ALARM` | Hangar temperature is critical; system is in ALARM state. |
| `REST` | System has returned to normal operation from Alarm. |
| `TEMP:<val>` | Real-time temperature update (e.g., `TEMP:24.5`). |
| `DISTANCE:<val>` | Real-time distance sensor reading (e.g., `DISTANCE:150`). |
