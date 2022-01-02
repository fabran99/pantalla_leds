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
bool repeat = false;
bool addBlack = false;
int dir = 0;
int colorList[colorCount][3];
//int veColorList[10][3];
int color1[3] = {31, 244, 255};
int color2[3] = {176, 31, 255};
int colorGrid[LED_COUNT][3];
int currentMode = 0;

bool clockTick = true;
int cicleCounter = 0;
long delayTime = 100;

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
  randomSeed(analogRead(0));
  //  getSingleColorEffect(colorGrid, color1);
  generateGradient(colorList, color1, color2, colorCount, repeat, addBlack);
  getGradientEffect(colorGrid, colorList, horizontal);
}

void loop()
{
  int c1[3];
  int c2[3];
//  Serial.println(delayTime);
//    showColorList(colorGrid, false);
//    delay(2000);
  //  delay(50);
  //  moveColorList(colorList, colorCount, dir);
  //  getGradientEffect(gradient, colorList, horizontal);
  cicleCounter += 1;
  if(currentMode == 0){
    drawCurrentTime(colorGrid, clockTick, false);
    if ((cicleCounter * delayTime)%1000 == 0)
    {
//      cicleCounter = 0;
      clockTick = !clockTick;
    }
    
//    Serial.println((cicleCounter * delayTime)%1300);
    if((cicleCounter * delayTime)%2000 == 0){
//      Serial.println("test");
//      currentMode = 1;   
      dir = !dir;
//      horizontal=!horizontal;
      int c1[3]={random(0,256),random(0,256),random(0,256)};
      int c2[3]={random(0,256),random(0,256),random(0,256)};
      generateGradient(colorList,c1 , c2, colorCount, repeat, addBlack);
    }
  }
  else{
    showColorList(colorGrid, false);
    if((cicleCounter * delayTime)%2000 == 0){
      currentMode = 0;
//      horizontal = !horizontal; 
//      int c1idx = (int)random(0,12);
//      int c2idx = (int)random(0,12);
//      color1[0] = random(0,256);
//      color1[1] = random(0,256);
//      color1[2] = random(0,256);
//      color2[0] = random(0,256);
//      color2[1] = random(0,256);
//      color2[2] = random(0,256);
//      c1[0] = defaultColors[c1idx][0];
//      c1[1] = defaultColors[c1idx][1];
//      c1[2] = defaultColors[c1idx][2];
//      c2[0] = defaultColors[c2idx][0];
//      c2[1] = defaultColors[c2idx][1];
//      c2[2] = defaultColors[c2idx][2];
      int c1[3]={random(0,256),random(0,256),random(0,256)};
      int c2[3]={random(0,256),random(0,256),random(0,256)};
      generateGradient(colorList,c1 , c2, colorCount, repeat, addBlack);
//      Serial.println(defaultColors[c1idx][0]);
    }
  }
//  Serial.println("comienz");
  delay(delayTime);
  moveColorList(colorList, colorCount, dir);
//  generateGradient(horizontal ? hzColorList : veColorList, color1, color2, colorCount, repeat, addBlack);
  getGradientEffect(colorGrid, colorList, horizontal);
}
