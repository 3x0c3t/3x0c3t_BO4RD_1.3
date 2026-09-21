#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <time.h>

// ========================================
// WIFI / NTP
// ========================================

#define WIFI_SSID     "N0wifiHere"
#define WIFI_PASSWORD "@PassWeurd"

#define NTP_SERVER_1 "pool.ntp.org"
#define NTP_SERVER_2 "time.nist.gov"

// France métropolitaine
// CET = UTC+1
// CEST = UTC+2
#define FRANCE_TZ "CET-1CEST,M3.5.0,M10.5.0"

// === WIFI / NTP - END


// ========================================
// CLOCK STATE
// ========================================

unsigned long lastClockUpdate = 0;
bool clockReady = false;

// === CLOCK STATE - END


// ========================================
// INITIALISATION WIFI + NTP
// ========================================

void initClock() {

  Serial.println();
  Serial.println("================================");
  Serial.println("WIFI CONNECTION");
  Serial.println("================================");

  Serial.print("SSID: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(
    WIFI_SSID,
    WIFI_PASSWORD
  );

  unsigned long startAttempt = millis();

  while (
    WiFi.status() != WL_CONNECTED &&
    millis() - startAttempt < 20000
  ) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("WiFi connected.");

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    Serial.print("RSSI: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");

  } else {

    Serial.println("WiFi connection FAILED.");
    Serial.println("Continuing without Internet time.");
  }


  // ========================================
  // NTP
  // ========================================

  configTime(
    FRANCE_TZ,
    NTP_SERVER_1,
    NTP_SERVER_2
  );

  Serial.println();
  Serial.println("Waiting for NTP time...");

  time_t now = time(nullptr);

  unsigned long ntpStart = millis();

  while (
    now < 100000 &&
    millis() - ntpStart < 15000
  ) {

    delay(250);

    now = time(nullptr);

    Serial.print(".");
  }

  Serial.println();


  if (now >= 100000) {

    clockReady = true;

    Serial.println("NTP synchronized.");

    struct tm timeInfo;

    localtime_r(
      &now,
      &timeInfo
    );

    Serial.printf(
      "Date: %02d/%02d/%04d\n",
      timeInfo.tm_mday,
      timeInfo.tm_mon + 1,
      timeInfo.tm_year + 1900
    );

    Serial.printf(
      "Time: %02d:%02d:%02d\n",
      timeInfo.tm_hour,
      timeInfo.tm_min,
      timeInfo.tm_sec
    );

  } else {

    clockReady = false;

    Serial.println("NTP synchronization FAILED.");
  }

  lastClockUpdate = 0;
}

// === INITIALISATION WIFI + NTP - END


// ========================================
// AFFICHAGE HEURE / DATE
// ========================================

void updateClock(TFT_eSPI &tft) {

  if (
    millis() - lastClockUpdate < 1000
  ) {
    return;
  }

  lastClockUpdate = millis();


  if (!clockReady) {

    tft.fillRect(
      0,
      0,
      tft.width(),
      34,
      TFT_BLACK
    );

    tft.setTextDatum(TL_DATUM);

    tft.setTextColor(
      TFT_YELLOW,
      TFT_BLACK
    );

    tft.setTextSize(1);

    tft.drawString(
      "NO NTP",
      8,
      12
    );

    return;
  }


  time_t now = time(nullptr);

  struct tm timeInfo;

  localtime_r(
    &now,
    &timeInfo
  );


  char timeBuffer[16];
  char dateBuffer[16];


  snprintf(
    timeBuffer,
    sizeof(timeBuffer),
    "%02d:%02d:%02d",
    timeInfo.tm_hour,
    timeInfo.tm_min,
    timeInfo.tm_sec
  );


  snprintf(
    dateBuffer,
    sizeof(dateBuffer),
    "%02d/%02d/%04d",
    timeInfo.tm_mday,
    timeInfo.tm_mon + 1,
    timeInfo.tm_year + 1900
  );


  // ========================================
  // HEADER
  // ========================================

  tft.fillRect(
    0,
    0,
    tft.width(),
    34,
    TFT_BLACK
  );


  tft.setTextDatum(TL_DATUM);

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.setTextSize(2);

  tft.drawString(
    timeBuffer,
    8,
    5
  );


  tft.setTextDatum(TR_DATUM);

  tft.setTextSize(1);

  tft.drawString(
    dateBuffer,
    tft.width() - 8,
    10
  );


  tft.setTextDatum(TL_DATUM);
}

// === AFFICHAGE HEURE / DATE - END

#endif
