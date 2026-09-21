#ifndef SCREEN_SPLASH2_H
#define SCREEN_SPLASH2_H

#include <Arduino.h>
#include <TFT_eSPI.h>

#define SPLASH_DURATION 3000

void drawScreenSplash2(TFT_eSPI &tft) {
  const int16_t w = tft.width();
  const int16_t h = tft.height();

  tft.fillScreen(TFT_BLACK);

  tft.setTextDatum(MC_DATUM);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  tft.drawString("3x0c3t_BO4RD", w / 2, h / 2 - 20);

  tft.setTextSize(1);
  tft.drawString("ScreenSplash2", w / 2, h / 2 + 10);

  tft.drawString("M4KE W1TH L0VE", w / 2, h / 2 + 35);

  tft.setTextDatum(TL_DATUM);
}

// === SCREEN SPLASH2 - END

#endif
