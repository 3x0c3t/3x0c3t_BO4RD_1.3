#ifndef SCREEN_APPLICATION_H
#define SCREEN_APPLICATION_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <ESP8266WiFi.h>

extern int wifiNetworkCount;
extern bool wifiScanRunning;
extern bool wifiListNeedsRedraw;


// === PROTOTYPES ===

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

  const int16_t h =
    tft.height();


  tft.fillScreen(
    TFT_BLACK
  );


  // ========================================
  // HEADER
  // ========================================

  const int16_t HEADER_HEIGHT = 24;

  tft.fillRect(
    0,
    0,
    w,
    HEADER_HEIGHT,
    TFT_DARKGREY
  );


  tft.setTextDatum(
    TL_DATUM
  );

  tft.setTextColor(
    TFT_WHITE,
    TFT_DARKGREY
  );

  tft.setTextSize(
    1
  );


  tft.drawString(
    "APPLICATION",
    6,
    5
  );


  // ========================================
  // HEADER SEPARATOR
  // ========================================

  tft.drawFastHLine(
    0,
    HEADER_HEIGHT,
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

  tft.drawString(
    "WIFI",
    6,
    29
  );


  // ========================================
  // SCAN
  // ========================================

  tft.setTextDatum(
    TR_DATUM
  );

  tft.drawString(
    "SCAN",
    w - 6,
    29
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

  const int16_t w =
    tft.width();

  const int16_t h =
    tft.height();


  const int16_t startY =
    52;

  const int16_t rowHeight =
    28;


  // Efface uniquement la liste

  tft.fillRect(
    0,
    startY,
    w,
    h - startY,
    TFT_BLACK
  );


  // ========================================
  // SCAN IN PROGRESS
  // ========================================

  if (
    wifiScanRunning
  ) {

    tft.setTextDatum(
      TL_DATUM
    );

    tft.setTextColor(
      TFT_YELLOW,
      TFT_BLACK
    );

    tft.drawString(
      "SCAN WIFI...",
      6,
      startY
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
      TFT_LIGHTGREY,
      TFT_BLACK
    );

    tft.drawString(
      "AUCUN RESEAU",
      6,
      startY
    );

    return;
  }


  // ========================================
  // NETWORK LIST
  // ========================================

  tft.setTextDatum(
    TL_DATUM
  );


  for (
    int i = 0;
    i < wifiNetworkCount;
    i++
  ) {

    const int16_t y =
      startY + (i * rowHeight);


    if (
      y + rowHeight >
      h
    ) {

      break;
    }


    String ssid =
      WiFi.SSID(i);


    if (
      ssid.length() == 0
    ) {

      ssid =
        "[HIDDEN]";
    }


    // SSID

    tft.setTextColor(
      TFT_WHITE,
      TFT_BLACK
    );

    tft.drawString(
      ssid,
      6,
      y
    );


    // RSSI

    tft.setTextDatum(
      TR_DATUM
    );

    tft.setTextColor(
      TFT_GREEN,
      TFT_BLACK
    );

    String rssi =
      String(
        WiFi.RSSI(i)
      );

    rssi +=
      " dBm";

    tft.drawString(
      rssi,
      w - 6,
      y
    );


    // CHANNEL

    tft.setTextDatum(
      TL_DATUM
    );

    String channel =
      "CH ";

    channel +=
      String(
        WiFi.channel(i)
      );

    tft.setTextColor(
      TFT_CYAN,
      TFT_BLACK
    );

    tft.drawString(
      channel,
      6,
      y + 13
    );


    // SEPARATOR

    tft.drawFastHLine(
      0,
      y + rowHeight - 1,
      w,
      TFT_DARKGREY
    );
  }
}


// === WIFI LIST - END

#endif
