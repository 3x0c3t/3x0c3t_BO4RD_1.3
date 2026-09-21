#ifndef WIFI_SCANNER_H
#define WIFI_SCANNER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

#define WIFI_SCAN_INTERVAL 10000

unsigned long lastWiFiScan = 0;

int wifiNetworkCount = 0;

bool wifiScanRunning = false;

bool wifiListNeedsRedraw = false;


// ========================================
// START WIFI SCAN
// ========================================

void startWiFiScan() {

  if (wifiScanRunning) {
    return;
  }

  Serial.println();
  Serial.println("Starting WiFi scan...");

  WiFi.scanDelete();

  wifiScanRunning = true;

  WiFi.scanNetworksAsync(

    [](int networksFound) {

      wifiNetworkCount =
        networksFound;

      wifiScanRunning =
        false;

      wifiListNeedsRedraw =
        true;


      Serial.println();

      Serial.print(
        "WiFi networks found: "
      );

      Serial.println(
        networksFound
      );


      for (
        int i = 0;
        i < networksFound;
        i++
      ) {

        Serial.print(
          i + 1
        );

        Serial.print(
          " | "
        );


        String ssid =
          WiFi.SSID(i);


        if (
          ssid.length() == 0
        ) {

          Serial.print(
            "[HIDDEN]"
          );

        } else {

          Serial.print(
            ssid
          );
        }


        Serial.print(
          " | RSSI "
        );

        Serial.print(
          WiFi.RSSI(i)
        );


        Serial.print(
          " | CH "
        );

        Serial.print(
          WiFi.channel(i)
        );


        Serial.print(
          " | "
        );

        Serial.println(
          WiFi.encryptionType(i)
        );
      }
    },

    // Inclure les réseaux masqués
    true
  );
}

// === START WIFI SCAN - END


// ========================================
// INITIALISATION
// ========================================

void initWiFiScanner() {

  Serial.println();

  Serial.println(
    "WiFi scanner initialization."
  );


  if (
    WiFi.status() == WL_CONNECTED
  ) {

    Serial.print(
      "Connected to: "
    );

    Serial.println(
      WiFi.SSID()
    );

  } else {

    Serial.println(
      "WiFi not connected."
    );
  }


  startWiFiScan();

  lastWiFiScan =
    millis();
}

// === INITIALISATION - END


// ========================================
// UPDATE WIFI SCANNER
// ========================================

void updateWiFiScanner() {

  // Nouveau résultat disponible
  if (
    wifiListNeedsRedraw
  ) {

    wifiListNeedsRedraw =
      false;
  }


  // Nouveau scan périodique
  if (
    !wifiScanRunning &&
    millis() - lastWiFiScan >=
    WIFI_SCAN_INTERVAL
  ) {

    lastWiFiScan =
      millis();

    startWiFiScan();
  }
}

// === UPDATE WIFI SCANNER - END

#endif
