package com.drone.hangar;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import com.fazecast.jSerialComm.SerialPort; // <--- RIGA AGGIUNTA (o decommentata)

public class SerialComm {
    private DroneRemoteUnit gui;
    private SerialPort serialPort; // <--- DECOMMENTATA
    private OutputStream output;

    public SerialComm(DroneRemoteUnit gui) {
        this.gui = gui;
    }

    public void connect(String portName) {
        System.out.println("Connecting to " + portName + " at 9600 baud...");

        // INIZIO IMPLEMENTAZIONE REALE 🚀
        serialPort = SerialPort.getCommPort(portName);
        serialPort.setBaudRate(9600);

        if (serialPort.openPort()) {
            System.out.println("Serial Port Opened Successfully.");
            output = serialPort.getOutputStream();
            // Avvia il thread per l'ascolto continuo dei messaggi dall'Arduino
            new Thread(() -> listen()).start();
            
            // Invia lo stato iniziale alla GUI (opzionale, basato sul mock precedente)
            new Thread(() -> {
                try {
                    Thread.sleep(100);
                    gui.updateState("DRONE INSIDE"); 
                } catch (Exception e) {
                }
            }).start();
            
        } else {
            System.err.println("Error: Unable to open serial port " + portName);
        }
        // FINE IMPLEMENTAZIONE REALE
    }

    public void send(String msg) {
        try {
            if (output != null) {
                // Scrive il messaggio e aggiunge '\n' per terminare la stringa,
                // come atteso dall'Arduino (Serial.readStringUntil('\n'))
                output.write((msg + "\n").getBytes());
                output.flush();
                System.out.println("Sent to Serial: " + msg); // Mantenuto per il log della console
            }
        } catch (Exception e) {
            System.err.println("Error sending data to serial port.");
            e.printStackTrace();
        }
    }

    private void listen() {
        try {
            // Legge i dati in arrivo dalla seriale
            BufferedReader reader = new BufferedReader(new
                    InputStreamReader(serialPort.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                // Inoltra il messaggio letto all'interfaccia grafica
                gui.updateState(line);
            }
        } catch (Exception e) {
            // E.g., la porta si è disconnessa
            System.err.println("Serial listener terminated.");
            e.printStackTrace();
        }
    }
}