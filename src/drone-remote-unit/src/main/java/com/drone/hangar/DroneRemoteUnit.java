package com.drone.hangar;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;

public class DroneRemoteUnit extends JFrame {
    private SerialComm serialComm;
    private JLabel droneStateLabel;
    private JLabel hangarStateLabel;
    private JLabel distanceLabel;
    private JLabel tempLabel;

    public DroneRemoteUnit() {
        setTitle("Drone Remote Unit");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Control Panel
        JPanel controlPanel = new JPanel();
        JButton takeOffBtn = new JButton("Take Off");
        JButton landBtn = new JButton("Land");

        takeOffBtn.addActionListener((ActionEvent e) -> sendCommand("TO"));
        landBtn.addActionListener((ActionEvent e) -> sendCommand("LD"));

        controlPanel.add(takeOffBtn);
        controlPanel.add(landBtn);
        add(controlPanel, BorderLayout.NORTH);

        // Status Panel
        JPanel statusPanel = new JPanel(new GridLayout(4, 2));
        statusPanel.add(new JLabel("Drone State:"));
        droneStateLabel = new JLabel("Unknown");
        statusPanel.add(droneStateLabel);
        statusPanel.add(new JLabel("Hangar State:"));
        hangarStateLabel = new JLabel("Normal");
        statusPanel.add(hangarStateLabel);
        statusPanel.add(new JLabel("Distance:"));
        distanceLabel = new JLabel("-");
        statusPanel.add(distanceLabel);
        statusPanel.add(new JLabel("Temperature:"));
        tempLabel = new JLabel("-");
        statusPanel.add(tempLabel);

        add(statusPanel, BorderLayout.CENTER);

        // Initialize Serial
        serialComm = new SerialComm(this);
        serialComm.connect("COM5"); // Default port, should be configurable
    }

    private void sendCommand(String cmd) {
        if (serialComm != null) {
            serialComm.send(cmd);
        }
    }

    public void updateState(String msg) {
        // Pulizia e standardizzazione del messaggio in ingresso
        // (Rimuove spazi bianchi e converte in maiuscolo)
        final String cleanedMsg = msg.trim().toUpperCase();

        // Log di DEBUG (Lascia questa parte per la console)
        System.out.println(cleanedMsg);

        // L'aggiornamento dell'interfaccia utente (GUI) deve essere eseguito sul thread
        // di Event Dispatch (EDT)
        SwingUtilities.invokeLater(() -> {

            // 1. Aggiornamenti dello stato Hangar (Hangar State)
            if (cleanedMsg.equals("ALARM")) {
                hangarStateLabel.setText("ALARM");
                hangarStateLabel.setForeground(Color.RED);
            } else if (cleanedMsg.equals("REST")) { // Stato inviato da Arduino per uscire dall'allarme
                hangarStateLabel.setText("Normal");
                hangarStateLabel.setForeground(Color.BLACK);
            }

            // 2. Aggiornamenti dello stato Drone (Drone State)
            else if (cleanedMsg.equals("TAKE OFF")) {
                droneStateLabel.setText("Taking Off");
            } else if (cleanedMsg.equals("LANDING")) {
                droneStateLabel.setText("Landing");
            } else if (cleanedMsg.equals("DRONE OUT")) {
                droneStateLabel.setText("Operating");
            } else if (cleanedMsg.equals("DRONE INSIDE")) {
                droneStateLabel.setText("Rest");
                // Assicurati che anche lo stato Hangar sia Normal, specialmente all'avvio
                hangarStateLabel.setText("Normal");
                hangarStateLabel.setForeground(Color.BLACK);
            }

            // 3. Aggiornamenti della temperatura
            else if (cleanedMsg.startsWith("TEMP:")) {
                String val = cleanedMsg.substring(5);
                tempLabel.setText(val + " C");
            }
            else if (cleanedMsg.startsWith("DISTANCE:")){
                String val = cleanedMsg.substring(9);
                distanceLabel.setText(val + " cm");
            }
        });
    }
}
