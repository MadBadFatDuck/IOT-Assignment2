package com.drone.hangar;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;

public class DroneRemoteUnit extends JFrame {
    private SerialComm serialComm;
    private JLabel droneStateLabel;
    private JLabel hangarStateLabel;
    private JLabel distanceLabel;
    private JTextArea logArea;

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
        JPanel statusPanel = new JPanel(new GridLayout(3, 2));
        statusPanel.add(new JLabel("Drone State:"));
        droneStateLabel = new JLabel("Unknown");
        statusPanel.add(new JLabel("Hangar State:"));
        hangarStateLabel = new JLabel("Normal");
        statusPanel.add(new JLabel("Distance:"));
        distanceLabel = new JLabel("-");

        add(statusPanel, BorderLayout.CENTER);

        // Log Area
        logArea = new JTextArea();
        logArea.setEditable(false);
        add(new JScrollPane(logArea), BorderLayout.SOUTH);

        // Initialize Serial
        serialComm = new SerialComm(this);
        serialComm.connect("COM5"); // Default port, should be configurable
    }

    private void sendCommand(String cmd) {
        if (serialComm != null) {
            serialComm.send(cmd);
            log("Sent: " + cmd);
        }
    }

    public void updateState(String msg) {
        SwingUtilities.invokeLater(() -> {
            log("Received: " + msg);
            if (msg.contains("ALARM")) {
                hangarStateLabel.setText("ALARM");
                hangarStateLabel.setForeground(Color.RED);
            } else if (msg.contains("REST")) {
                hangarStateLabel.setText("Normal");
                hangarStateLabel.setForeground(Color.BLACK);
            } else if (msg.contains("TAKE OFF")) {
                droneStateLabel.setText("Taking Off");
            } else if (msg.contains("LANDING")) {
                droneStateLabel.setText("Landing");
            } else if (msg.contains("DRONE OUT")) {
                droneStateLabel.setText("Operating");
            } else if (msg.contains("DRONE INSIDE")) {
                droneStateLabel.setText("Rest");
            }
        });
    }

    private void log(String msg) {
        logArea.append(msg + "\n");
    }
}
