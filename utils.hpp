uint8_t coordsToPixel(uint8_t row, uint8_t col)
{
  return row * COLUMNS + col;
};



uint16_t XYsafe( int x, int y) {
  if ( x >= COLUMNS) return NUM_LEDS;
  if ( y >= ROWS) return NUM_LEDS;

  if ( x < 0 ) return NUM_LEDS;
  if ( y < 0 ) return NUM_LEDS;

  return coordsToPixel(y, x);
}

void pixelToCoords(uint8_t pixel, uint8_t row, uint8_t col){
  row = pixel/COLUMNS;
  col = pixel%COLUMNS;  
}

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

void localGenerateGradient(uint8_t clist[][3], uint8_t cCount, uint8_t c1[3], uint8_t c2[3])
{
  float alpha = 0.0;
  for (int i = 0; i < cCount; i++)
  {
      alpha += (1.0 / cCount);
      for (int j = 0; j < 3; j++)
      {
        clist[i][j] = (c1[j] * alpha + (1 - alpha) * c2[j]);
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

void updatePalette(){
    if(gradientMode){
//      uint8_t clist[16][3];
//      localGenerateGradient(clist, 16, color1, color2);
//      for(int i = 0; i<16; i++){
//        currentPalette[i]=CRGB(clist[i][0],clist[i][1],clist[i][2]);  
//      }
//      Serial.println(CRGB(color1[0], color1[1],color1[2]));
      fill_solid( currentPalette, 16, CRGB::Black);
      currentPalette[0] = CRGB(color1[0], color1[1],color1[2]);
      currentPalette[1] = CRGB(color2[0], color2[1],color2[2]);
      currentPalette[4] = CRGB(color1[0], color1[1],color1[2]);
      currentPalette[5] = CRGB(color2[0], color2[1],color2[2]);
      currentPalette[8] = CRGB(color1[0], color1[1],color1[2]);
      currentPalette[9] = CRGB(color2[0], color2[1],color2[2]);
      currentPalette[12] = CRGB(color1[0], color1[1],color1[2]);
      currentPalette[13] = CRGB(color2[0], color2[1],color2[2]);
    }
    else{
      // 'black out' all 16 palette entries...
      fill_solid( currentPalette, 16, CRGB::Black);
      // and set every fourth one to color1.
      currentPalette[0] = CRGB(color1[0], color1[1],color1[2]);
      currentPalette[4] = CRGB(color1[0], color1[1],color1[2]);
      currentPalette[8] = CRGB(color1[0], color1[1],color1[2]);
      currentPalette[12] = CRGB(color1[0], color1[1],color1[2]);  
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
  tmElements_t tm;
    FastLED.clear();
//  
  if (RTC.read(tm)){
    h1 = tm.Hour / 10;
    h2 = tm.Hour % 10;
    m1 = tm.Minute / 10;
    m2 = tm.Minute % 10;
    s = tm.Second;
  }
  else{
//  Serial.println("no pude leer");  
  }
    drawNumber(h1, 0, 0);
    drawNumber(h2, 0, 4);
    drawNumber(m1, 0, 10);
    drawNumber(m2, 0, 14);
    if (s % 2 == 0)
    {
      drawNumber(10, 0, 7);
    }

  FastLED.show();
}

//==================================
// Leer de serial
//==================================
int StrToHex(char str[]){
  return (int) strtol(str, 0, 16);
}

void handleReceivedChars(char receivedChars[MAX_CHARS])
{
  switch (receivedChars[0])
  {
  // Cambio de modo
  case 'M':
  {
    uint8_t newMode = String(receivedChars[1]).toInt();
    // chequeo si no es el modo 10
    if(newMode == 1 && receivedChars[2] != '>'){
      char nm[3] = {receivedChars[1], receivedChars[2], '\0'};
      newMode = String(nm).toInt();
    }
    if(newMode == currentMode && (currentMode != 5 && currentMode != 3)){
      break;  
    }
    if (newMode >= 0 && newMode <= 10)
    {
      currentMode = newMode;
      // Si entro a modo manual limpio la pantalla
      if (currentMode == 3)
      {
        uint8_t black[3] = {0, 0, 0};
        getSingleColorEffect(black);
      }
      // Tomo los hue en estos modos
      else if(currentMode == 2){
        // En este paso los hue minimos y maximos   
        char minh[4] = {receivedChars[2],receivedChars[3],receivedChars[4],'\0'};
        char maxh[4] = {receivedChars[5],receivedChars[6],receivedChars[7],'\0'};
        minHue = atoi(minh);
        maxHue = atoi(maxh);  
//        FastLED.clear();
      }
      else if(currentMode == 5 || currentMode == 6 || currentMode == 7 || currentMode == 8 || currentMode ==9){
        // En este limpio la tira
        counter=0;
        FastLED.clear();
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
  // Cambio direccion del movimiento en degradado
//  case 'd':
//  {
//    dir = String(receivedChars[1]).toInt();
//    break;
//  }
//  Cambio el hue para las animaciones
  case 'h':
  {
    char nhue[4] = {receivedChars[1],receivedChars[2],receivedChars[3],'\0'};
    hue= atoi(nhue);
    break;
  }
  // Cambio horizontal
  case 'H':
  {
    uint8_t isHorizontal = String(receivedChars[1]).toInt();
    horizontal = isHorizontal ? true : false;
    colorCount = horizontal ? COLUMNS : ROWS;
    bool showingThis = (currentMode == 0 || currentMode == 1);
    if (gradientMode && showingThis)
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
    bool showingThis = (currentMode == 0 || currentMode == 1 || currentMode == 10);
    updatePalette();
    if (gradientMode && showingThis )
    {
        generateGradient(color1, color2);
        getGradientEffect();   
    }
    else if(showingThis)
    {
      getSingleColorEffect(color1);
    }
    break;
  }
  // agregar franja negra
  case 'b':
  {
    uint8_t shouldAddBlack = String(receivedChars[1]).toInt();
    addBlack = shouldAddBlack ? true : false;
    bool showingThis = (currentMode == 0 || currentMode == 1);
    if (gradientMode && showingThis)
    {
      generateGradient(color1, color2);
      getGradientEffect();
    }
    break;
  }
  // Invertir degradado
  case 'R':
  {
    uint8_t isReversed = String(receivedChars[1]).toInt();
    reverseGradient = isReversed ? true : false;
    
    bool showingThis = (currentMode == 0 || currentMode == 1);
    if (gradientMode && showingThis)
    {
      generateGradient(color1, color2);
      getGradientEffect();
    }
    break;
  }
  // Aplicar hora nueva
  case 'T':
  {
    tmElements_t tm;
    char y[5] = {receivedChars[1],receivedChars[2],receivedChars[3],receivedChars[4],'\0'};
    tm.Year = String(y).toInt();
    char m[3] = {receivedChars[5],receivedChars[6],'\0'};
    tm.Month = String(m).toInt();
    char d[3] = {receivedChars[7],receivedChars[8],'\0'};
    tm.Day = String(d).toInt();
    char h[3] = {receivedChars[9],receivedChars[10],'\0'};
    tm.Hour = String(h).toInt();
    char mn[3] = {receivedChars[11],receivedChars[12],'\0'};
    tm.Minute = String(mn).toInt();
    char s[3] = {receivedChars[13],receivedChars[14],'\0'};
    tm.Second = String(s).toInt();
    RTC.write(tm);
    break;
  }
  // Cambiar brillo
  case 'L':
  {
    char brightness[5] = {receivedChars[1],receivedChars[2],receivedChars[3],'\0'};
    LED_BRIGHTNESS = String(brightness).toInt();
    FastLED.setBrightness(LED_BRIGHTNESS);
    break;
  }
  // color 1
  case 'A':
  {
    Serial.println("Color 1");
    char r[4] = {receivedChars[1],receivedChars[2],receivedChars[3],'\0'};
    char g[4] = {receivedChars[4],receivedChars[5],receivedChars[6],'\0'};
    char b[4]= {receivedChars[7],receivedChars[8],receivedChars[9],'\0'};
    color1[0] = atoi(r);
    color1[1] = atoi(g);
    color1[2] = atoi(b);
    updatePalette();
    
    bool showingThis = (currentMode == 0 || currentMode == 1 || currentMode == 10);

    if (gradientMode && showingThis)
    {
        generateGradient(color1, color2);
        getGradientEffect();    
    }
    else if(showingThis)
    {
      getSingleColorEffect(color1);
    }
    break;
  }
  // color 2
  case 'B':
  {
    Serial.println("Color 2");
    char r[4] = {receivedChars[1],receivedChars[2],receivedChars[3],'\0'};
    char g[4] = {receivedChars[4],receivedChars[5],receivedChars[6],'\0'};
    char b[4]= {receivedChars[7],receivedChars[8],receivedChars[9],'\0'};
    color2[0] = atoi(r);
    color2[1] = atoi(g);
    color2[2] = atoi(b);

    bool showingThis = (currentMode == 0 || currentMode == 1 || currentMode == 10);

    if (gradientMode && showingThis)
    {
      if(currentMode == 10){
        updatePalette();
      }
      else{
        generateGradient(color1, color2);
        getGradientEffect();    
      }
    }
    else if(showingThis)
    {
      getSingleColorEffect(color1);
    }
    break;
  }
  case 'P':
  {
    if(currentMode != 3){
      break;  
    }
    Serial.println("Pixel");
    char pixel[4] = {receivedChars[1],receivedChars[2],receivedChars[3],'\0'};
    char r[4] = {receivedChars[4],receivedChars[5],receivedChars[6],'\0'};
    char g[4]= {receivedChars[7],receivedChars[8],receivedChars[9],'\0'};
    char b[4]= {receivedChars[10],receivedChars[11],receivedChars[12],'\0'};
  
    colorGrid[atoi(pixel)][0] = atoi(r);
    colorGrid[atoi(pixel)][1] = atoi(g);
    colorGrid[atoi(pixel)][2] = atoi(b);
    break;
  }
  // Muestro tira
  case 'S':
  {
    FastLED.show();
    break;
  }
  // Limpio tira
  case 'c':
  {
    FastLED.clear();
    break;
  }
  // aplico color a una lista de pixeles en hexadecimal
  case 'C':
  {
//    Serial.println(receivedChars);
    char r[3] = {receivedChars[1],receivedChars[2],'\0'};
    char g[3]= {receivedChars[3],receivedChars[4],'\0'};
    char b[3]= {receivedChars[5],receivedChars[6],'\0'};
    CRGB currentColor = CRGB(StrToHex(r), StrToHex(g),StrToHex(b));
    
    int posCounter = 7;
    char pos[3] = {'0','0','\0'};
    while(posCounter < MAX_CHARS){
      pos[0] = receivedChars[posCounter];
      pos[1] = receivedChars[posCounter +1];
      if(pos[0] == '|' || pos[1] == '|'){
        break;
      }
      colorGrid[StrToHex(pos)][0] = currentColor.r;
      colorGrid[StrToHex(pos)][1] = currentColor.g;
      colorGrid[StrToHex(pos)][2] = currentColor.b;
      posCounter +=2;
    }
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
