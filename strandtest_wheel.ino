#include <FastLED.h>
#define NUM_LEDS 108
//#define COLOR_ORDER GRB
//#define CHIPSET WS2812B
CRGBArray<NUM_LEDS> leds;

//Custom imports
#include "constants.hpp"
#define PIN 6

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

#include "utils.hpp"

bool horizontal = false;
uint8_t colorCount = horizontal ? COLUMNS : ROWS;
bool repeat = false;
bool addBlack = false;
uint8_t dir = 0;
int colorList[18];
uint8_t color1 = 220;
uint8_t color2 = 180;
uint8_t colorGrid[LED_COUNT]; // Plantear eliminar este dato para ahorrar memoria
uint8_t currentMode = 0;

long delayTime = 1000 / 10;

void setup(void)
{
  Serial.begin(9600);
  while (!Serial)
  {
    delay(100);
  }
  FastLED.addLeds<WS2812B, 6>(leds, NUM_LEDS);
  FastLED.setBrightness(LED_BRIGHTNESS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);
  FastLED.clear();
  FastLED.show();

  Serial.println("Inicio");
  randomSeed(analogRead(0));
   generateGradient(colorList, color1, color2, colorCount, repeat, addBlack);
   getGradientEffect(colorGrid, colorList, horizontal);
//  getSingleColorEffect(colorGrid, color1);
}

void loop()
{

  drawCurrentTime(colorGrid, true);
  delay(delayTime);
//  moveColorList(colorList, colorCount, dir);
//  getGradientEffect(colorGrid, colorList, horizontal);
}
