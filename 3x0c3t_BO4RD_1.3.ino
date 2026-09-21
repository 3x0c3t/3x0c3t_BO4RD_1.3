#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <ESP8266WiFi.h>

#include "TFT_Config.h"
#include "ScreenSplash2.h"
#include "Clock.h"
#include "WiFiScanner.h"
#include "ScreenApplication.h"

TFT_eSPI tft = TFT_eSPI();

void setup() {

  Serial.begin(115200);

  delay(100);

  Serial.println();
  Serial.println("================================");
  Serial.println("3x0c3t_BO4RD_1.3");
  Serial.println("================================");


  // ========================================
  // TFT
  // ========================================

  tft.init();

  tft.setRotation(
    TFT_ROTATION
  );

  tft.fillScreen(
    TFT_BLACK
  );

  // === TFT - END


  // ========================================
  // WIFI + NTP
  // ========================================

  initClock();

  // === WIFI + NTP - END


  // ========================================
  // SPLASH
  // ========================================

  drawScreenSplash2(
    tft
  );

  delay(
    SPLASH_DURATION
  );

  // === SPLASH - END


  // ========================================
  // WIFI SCANNER
  // ========================================

  initWiFiScanner();

  // === WIFI SCANNER - END


  // ========================================
  // APPLICATION
  // ========================================

  drawApplication(
    tft
  );

  // === APPLICATION - END
}


void loop() {

  // ========================================
  // CLOCK
  // ========================================

  updateClock(
    tft
  );

  // === CLOCK - END


  // ========================================
  // WIFI SCANNER
  // ========================================

  updateWiFiScanner();

  // === WIFI SCANNER - END


  // ========================================
  // WIFI DISPLAY REFRESH
  // ========================================

  if (
    wifiListNeedsRedraw
  ) {

    wifiListNeedsRedraw =
      false;

    drawWiFiList(
      tft
    );
  }

  // === WIFI DISPLAY REFRESH - END


  delay(100);
}
