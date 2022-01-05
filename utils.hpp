uint8_t coordsToPixel(uint8_t row, uint8_t col)
{
  return row * COLUMNS + col;
};

//======================================
// COLORS
//======================================

void generateGradient(uint8_t color1[3], uint8_t color2[3])
{
  uint8_t repeatLimit = (colorCount / 2);
  // uint8_t diff = (color2 - color1) / colorCount;
  float alpha = 0.0;
  for (int i = 0; i < colorCount; i++)
  {
    if (addBlack && i == colorCount - 1)
    {
      // ar[i] = {0, 0, 0};
      colorList[i][0] = 0;
      colorList[i][1] = 0;
      colorList[i][2] = 0;
      break;
    }
    if (reverseGradient && i > repeatLimit)
    {
      uint8_t prevIndex = repeatLimit - (i - repeatLimit);
      // colorList[i] = {colorList[prevIndex][0], colorList[prevIndex][1], colorList[prevIndex][2]};
      for (uint8_t j = 0; j < 3; j++)
      {
        colorList[i][j] = colorList[prevIndex][j];
      }
    }
    else
    {
      alpha += (1.0 / colorCount);
      for (int j = 0; j < 3; j++)
      {
        colorList[i][j] = (color1[j] * alpha + (1 - alpha) * color2[j]);
      }
    }
  }
};

//============================================
// Draw to strip
//============================================

void showColorGrid()
{
  for (uint8_t i = 0; i < LED_COUNT; i++)
  {
    leds[i] = CRGB(colorGrid[i][0], colorGrid[i][1], colorGrid[i][2]);
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

void moveColorList()
{
  //  1 = derecha, el resto es izquierda
  uint8_t lastIndex = colorCount - 1;
  if (dir == 1)
  {
    uint8_t edge[3] = {colorList[lastIndex][0], colorList[lastIndex][1], colorList[lastIndex][2]};
    for (uint8_t i = lastIndex; i >= 0; i--)
    {
      for (int j = 0; j < 3; j++)
      {
        colorList[i][j] = colorList[i - 1][j];
      }
    }
    for (int j = 0; j < 3; j++)
    {
      colorList[0][j] = edge[j];
    }
  }
  else
  {
    // uint8_t edge = colorList[0];
    uint8_t edge[3] = {colorList[0][0], colorList[0][1], colorList[0][2]};
    for (uint8_t i = 0; i < lastIndex; i++)
    {
      // colorList[i] = colorList[i + 1];
      for (uint8_t j = 0; j < 3; j++)
      {
        colorList[i][j] = colorList[i + 1][j];
      }
    }
    // colorList[lastIndex] = edge;
    for (uint8_t j = 0; j < 3; j++)
    {
      colorList[lastIndex][j] = edge[j];
    }
  }
};

//==================================
// Matrix generation
//==================================

void getGradientEffect()
{
  for (uint8_t row = 0; row < ROWS; row++)
  {
    for (uint8_t col = 0; col < COLUMNS; col++)
    {
      uint8_t currentPixel = coordsToPixel(row, col);
      uint8_t colorListIndex = horizontal ? col : row;
      for (int i = 0; i < 3; i++)
      {
        colorGrid[currentPixel][i] = colorList[colorListIndex][i];
      }
    }
  }
};

void getSingleColorEffect(uint8_t color[3])
{
  for (uint8_t row = 0; row < ROWS; row++)
  {
    for (uint8_t col = 0; col < COLUMNS; col++)
    {
      uint8_t currentPixel = coordsToPixel(row, col);

      for (int i = 0; i < 3; i++)
      {
        colorGrid[currentPixel][i] = color[i];
      }
    }
  }
}

//==============================================
// TIME
//==============================================

void drawNumber(uint8_t number, uint8_t rowStart, uint8_t colStart)
{
  uint8_t startPixel = coordsToPixel(rowStart, colStart);
  uint8_t totalElements = pgm_read_byte_near(&(NUMBER_QUANTITY[number]));
  for (uint8_t i = 0; i < totalElements; i++)
  {
    uint8_t currentPosition = pgm_read_byte_near(&(NUMBER_POSITIONS[number][i]));
    //    Serial.println(currentPosition);
    uint8_t pixel = startPixel + currentPosition;
    //    uint8_t currentColor[3] = {colorList[pixel][0], colorList[pixel][1], colorList[pixel][2]};

    leds[pixel] = CRGB(colorGrid[pixel][0], colorGrid[pixel][1], colorGrid[pixel][2]);
    if (randomizeDark && random(0, 10) > RANDOM_SHADE)
    {
      //        shadeColor(currentColor, -SHADE_AMT);
      leds[pixel].fadeToBlackBy(SHADE_AMT);
    }
  }
}

void drawCurrentTime()
{
  FastLED.clear();
  tmElements_t tm;
  if (RTC.read(tm))
  {
    drawNumber(tm.Hour / 10, 0, 0);
    drawNumber(tm.Hour % 10, 0, 4);
    drawNumber(tm.Minute / 10, 0, 10);
    drawNumber(tm.Minute % 10, 0, 14);
    if (tm.Second % 2 == 0)
    {
      drawNumber(10, 0, 7);
    }
  }

  FastLED.show();
}

//==================================
// Leer de serial
//==================================
void handleReceivedChars(char receivedChars[MAX_CHARS])
{
  switch (receivedChars[0])
  {
  // Cambio de modo
  case 'M':
  {
    uint8_t newMode = String(receivedChars[1]).toInt();
    if(newMode == currentMode){
      break;  
    }
    if (newMode >= 0 && newMode <= 3)
    {
      currentMode = newMode;
      // Si entro a modo manual limpio la pantalla
      if (currentMode == 3)
      {
        uint8_t black[3] = {0, 0, 0};
        getSingleColorEffect(black);
        randomizeDark = false;
      }
      else
      {
        if (gradientMode)
        {
          generateGradient(color1, color2);
          getGradientEffect();
        }
        else
        {
          getSingleColorEffect(color1);
        }
      }
    }
    break;
  }
  // Cambio aleatoriedad de shading
  case 'D':
  {
    uint8_t newRandomizeDark = String(receivedChars[1]).toInt();
    randomizeDark = newRandomizeDark ? true : false;
    break;
  }
  // Cambio horizontal
  case 'H':
  {
    uint8_t isHorizontal = String(receivedChars[1]).toInt();
    horizontal = isHorizontal ? true : false;
    colorCount = horizontal ? COLUMNS : ROWS;
    if (gradientMode)
    {
      generateGradient(color1, color2);
      getGradientEffect();
    }
    break;
  }
  // Modo degradado
  case 'G':
  {
    uint8_t isGradient = String(receivedChars[1]).toInt();
    gradientMode = isGradient ? true : false;
    if (gradientMode)
    {
      generateGradient(color1, color2);
      getGradientEffect();
    }
    else
    {
      getSingleColorEffect(color1);
    }
    break;
  }
  // Invertir degradado
  case 'R':
  {
    uint8_t isReversed = String(receivedChars[1]).toInt();
    reverseGradient = isReversed ? true : false;
    if (gradientMode)
    {
      generateGradient(color1, color2);
      getGradientEffect();
    }
    break;
  }
  // color 1
  case 'A':
  {
    Serial.println("Color 1");
    char r[4];
    char g[4];
    char b[4];
    uint8_t prevIndex = 1;
    uint8_t nIdx = 0;
    // Tomo los valores de r
    for (int i = prevIndex; i < prevIndex + 3; i++)
    {
      Serial.println(receivedChars[i]);
      if (receivedChars[i] == ',')
      {
        prevIndex = i + 1;
        break;
      }
      r[nIdx] = receivedChars[i];
      nIdx++;
      if (nIdx == 3)
      {
        prevIndex = i + 2;
      }
    }
    r[nIdx] = '\0';
    // Tomo los valores de g
    nIdx = 0;
    for (int i = prevIndex; i < prevIndex + 3; i++)
    {
      Serial.println(receivedChars[i]);
      if (receivedChars[i] == ',')
      {
        prevIndex = i + 1;
        break;
      }
      g[nIdx] = receivedChars[i];
      nIdx++;
      if (nIdx == 3)
      {
        prevIndex = i + 2;
      }
    }
    g[nIdx] = '\0';
    // Tomo los valores de b
    nIdx = 0;
    for (int i = prevIndex; i < prevIndex + 3; i++)
    {
      if (receivedChars[i] == ',')
      {
        prevIndex = i + 1;
        break;
      }
      b[nIdx] = receivedChars[i];
      nIdx++;
    }
    b[nIdx] = '\0';
    color1[0] = atoi(r);
    color1[1] = atoi(g);
    color1[2] = atoi(b);

    if (gradientMode)
    {
      generateGradient(color1, color2);
      getGradientEffect();
    }
    else
    {
      getSingleColorEffect(color1);
    }
    break;
  }
  // color 2
  case 'B':
  {
    Serial.println("Color 2");
    char r[4];
    char g[4];
    char b[4];
    uint8_t prevIndex = 1;
    uint8_t nIdx = 0;
    // Tomo los valores de r
    for (int i = prevIndex; i < prevIndex + 3; i++)
    {
      if (receivedChars[i] == ',')
      {
        prevIndex = i + 1;
        break;
      }
      r[nIdx] = receivedChars[i];
      nIdx++;
      if (nIdx == 3)
      {
        prevIndex = i + 2;
      }
    }
    r[nIdx] = '\0';
    // Tomo los valores de g
    nIdx = 0;
    for (int i = prevIndex; i < prevIndex + 3; i++)
    {
      if (receivedChars[i] == ',')
      {
        prevIndex = i + 1;
        break;
      }
      g[nIdx] = receivedChars[i];
      nIdx++;
      if (nIdx == 3)
      {
        prevIndex = i + 2;
      }
    }
    g[nIdx] = '\0';
    // Tomo los valores de b
    nIdx = 0;
    for (int i = prevIndex; i < prevIndex + 3; i++)
    {
      if (receivedChars[i] == ',')
      {
        prevIndex = i + 1;
        break;
      }
      b[nIdx] = receivedChars[i];
      nIdx++;
    }
    b[nIdx] = '\0';
    color2[0] = atoi(r);
    color2[1] = atoi(g);
    color2[2] = atoi(b);

    if (gradientMode)
    {
      generateGradient(color1, color2);
      getGradientEffect();
    }
    else
    {
      getSingleColorEffect(color2);
    }
    break;
  }
  case 'P':
  {
    if(currentMode != 3){
      break;  
    }
    Serial.println("Pixel");
    char pixel[4];
    char r[4];
    char g[4];
    char b[4];
    uint8_t prevIndex = 1;
    uint8_t nIdx = 0;
    // Tomo el pixel
    for (int i = prevIndex; i < prevIndex + 3; i++)
    {
      if (receivedChars[i] == ',')
      {
        prevIndex = i + 1;
        break;
      }
      pixel[nIdx] = receivedChars[i];
      nIdx++;
      if (nIdx == 3)
      {
        prevIndex = i + 2;
      }
    }
    pixel[nIdx] = '\0';
    nIdx=0;
    
    // Tomo los valores de r
    for (int i = prevIndex; i < prevIndex + 3; i++)
    {
      if (receivedChars[i] == ',')
      {
        prevIndex = i + 1;
        break;
      }
      r[nIdx] = receivedChars[i];
      nIdx++;
      if (nIdx == 3)
      {
        prevIndex = i + 2;
      }
    }
    r[nIdx] = '\0';
    // Tomo los valores de g
    nIdx = 0;
    for (int i = prevIndex; i < prevIndex + 3; i++)
    {
      if (receivedChars[i] == ',')
      {
        prevIndex = i + 1;
        break;
      }
      g[nIdx] = receivedChars[i];
      nIdx++;
      if (nIdx == 3)
      {
        prevIndex = i + 2;
      }
    }
    g[nIdx] = '\0';
    // Tomo los valores de b
    nIdx = 0;
    for (int i = prevIndex; i < prevIndex + 3; i++)
    {
      if (receivedChars[i] == ',')
      {
        prevIndex = i + 1;
        break;
      }
      b[nIdx] = receivedChars[i];
      nIdx++;
    }
    b[nIdx] = '\0';
    colorGrid[atoi(pixel)][0] = atoi(r);
    colorGrid[atoi(pixel)][1] = atoi(g);
    colorGrid[atoi(pixel)][2] = atoi(b);
    break;
  }
  default:
  {
    Serial.println("default");
    break;
  }
  }
}

void readFromSerial()
{
  static byte ndx = 0;
  char rc;
  static boolean recvInProgress = false;
  char startMarker = '<';
  char endMarker = '>';

  while (BT.available() > 0 && newData == false)
  {
    rc = BT.read();
    if (recvInProgress)
    {
      if (rc != endMarker)
      {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= MAX_CHARS)
        {
          ndx = MAX_CHARS - 1;
        }
      }
      else
      {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }
    else if (rc == startMarker)
    {
      recvInProgress = true;
    }
  }

  if (newData)
  {
    newData = false;
    handleReceivedChars(receivedChars);
  }
}

//==================================
// Efectos extra
//==================================
void concentricHueShift()
{
  hue = minHue;
  hueChangeSpeed = max(1, (maxHue - minHue) / (NUM_LEDS / 2));
  for (int i = 0; i < NUM_LEDS / 2; i++)
  {
    // fade everything out
    leds.fadeToBlackBy(40);

    // let's set an led value
    if (hueRotation)
    {
      hue += hueChangeSpeed;
    }
    if (hue > maxHue || hue < minHue)
    {
      hueChangeSpeed *= -1;
    }
    leds[i] = CHSV(hue, 255, 255);
    // now, let's first 20 leds to the top 20 leds,
    leds(NUM_LEDS / 2, NUM_LEDS - 1) = leds(NUM_LEDS / 2 - 1, 0);
    FastLED.show();
    FastLED.delay(33);
  }
}
