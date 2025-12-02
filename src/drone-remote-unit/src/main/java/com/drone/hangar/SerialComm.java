package com.drone.hangar;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
// import com.fazecast.jSerialComm.*; // Assuming jSerialComm usage

public class SerialComm {
    private DroneRemoteUnit gui;
    // private SerialPort serialPort;
    private OutputStream output;

    public SerialComm(DroneRemoteUnit gui) {
        this.gui = gui;
    }

    public void connect(String portName) {
        // Mock connection for now since library is not present
        System.out.println("Connecting to " + portName);

        // Actual implementation would be:
        /*
         * serialPort = SerialPort.getCommPort(portName);
         * serialPort.setBaudRate(9600);
         * if (serialPort.openPort()) {
         * output = serialPort.getOutputStream();
         * // Start listener thread
         * new Thread(() -> listen()).start();
         * }
         */

        // Mock listener
        new Thread(() -> {
            try {
                Thread.sleep(1000);
                gui.updateState("DRONE INSIDE");
            } catch (Exception e) {
            }
        }).start();
    }

    public void send(String msg) {
        /*
         * try {
         * if (output != null) {
         * output.write((msg + "\n").getBytes());
         * output.flush();
         * }
         * } catch (Exception e) {
         * e.printStackTrace();
         * }
         */
        System.out.println("Sending to Serial: " + msg);
    }

    private void listen() {
        /*
         * try {
         * BufferedReader reader = new BufferedReader(new
         * InputStreamReader(serialPort.getInputStream()));
         * String line;
         * while ((line = reader.readLine()) != null) {
         * gui.updateState(line);
         * }
         * } catch (Exception e) {
         * e.printStackTrace();
         * }
         */
    }
}
