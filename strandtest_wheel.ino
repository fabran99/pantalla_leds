#include <SoftwareSerial.h>
#include <FastLED.h>
#define NUM_LEDS 108
//#define COLOR_ORDER GRB
//#define CHIPSET WS2812B
CRGBArray<NUM_LEDS> leds;
SoftwareSerial BT(11,10);

//Custom imports
#include "constants.hpp"
#include "extra_animations.hpp"
#define PIN 6

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

#include "config.hpp"
#include "utils.hpp"


void setup(void)
{
  Serial.begin(9600);
  BT.begin(38400);
  while (!Serial)
  {
    delay(100);
  }
  FastLED.addLeds<WS2812B, 6,GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(LED_BRIGHTNESS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);
  FastLED.clear();
  FastLED.show();

  Serial.println("Inicio");
  randomSeed(analogRead(0));

//  Seteo valores default;
  if(gradientMode){
    generateGradient(color1, color2);
    getGradientEffect();  
  }
  else{
    getSingleColorEffect(color1);  
  }
}

void loop()
{
  //============================
  // Leo el serial
  //============================
  readFromSerial();
  
  //============================
  // Modo reloj
  //============================
  if(currentMode == 0){
    //Muestro el reloj
    drawCurrentTime();
    delay(delayTime);
    // Actualizo variables
    if(gradientMode && moveGradient){
      moveColorList();
      getGradientEffect();
    }
  }
  else if(currentMode == 1){
    // Muestro la pantalla
    showColorGrid();
    delay(delayTime);
    // Actualizo variables
    if(gradientMode && moveGradient){
      moveColorList();
      getGradientEffect();
    }
  }
  else if(currentMode == 2){
    concentricHueShift();
  }
  else if(currentMode == 3){
    // Muestro la pantalla manual
    showColorGrid();
    delay(delayTime);
  }
  else if(currentMode == 4){
    runOptimizedDrawing();
    delay(delayTime);  
  }

  
}
