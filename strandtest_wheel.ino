#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

//Custom imports
#include "constants.hpp"
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

#include "utils.hpp"

bool horizontal = false;
const int colorCount = ROWS;
bool repeat = true;
bool addBlack = false;
int dir = 0;
int colorList[colorCount][3];
int color1[3] = {0, 179, 255};
int color2[3] = {110, 43, 255};
int gradient[LED_COUNT][3];
//int colorGrid[LED_COUNT][3];

bool clockTick = true;
int cicleCounter = 0;
int delayTime = 200;

void setup(void)
{
  Serial.begin(9600);
  while (!Serial)
  {
    delay(100);
  }
#if defined(__AVR_ATtiny85__)
  if (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  strip.begin();
  strip.setBrightness(LED_BRIGHTNESS);
  strip.show(); // Initialize all pixels to 'off'

  Serial.println("Inicio");
  //  getSingleColorEffect(colorGrid, color1);
  generateGradient(colorList, color1, color2, colorCount, repeat, addBlack);
  getGradientEffect(gradient, colorList, horizontal);
}

void loop()
{

  //  showColorList(gradient, true);
  //  delay(50);
  //  moveColorList(colorList, colorCount, dir);
  //  getGradientEffect(gradient, colorList, horizontal);
  drawCurrentTime(gradient, clockTick, false);
  //  drawCurrentTime(colorGrid, clockTick, true);
  cicleCounter += 1;
  if (cicleCounter * delayTime == 1000)
  {
    cicleCounter = 0;
    clockTick = !clockTick;
  }
  delay(delayTime);
  moveColorList(colorList, colorCount, dir);
  getGradientEffect(gradient, colorList, horizontal);
}
