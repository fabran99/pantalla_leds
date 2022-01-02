int coordsToPixel(int row, int col)
{
  return row * COLUMNS + col;
};

//======================================
// COLORS
//======================================

rgbColor shadeColor(rgbColor color, int amt)
{
  rgbColor newColor = {max(min(255, color.r + amt), 0), max(min(255, color.g + amt), 0), max(min(255, color.b + amt), 0)};
  return newColor;
};

void generateGradient(rgbColor ar[], rgbColor color1, rgbColor color2, int colorCount, bool repeat = false, bool addBlack = false)
{
  float alpha = 0.0;
  int repeatLimit = (colorCount / 2);
  for (int i = 0; i < colorCount; i++)
  {
    if (addBlack && i == colorCount - 1)
    {
      rgbColor black = {0,0,0};
      ar[i] = black;
      break;
    }
    if (repeat && i > repeatLimit)
    {
      int prevIndex = repeatLimit - (i - repeatLimit);
      rgbColor currentColor = {ar[prevIndex].r,ar[prevIndex].g,ar[prevIndex].b};
      // ar[i][0] = ar[prevIndex][0];
      // ar[i][1] = ar[prevIndex][1];
      // ar[i][2] = ar[prevIndex][2];
      ar[i] = currentColor;
    }
    else
    {
//      Serial.print("=====================");
      alpha += (1.0 / colorCount);
      // ar[i][0] = color1[0] * alpha + (1-alpha)* color2[0];
      // ar[i][1] = color1[1] * alpha + (1-alpha)* color2[1];
      // ar[i][2] = color1[2] * alpha + (1-alpha)* color2[2];
      rgbColor newColor = {color1.r * alpha + (1 - alpha) * color2.r, color1.g * alpha + (1 - alpha) * color2.g, color1.b * alpha + (1 - alpha) * color2.b};
      ar[i] = newColor;
//      Serial.print(newColor.r);
//      Serial.print(",");
//      Serial.print(newColor.g);
//      Serial.print(",");
//      Serial.print(newColor.b);
//      Serial.println("=====================");
    }
  }
  
};

//============================================
// Draw to strip
//============================================
// void showMatrix(int matrix[ROWS][COLUMNS][3]){
// //  Recorro la matriz y voy asignando cada color a la tira, finalmente hago show
//   for(int row = 0; row < ROWS; row++){
//     for(int col = 0; col < COLUMNS; col++){
//       int currentPixel = row * COLUMNS + col;
//       int currentColor[3] = {matrix[row][col][0],matrix[row][col][1],matrix[row][col][2]};
//       strip.setPixelColor(currentPixel,
//       strip.Color(currentColor[0],currentColor[1],currentColor[2]));
//     }
//   }
//   strip.show();
// };

void showColorList(rgbColor colors[LED_COUNT], bool randomizeDark)
{
  for (int i = 0; i < LED_COUNT; i++)
  {
    rgbColor currentColor = {colors[i].r, colors[i].g,colors[i].b};
    float n = random(0, 10);
    if (randomizeDark && n > 7)
    {
      currentColor = shadeColor(currentColor, -15);
    }
    //    Serial.print(i);
    //    Serial.print(currentColor[0]);
    //    Serial.print(",");
    //    Serial.print(currentColor[1]);
    //    Serial.print(",");
    //    Serial.print(currentColor[2]);
    //    Serial.println();
    //    delay(10);
    strip.setPixelColor(i, strip.Color(currentColor.r, currentColor.g, currentColor.b));
  }
  strip.show();
};

//======================================
// UTILS
//======================================

void moveColorList(rgbColor ar[], int arlen, int dir)
{
  //  1 = derecha, el resto es izquierda
  int lastIndex = arlen - 1;
  if (dir == 1)
  {
    rgbColor edge = {ar[lastIndex].r, ar[lastIndex].g,ar[lastIndex].b};
    for (int i = lastIndex; i >= 0; i--)
    {
      // for(int j = 0; j<3; j++){
      //   ar[i][j]=ar[i-1][j]  ;
      // }
      rgbColor tmpColor = {ar[i - 1].r, ar[i - 1].g, ar[i - 1].b};
      ar[i] = tmpColor;
    }
    // for(int i = 0; i<3; i++){
    //     ar[0][i]=edge[i] ;
    //  }
    ar[0] = {edge.r, edge.g, edge.b};
  }
  else
  {
    // int edge[3] =  {ar[0][0],ar[0][1], ar[0][2] };
    rgbColor edge = {ar[0].r, ar[0].g,ar[0].b};
    for (int i = 0; i < lastIndex; i++)
    {
      // for(int j = 0; j<3; j++){
      //   ar[i][j]=ar[i+1][j]  ;
      // }
      rgbColor tmpColor = {ar[i + 1].r, ar[i + 1].g, ar[i + 1].b};
      ar[i] = tmpColor;
    }
    // for(int i = 0; i<3; i++){
    //     ar[lastIndex][i]=edge[i] ;
    //  }
    ar[lastIndex] = {edge.r, edge.g,edge.b};
  }
};

void getNumberPosition(int currentNumberPosition[NUMBER_HEIGHT][NUMBER_WIDTH], int number)
{
  for (int i = 0; i < NUMBER_HEIGHT; i++)
  {
    for (int j = 0; j < NUMBER_WIDTH; j++)
    {
      currentNumberPosition[i][j] = NUMBER_POSITIONS[number][i][j];
    }
  }
}

void getNumberRow(int row[NUMBER_WIDTH], int currentNumberPosition[NUMBER_HEIGHT][NUMBER_WIDTH], int rowN)
{
  for (int i = 0; i < NUMBER_WIDTH; i++)
  {
    row[i] = currentNumberPosition[rowN][i];
  }
}

//==================================
// Matrix generation
//==================================

void getGradientEffect(rgbColor ar[], rgbColor colorList[], bool horizontal)
{
  for (int row = 0; row < ROWS; row++)
  {
    for (int col = 0; col < COLUMNS; col++)
    {
      int currentPixel = coordsToPixel(row, col);
      rgbColor currentColor = {
        colorList[horizontal ? col : row].r, 
        colorList[horizontal ? col : row].g,
        colorList[horizontal ? col : row].b};
      // ar[currentPixel][0] = currentColor[0];
      // ar[currentPixel][1] = currentColor[1];
      // ar[currentPixel][2] = currentColor[2];
      ar[currentPixel] = currentColor;
    }
  }
};

void clearAllPixels(){
    
    for(int i=0; i<LED_COUNT; i++){
      strip.setPixelColor(i, strip.Color(0,0,0));  
    }
    strip.show();
}

void getSingleColorEffect(rgbColor ar[LED_COUNT], rgbColor color)
{
  for (int row = 0; row < ROWS; row++)
  {
    for (int col = 0; col < COLUMNS; col++)
    {
      int currentPixel = coordsToPixel(row, col);
      // ar[currentPixel][0] = color[0];
      // ar[currentPixel][1] = color[1];
      // ar[currentPixel][2] = color[2];
      ar[currentPixel] = {color.r, color.g, color.b};
    }
  }
}

//==============================================
// TIME
//==============================================
timeDigits getTimeDigits()
{
  tmElements_t tm;
  timeDigits digits = {0, 0, 0, 0};
   if (RTC.read(tm))
   {
     int digits1 = tm.Hour / 10;
     int digits2 = tm.Hour % 10;
     int digits3 = tm.Minute / 10;
     int digits4 = tm.Minute % 10;
     digits = {
         digits1,
         digits2,
         digits3,
         digits4};
   }
  return digits;
}

void drawNumber(int number, int rowStart, int colStart, rgbColor colorList[LED_COUNT], bool showStrip = false, bool randomizeDark = false)
{
  int currentNumberPosition[NUMBER_HEIGHT][NUMBER_WIDTH];
  getNumberPosition(currentNumberPosition, number);
  for (int i = 0; i < NUMBER_HEIGHT; i++)
  {
    int row[3];
    getNumberRow(row, currentNumberPosition, i);

    for (int j = 0; j < NUMBER_WIDTH; j++)
    {
      int pixel = coordsToPixel(rowStart + i, colStart + j);
//      Serial.println(pixel);
      if (row[j] == 1)
      {
//        int tmpList[3] = {colorList[pixel].r, colorList[pixel].g, colorList[pixel].b};
//        rgbColor currentColor = {tmpList[3][0], colorList[pixel].g, colorList[pixel].b};
//        if (randomizeDark && random(0, 10) > 7)
//        {
//          currentColor = shadeColor(currentColor, -40);
//        }
//        Serial.print(pixel);
//        Serial.print(": ");
//        Serial.print(currentColor.r);
//        Serial.print(",");
//        Serial.print(currentColor.g);
//        Serial.print(",");
//        Serial.print(currentColor.b);
//        Serial.println();
        strip.setPixelColor(pixel,
                            strip.Color(255,255,255));
//        Serial.println("if");
      }
      else{
//        Serial.println("else");
//        strip.setPixelColor(pixel, strip.Color(255,255,255));  
strip.setPixelColor(pixel, strip.Color(255,255,255));  
      }
    }
  }
  if (showStrip)
  {
    strip.show();
  }
}

void drawCurrentTime(rgbColor colorList[LED_COUNT], bool clockTick = true, bool randomizeDark = false)
{
 
  timeDigits digits = getTimeDigits();
//  Serial.println("dentro");
//  // // dibujo la hora
//  // for (int i = 0; i < 4; i++)
//  // {
    int i = 1;
    Serial.print(currentGradient.colorList[i].r);
    Serial.print(",");
    Serial.print(currentGradient.colorList[i].g);
    Serial.print(",");
    Serial.print(currentGradient.colorList[i].b);  
    Serial.println();
    strip.clear();
//  drawNumber(digits.hourFirst, DIGIT_POSITIONS[0][0], DIGIT_POSITIONS[0][1], colorList, false, false);
//  Serial.println(strip.getPixelColor(107));
//  drawNumber(digits.hourSecond, DIGIT_POSITIONS[1][0], DIGIT_POSITIONS[1][1], colorList, false, randomizeDark);
//  drawNumber(digits.minuteFirst, DIGIT_POSITIONS[2][0], DIGIT_POSITIONS[2][1], colorList, false, randomizeDark);
//  drawNumber(digits.minuteSecond, DIGIT_POSITIONS[3][0], DIGIT_POSITIONS[3][1], colorList, false, randomizeDark);
////  // }
//   if (clockTick)
//   {
//     drawNumber(10, DIGIT_POSITIONS[4][0], DIGIT_POSITIONS[4][1], colorList, false, randomizeDark);
//   }

  Serial.print(currentGradient.colorList[i].r);
    Serial.print(",");
    Serial.print(currentGradient.colorList[i].g);
    Serial.print(",");
    Serial.print(currentGradient.colorList[i].b);  
    Serial.println();
//  strip.show();
}
