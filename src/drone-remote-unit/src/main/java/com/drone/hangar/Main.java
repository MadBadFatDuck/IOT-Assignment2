package com.drone.hangar;

import javax.swing.SwingUtilities;

public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            DroneRemoteUnit dru = new DroneRemoteUnit();
            dru.setVisible(true);
        });
    }
}
