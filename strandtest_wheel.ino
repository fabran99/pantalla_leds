#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

//Custom imports
#include "constants.hpp"
#include "data_definitions.hpp"
#include "variables.hpp"
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

#include "utils.hpp"

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
//  Serial.println("inicio");
//  Serial.println(currentColorCount);
  generateGradient(currentGradient.colorList,
                   currentGradient.color1,
                   currentGradient.color2,
                   currentColorCount,
                   currentGradient.repeat,
                   currentGradient.addBlack);
  getGradientEffect(currentGradient.colorMatrix, currentGradient.colorList, currentConfig.isHorizontalGradient);
}

void loop()
{
//  Serial.println("hola");
//    for(int i = 0; i<ROWS; i++){
//      Serial.println(i);
//    Serial.print(currentGradient.colorList[i].r);
//    Serial.print(",");
//    Serial.print(currentGradient.colorList[i].g);
//    Serial.print(",");
//    Serial.print(currentGradient.colorList[i].b);  
//    Serial.println();
//  }
//  showColorList(currentGradient.colorMatrix, false);
 int i = 1;
 Serial.print(currentGradient.colorList[i].r);
    Serial.print(",");
    Serial.print(currentGradient.colorList[i].g);
    Serial.print(",");
    Serial.print(currentGradient.colorList[i].b);  
    Serial.println();
//    clearAllPixels();
  drawCurrentTime(currentGradient.colorMatrix, currentClockConfig.showTick, false);
//  moveColorList(currentGradient.colorList, ROWS, currentConfig.gradientDirection);
//        for(int i = 0; i<ROWS; i++){
//      Serial.println(i);
 
    Serial.print(currentGradient.colorList[i].r);
    Serial.print(",");
    Serial.print(currentGradient.colorList[i].g);
    Serial.print(",");
    Serial.print(currentGradient.colorList[i].b);  
    Serial.println();
//  }
  delay(100000);
//  getGradientEffect(currentGradient.colorMatrix, currentGradient.colorList, currentConfig.isHorizontalGradient);
//      for(int i = 0; i<ROWS; i++){
//      Serial.println(i);
//    Serial.print(currentGradient.colorList[i].r);
//    Serial.print(",");
//    Serial.print(currentGradient.colorList[i].g);
//    Serial.print(",");
//    Serial.print(currentGradient.colorList[i].b);  
//    Serial.println();
//  }
//  getGradientEffect(currentGradient.colorMatrix, currentGradient.colorList, currentConfig.isHorizontalGradient);
//  delay(currentClockConfig.delayTime);
//  delay(100000);

  //  showColorList(gradient, true);
  //  delay(50);
  //  moveColorList(colorList, colorCount, dir);
  //  getGradientEffect(gradient, colorList, horizontal);
//  drawCurrentTime(currentGradient.colorList, currentClockConfig.showTick, false);
//  delay(100000);
  //  drawCurrentTime(colorGrid, clockTick, true);
//  currentClockConfig.cicleCounter += 1;
//  if (currentClockConfig.cicleCounter * currentClockConfig.delayTime == 1000)
//  {
//    currentClockConfig.cicleCounter = 0;
//    currentClockConfig.showTick = !currentClockConfig.showTick;
//  }
//  delay(currentClockConfig.delayTime);
//  moveColorList(currentGradient.colorList, ROWS, currentConfig.gradientDirection);
//  getGradientEffect(currentGradient.colorMatrix, currentGradient.colorList, currentConfig.isHorizontalGradient);
}
