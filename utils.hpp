uint8_t coordsToPixel(uint8_t row, uint8_t col)
{
  return row * COLUMNS + col;
};

//======================================
// COLORS
//======================================

void generateGradient(int ar[], uint8_t color1, uint8_t color2, uint8_t colorCount, bool repeat = false, bool addBlack = false)
{
  uint8_t repeatLimit = (colorCount / 2);
  uint8_t diff = (color2 - color1) / colorCount;
  for (uint8_t i = 0; i < colorCount; i++)
  {
    if (addBlack && i == colorCount - 1)
    {
      ar[i] = 0;
      break;
    }
    if (repeat && i > repeatLimit)
    {
      uint8_t prevIndex = repeatLimit - (i - repeatLimit);
      ar[i] = ar[prevIndex];
    }
    else
    {
      ar[i] = color1 + diff * i;
    }
  }
};

//============================================
// Draw to strip
//============================================

void showColorList(uint8_t colors[LED_COUNT], bool randomizeDark)
{
  for (uint8_t i = 0; i < LED_COUNT; i++)
  {
    leds[i] = CHSV(colors[i], 255, 255);
    if (randomizeDark && random(0, 10) > RANDOM_SHADE)
    {
      //      shadeColor(currentColor, -SHADE_AMT);
      leds[i].fadeToBlackBy(SHADE_AMT);
    }
  }
  FastLED.show();
};

//======================================
// UTILS
//======================================

void moveColorList(int ar[], uint8_t arlen, uint8_t dir)
{
  //  1 = derecha, el resto es izquierda
  uint8_t lastIndex = arlen - 1;
  if (dir == 1)
  {
    uint8_t edge = ar[lastIndex];
    for (uint8_t i = lastIndex; i >= 0; i--)
    {
      ar[i] = ar[i - 1];
    }
    ar[0] = edge;
  }
  else
  {
    uint8_t edge = ar[0];
    for (uint8_t i = 0; i < lastIndex; i++)
    {
      ar[i] = ar[i + 1];
    }
    ar[lastIndex] = edge;
  }
};

//==================================
// Matrix generation
//==================================

void getGradientEffect(uint8_t ar[LED_COUNT], int colorList[], bool horizontal)
{
  for (uint8_t row = 0; row < ROWS; row++)
  {
    for (uint8_t col = 0; col < COLUMNS; col++)
    {
      uint8_t currentPixel = coordsToPixel(row, col);
      uint8_t colorListIndex = horizontal ? col : row;
      ar[currentPixel] = colorList[colorListIndex];
    }
  }
};

void getSingleColorEffect(uint8_t ar[LED_COUNT], uint8_t color)
{
  for (uint8_t row = 0; row < ROWS; row++)
  {
    for (uint8_t col = 0; col < COLUMNS; col++)
    {
      uint8_t currentPixel = coordsToPixel(row, col);
      ar[currentPixel] = color;
    }
  }
}

//==============================================
// TIME
//==============================================

void drawNumber(uint8_t number, uint8_t rowStart, uint8_t colStart, uint8_t colorList[LED_COUNT], bool showStrip = false, bool randomizeDark = false)
{
  uint8_t startPixel = coordsToPixel(rowStart, colStart);
  uint8_t totalElements = pgm_read_byte_near(&(NUMBER_QUANTITY[number]));
  for (uint8_t i = 0; i < totalElements; i++)
  {
    uint8_t currentPosition = pgm_read_byte_near(&(NUMBER_POSITIONS[number][i]));
//    Serial.println(currentPosition);
    uint8_t pixel = startPixel + currentPosition;
    //    uint8_t currentColor[3] = {colorList[pixel][0], colorList[pixel][1], colorList[pixel][2]};

    leds[pixel] = CHSV(colorList[pixel], 255, 255);
    if (randomizeDark && random(0, 10) > RANDOM_SHADE)
    {
      //        shadeColor(currentColor, -SHADE_AMT);
      leds[pixel].fadeToBlackBy(SHADE_AMT);
    }
  }
  if (showStrip)
  {
    FastLED.show();
  }
}

void drawCurrentTime(uint8_t colorList[LED_COUNT], bool randomizeDark = false)
{
  FastLED.clear();
  tmElements_t tm;
  if (RTC.read(tm))
  {
    drawNumber(tm.Hour / 10, 0, 0, colorList, false, randomizeDark);
    drawNumber(tm.Hour % 10, 0, 4, colorList, false, randomizeDark);
    drawNumber(tm.Minute / 10, 0, 10, colorList, false, randomizeDark);
    drawNumber(tm.Minute % 10, 0, 14, colorList, false, randomizeDark);
    if (tm.Second%2==0)
    {
    drawNumber(10, 0, 7, colorList, false, randomizeDark);
    }
  }

  
  FastLED.show();
}
