int coordsToPixel(int row, int col)
{
  return row * COLUMNS + col;
};

//======================================
// COLORS
//======================================

//void shadeColor(int ar[3], int amt)
//{
//  ar[0] = max(min(255, ar[0] + amt), 0);
//  ar[1] = max(min(255, ar[1] + amt), 0);
//  ar[2] = max(min(255, ar[2] + amt), 0);
//};

void generateGradient(int ar[], int color1, int color2, int colorCount, bool repeat = false, bool addBlack = false)
{
  float alpha = 0.0;
  int repeatLimit = (colorCount / 2);
  int diff = (color2 - color1) / colorCount;
  for(int i = 0; i < colorCount; i++){
    if(addBlack && i==colorCount-1){
      ar[i] = 0;
      break;
    }
    if (repeat && i > repeatLimit)
    {
      int prevIndex = repeatLimit - (i - repeatLimit);
      ar[i] = ar[prevIndex];
    }
    else{
      ar[i] = color1 + diff*i;
    }
    
  }

//    ar[i][0]=0;
//    ar[i][1]=0;
//    ar[i][2]=0;  
//  }
//  for (int i = 0; i < colorCount; i++)
//  {
//    if (addBlack && i == colorCount - 1)
//    {
//      ar[i][0] = 0;
//      ar[i][1] = 0;
//      ar[i][2] = 0;
//      break;
//    }
//    if (repeat && i > repeatLimit)
//    {
//      int prevIndex = repeatLimit - (i - repeatLimit);
//      ar[i][0] = ar[prevIndex][0];
//      ar[i][1] = ar[prevIndex][1];
//      ar[i][2] = ar[prevIndex][2];
//    }
//    else
//    {
//      alpha += (1.0 / colorCount);
//      ar[i][0] = color1[0] * alpha + (1 - alpha) * color2[0];
//      ar[i][1] = color1[1] * alpha + (1 - alpha) * color2[1];
//      ar[i][2] = color1[2] * alpha + (1 - alpha) * color2[2];
//    }
//  }
};

//============================================
// Draw to strip
//============================================
//void showMatrix(int matrix[ROWS][COLUMNS][3]){
////  Recorro la matriz y voy asignando cada color a la tira, finalmente hago show
//  for(int row = 0; row < ROWS; row++){
//    for(int col = 0; col < COLUMNS; col++){
//      int currentPixel = row * COLUMNS + col;
//      int currentColor[3] = {matrix[row][col][0],matrix[row][col][1],matrix[row][col][2]};
//      strip.setPixelColor(currentPixel,
//      strip.Color(currentColor[0],currentColor[1],currentColor[2]));
//    }
//  }
//  strip.show();
//};

void showColorList(int colors[LED_COUNT], bool randomizeDark)
{
  for (int i = 0; i < LED_COUNT; i++)
  {
//    int currentColor = ;
    
    //    Serial.print(i);
    //    Serial.print(currentColor[0]);
    //    Serial.print(",");
    //    Serial.print(currentColor[1]);
    //    Serial.print(",");
    //    Serial.print(currentColor[2]);
    //    Serial.println();
    //    delay(10);
    leds[i] = CHSV(colors[i],255,255);
    if (randomizeDark && random(0, 10) > RANDOM_SHADE)
    {
//      shadeColor(currentColor, -SHADE_AMT);
      leds[i].fadeToBlackBy(SHADE_AMT);
    }
//    leds[i].setRGB(125,0,125);


    // strip.setPixelColor(i, strip.Color(currentColor[0], currentColor[1], currentColor[2]));
  }
   FastLED.show();
};

//======================================
// UTILS
//======================================

void moveColorList(int ar[], int arlen, int dir)
{
  //  1 = derecha, el resto es izquierda
  int lastIndex = arlen - 1;
  if (dir == 1)
  {
    int edge = ar[lastIndex];
    for (int i = lastIndex; i >= 0; i--)
    {
      ar[i]=ar[i-1];
//      for (int j = 0; j < 3; j++)
//      {
//        ar[i][j] = ar[i - 1][j];
//      }
    }
//    for (int i = 0; i < 3; i++)
//    {
//      ar[0][i] = edge[i];
//    }
    ar[0]=edge;
  }
  else
  {
    int edge = ar[0];
    for (int i = 0; i < lastIndex; i++)
    {
      ar[i]=ar[i+1];
//      for (int j = 0; j < 3; j++)
//      {
//        ar[i][j] = ar[i + 1][j];
//      }
    }
//    for (int i = 0; i < 3; i++)
//    {
//      ar[lastIndex][i] = edge[i];
//    }
    ar[lastIndex]=edge;
  }
};

//void getNumberPosition(int currentNumberPosition[NUMBER_HEIGHT][NUMBER_WIDTH], int number)
//{
//  for (int i = 0; i < NUMBER_HEIGHT; i++)
//  {
//    for (int j = 0; j < NUMBER_WIDTH; j++)
//    {
//      Serial.println("Numero: ");
//      Serial.print(number);
//      Serial.print("valor: ");
//      Serial.println(NUMBER_POSITIONS[0][0][0]);
//       
//      
//      currentNumberPosition[i][j] = NUMBER_POSITIONS[0][0][0];
//    }
//  }
//}
//
//void getNumberRow(int row[NUMBER_WIDTH], int currentNumberPosition[NUMBER_HEIGHT][NUMBER_WIDTH], int rowN)
//{
//  for (int i = 0; i < NUMBER_WIDTH; i++)
//  {
//    row[i] = currentNumberPosition[rowN][i];
//  }
//}

//==================================
// Matrix generation
//==================================

void getGradientEffect(int ar[LED_COUNT], int colorList[], bool horizontal)
{
  for (int row = 0; row < ROWS; row++)
  {
    for (int col = 0; col < COLUMNS; col++)
    {
      int currentPixel = coordsToPixel(row, col);
      int colorListIndex = horizontal ? col : row;
//      int currentColor[3] = {
//        colorList[horizontal ? col : row][0],
//        colorList[horizontal ? col : row][1],
//        colorList[horizontal ? col : row][2]
//      };
//      for(int i = 0; i<3; i++){
//        ar[currentPixel][i]=colorList[colorListIndex][i];
//      }
        ar[currentPixel]=colorList[colorListIndex];
//      ar[currentPixel][0] = currentColor[0];
//      ar[currentPixel][1] = currentColor[1];
//      ar[currentPixel][2] = currentColor[2];
    }
  }
};

void getSingleColorEffect(int ar[LED_COUNT], int color)
{
  for (int row = 0; row < ROWS; row++)
  {
    for (int col = 0; col < COLUMNS; col++)
    {
      int currentPixel = coordsToPixel(row, col);
      ar[currentPixel] = color;
//      ar[currentPixel][0] = color[0];
//      ar[currentPixel][1] = color[1];
//      ar[currentPixel][2] = color[2];
//      for(int i = 0; i<3; i++){
//        ar[currentPixel][i]=color[i];
//      }
    }
  }
}

//==============================================
// TIME
//==============================================
//void getTimeDigits(int digits[4])
//{
//  tmElements_t tm;
//  if (RTC.read(tm))
//  {
//    digits[0] = tm.Hour / 10;
//    digits[1] = tm.Hour % 10;
//    digits[2] = tm.Minute / 10;
//    digits[3] = tm.Minute % 10;
//  }
//}

void drawNumber(int number, int rowStart, int colStart, int colorList[LED_COUNT], bool showStrip = false, bool randomizeDark = false)
{
  int startPixel = coordsToPixel(rowStart, colStart);
  for(int i = 0; i<NUMBER_QUANTITY[number]; i++){
    int pixel = startPixel + NUMBER_POSITIONS[number][i];
//    int currentColor[3] = {colorList[pixel][0], colorList[pixel][1], colorList[pixel][2]};
    
    
    leds[pixel] = CHSV(colorList[pixel], 255,255);
    if(randomizeDark && random(0,10)>RANDOM_SHADE){
//        shadeColor(currentColor, -SHADE_AMT);
    leds[pixel].fadeToBlackBy(SHADE_AMT);
    }
  }
  if (showStrip)
  {
    FastLED.show();
  }
}

void drawCurrentTime(int colorList[LED_COUNT], bool clockTick = true, bool randomizeDark = false)
{
   FastLED.clear();
   tmElements_t tm;
  if (RTC.read(tm))
  {
  drawNumber(tm.Hour / 10, 0, 0, colorList, false, randomizeDark);
  drawNumber(tm.Hour % 10, 0, 4, colorList, false, randomizeDark);
  drawNumber(tm.Minute / 10, 0, 10, colorList, false, randomizeDark);
  drawNumber(tm.Minute % 10, 0, 14, colorList, false, randomizeDark);
  }

  if (clockTick)
  {
    drawNumber(10, 0, 7, colorList, false, randomizeDark);
  }
   FastLED.show();
}
