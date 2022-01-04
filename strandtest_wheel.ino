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
int colorCount = horizontal ? COLUMNS : ROWS;
bool repeat = false;
bool addBlack = false;
int dir = 0;
int colorList[18];
//int veColorList[10][3];
//int color1[3] = {31, 244, 255};
//int color2[3] = {176, 31, 255};
int color1=220;
int color2=170;
int colorGrid[LED_COUNT]; // Plantear eliminar este dato para ahorrar memoria
int currentMode = 0;

bool clockTick = true;
int cicleCounter = 0;
long delayTime = 1000/10;

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
  //  getSingleColorEffect(colorGrid, color1);
//  Serial.println(colorCount);
  generateGradient(colorList, color1, color2, colorCount, repeat, addBlack);
//  
////  moveColorList(colorList, colorCount, dir);
//  getGradientEffect(colorGrid, colorList, horizontal);
//  for(int i = 0; i<colorCount; i++){
//    Serial.println(colorList[i]);
//  }
//  getSingleColorEffect(colorGrid, color1);
//  Serial.println(colorCount);
}

void loop()
{

  

   cicleCounter += 1;
//   if (currentMode == 0)
//   {
////  Serial.println(colorCount);
//    Serial.println("ejecuto");
     drawCurrentTime(colorGrid, clockTick, true);
     if ((cicleCounter * delayTime) % 1000 == 0){
      clockTick = !clockTick;
//         int c1 = random(0, 12);
//       int c2 = random(0, 12);
//       color1[0] = (int)defaultColors[c1][0];
//       color1[1] = defaultColors[c1][1];
//       color1[2] = defaultColors[c1][2];
//       color2[0] = defaultColors[c2][0];
//       color2[1] = defaultColors[c2][1];
//       color2[2] = defaultColors[c2][2];
//       generateGradient(colorList, color1, color2, colorCount, repeat, addBlack);

//  getSingleColorEffect(colorGrid, color1);
     }
////  Serial.println(colorCount);
//     if ((cicleCounter * delayTime) % 1000 == 0)
//     {
//       //      cicleCounter = 0;
//       clockTick = !clockTick;
//     }
//
//  //   //    Serial.println((cicleCounter * delayTime)%1300);
//     if ((cicleCounter * delayTime) % 2000 == 0)
//     {
//  //     //      Serial.println("test");
//       currentMode = 1;
//       dir = !dir;
      
//  //     //      horizontal=!horizontal;
//  //     int c1[3] = {random(0, 256), random(0, 256), random(0, 256)};
//  //     int c2[3] = {random(0, 256), random(0, 256), random(0, 256)};
////       
//     }
//   }
//   else
//   {
//  showColorList(colorGrid, false);
//  
//     if ((cicleCounter * delayTime) % 2000 == 0)
//     {
//                   int c1idx = (int)random(0,12);
//             int c2idx = (int)random(0,12);
//             color1[0] = defaultColors[c1idx][0];
//             color1[1] = defaultColors[c1idx][1];
//             color1[2] = defaultColors[c1idx][2];
//             color2[0] = defaultColors[c2idx][0];
//             color2[1] = defaultColors[c2idx][1];
//             color2[2] = defaultColors[c2idx][2];
//       generateGradient(colorList, color1, color2, colorCount, repeat, addBlack);
//       currentMode = 0;
//  //     //      horizontal = !horizontal;

//  //     //      Serial.println(defaultColors[c1idx][0]);
//     }
//   }
  //  Serial.println("comienz");
   
   Serial.print(color1);
   Serial.print(",");
   Serial.print(color2);
   Serial.println(" ");
//  getSingleColorEffect(colorGrid, color1);
  delay(delayTime);
//  if ((cicleCounter * delayTime) % 300 == 0){
//    moveColorList(colorList, colorCount, dir);
//  }
//  
//   color1+=2;
//   color2+=2;
//  if(color1>255 && color2>255){
//    color1-=255;
//    color2-=255;  
//  }
//  generateGradient(colorList, color1, color2, colorCount, repeat, addBlack);
  getGradientEffect(colorGrid, colorList, horizontal);
}
