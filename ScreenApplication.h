#ifndef SCREEN_APPLICATION_H
#define SCREEN_APPLICATION_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <ESP8266WiFi.h>


// ========================================
// PROTOTYPES
// ========================================

void drawWiFiList(TFT_eSPI &tft);

// === PROTOTYPES - END



// ========================================
// APPLICATION
// ========================================

void drawApplication(
  TFT_eSPI &tft
) {

  const int16_t w =
    tft.width();


  tft.fillScreen(
    TFT_BLACK
  );


  // ========================================
  // HEADER
  // ========================================

  // Header remonté de 15 px
  // Hauteur : 19 px

  tft.fillRect(
    0,
    0,
    w,
    19,
    TFT_DARKGREY
  );


  tft.setTextDatum(
    TL_DATUM
  );

  tft.setTextColor(
    TFT_WHITE,
    TFT_DARKGREY
  );

  tft.setTextSize(1);


  tft.drawString(
    "APPLICATION",
    6,
    5
  );


  // ========================================
  // SEPARATEUR
  // ========================================

  tft.drawFastHLine(
    0,
    19,
    w,
    TFT_WHITE
  );


  // ========================================
  // WIFI TITLE
  // ========================================

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.setTextSize(2);


  tft.drawString(
    "WIFI",
    6,
    25
  );


  // ========================================
  // SCAN STATUS
  // ========================================

  tft.setTextDatum(
    TR_DATUM
  );

  tft.setTextSize(1);

  tft.drawString(
    "SCAN",
    w - 6,
    31
  );


  tft.setTextDatum(
    TL_DATUM
  );


  // ========================================
  // WIFI LIST
  // ========================================

  drawWiFiList(
    tft
  );
}

// === APPLICATION - END



// ========================================
// WIFI LIST
// ========================================

void drawWiFiList(
  TFT_eSPI &tft
) {

  const int16_t startY = 52;

  const int16_t rowHeight = 28;


  // ========================================
  // CLEAR LIST AREA
  // ========================================

  tft.fillRect(
    0,
    startY,
    tft.width(),
    tft.height() - startY,
    TFT_BLACK
  );


  // ========================================
  // SCAN IN PROGRESS
  // ========================================

  if (
    wifiScanRunning
  ) {

    tft.setTextColor(
      TFT_YELLOW,
      TFT_BLACK
    );

    tft.setTextSize(1);


    tft.drawString(
      "SCAN WIFI...",
      6,
      startY + 5
    );

    return;
  }


  // ========================================
  // NO NETWORK
  // ========================================

  if (
    wifiNetworkCount <= 0
  ) {

    tft.setTextColor(
      TFT_RED,
      TFT_BLACK
    );

    tft.setTextSize(1);


    tft.drawString(
      "AUCUN RESEAU",
      6,
      startY + 5
    );

    return;
  }


  // ========================================
  // NUMBER OF DISPLAYABLE NETWORKS
  // ========================================

  int maxRows =
    min(
      wifiNetworkCount,
      (tft.height() - startY - 2)
      / rowHeight
    );


  // ========================================
  // NETWORKS
  // ========================================

  for (
    int i = 0;
    i < maxRows;
    i++
  ) {

    const int y =
      startY +
      (i * rowHeight);


    // ======================================
    // SSID
    // ======================================

    String ssid =
      WiFi.SSID(i);


    // Réseau masqué
    if (
      ssid.length() == 0
    ) {

      ssid =
        "[HIDDEN]";
    }


    // Limitation largeur
    if (
      ssid.length() > 24
    ) {

      ssid =
        ssid.substring(
          0,
          24
        );
    }


    // ======================================
    // RSSI
    // ======================================

    int rssi =
      WiFi.RSSI(i);


    // ======================================
    // CHANNEL
    // ======================================

    int channel =
      WiFi.channel(i);


    // ======================================
    // NETWORK NUMBER
    // ======================================

    tft.setTextDatum(
      TL_DATUM
    );

    tft.setTextColor(
      TFT_WHITE,
      TFT_BLACK
    );

    tft.setTextSize(1);


    tft.drawString(
      String(i + 1),
      5,
      y + 2
    );


    // ======================================
    // SSID
    // ======================================

    tft.setTextColor(
      TFT_CYAN,
      TFT_BLACK
    );

    tft.setTextSize(1);


    tft.drawString(
      ssid,
      22,
      y + 2
    );


    // ======================================
    // RSSI + CHANNEL
    // ======================================

    tft.setTextColor(
      TFT_LIGHTGREY,
      TFT_BLACK
    );


    String info =
      String(rssi) +
      "dBm  CH" +
      String(channel);


    tft.drawString(
      info,
      22,
      y + 14
    );


    // ======================================
    // SEPARATOR
    // ======================================

    tft.drawFastHLine(
      5,
      y + rowHeight - 2,
      tft.width() - 10,
      TFT_DARKGREY
    );
  }


  tft.setTextDatum(
    TL_DATUM
  );
}

// === WIFI LIST - END

#endif
