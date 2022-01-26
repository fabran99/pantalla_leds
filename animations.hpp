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

void randomDots(){
//  for(int i = 0; i< NUM_LEDS; i++){
//    if(random(0,20)>18){
//      leds[i]=CHSV(random(minHue,maxHue+1),220,255);
//    }
//  }
//  
//  FastLED.show();
//  leds.fadeToBlackBy(40);

  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 40);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( hue + random8(8), 200, 255);
  FastLED.show();
  hue++;
}

void matrixEffect(){
  // start with lowest row to allow proper overlapping on each column
    for (int8_t row=ROWS-1; row>=0; row--)
    {
      for (int8_t col=0; col<COLUMNS; col++)
      {
        if (leds[coordsToPixel(row, col)] == CRGB(82, 240, 255))
        {
          leds[coordsToPixel(row, col)] = CRGB(19, 221, 240); // create trail
          if (row < ROWS-1) leds[coordsToPixel(row+1, col)] = CRGB(82, 240, 255);
        }
      }
    }

    // fade all leds
    for(int i = 0; i < NUM_LEDS; i++) {
      if (leds[i].b != 255) leds[i].nscale8(192); // only fade trail
    }

    // check for empty screen to ensure code spawn
    bool emptyScreen = true;
    for(int i = 0; i < NUM_LEDS; i++) {
      if (leds[i])
      {
        emptyScreen = false;
        break;
      }
    }

    // spawn new falling code
    if (random8(2) == 0 || emptyScreen) // lower number == more frequent spawns
    {
      int8_t spawnX = random8(COLUMNS);
      leds[coordsToPixel(0, spawnX)] = CRGB(82, 240, 255 );
    }

    FastLED.show();
}


void parttrail() {
  // 20 ms frame time is best
  long i = counter;
  px += vx / 8;
  py += vy / 8;

  if (px > COLUMNS - 2 || px <= 0) vx = -vx;


  if (py > ROWS - 2 || py <= 0) vy = -vy;

  if (px < 0) px = 0;
  if (py < 0) py = 0;
  if (px > COLUMNS - 1) px = COLUMNS - 1;
  if (py > ROWS - 1) py = ROWS - 1;

  //leds[XYsafe(px + random8() % 5 - 2 - vx / 4, py + random8() % 5 - 2 - vy / 4)] = CHSV(i / 4, random8(64, 256), random8(32, 200));
  leds[XYsafe(px, py)] = CHSV(i / 4, 255, 255);
  fadeToBlackBy( leds, NUM_LEDS, 32);
  FastLED.show();
  if (i % 3 == 0) {
    vx = vx + random8() % 3 - 1;
    vy = vy + random8() % 3 - 1;
    while (vx / 8 == 0) vx = vx + random8() % 7 - 3;
    while (vy / 8 == 0) vy = vy + random8() % 7 - 3;
    if (vx > 24) vx = 24;
    if (vx < -24) vx = -24;
    if (vy > 16) vy = 16;
    if (vy < -16) vy = -16;
  }
  counter++;
}

void rbow() { //20 ms is best
  hue+=5;
  for(int i = 0; i< NUM_LEDS; i++){
    leds[i] = CHSV(hue, 255,255 )  ;
    if (randomizeDark && random(0, 10) > RANDOM_SHADE)
    {
      leds[i].fadeToBlackBy(SHADE_AMT);
    }
  }
  FastLED.show();
//  int i = counter % 4096;
//  if (i < 2048) {
//    for (byte x = 0; x < COLUMNS; x++) {
//      for (byte y = 0; y < ROWS; y++) {
//        leds[XYsafe(x, y)] = CHSV(cos8(y * i / 50) + sin8(x * 5 + i / 10) + i, 255, 255);
//      }
//    }
//  }
//  else  {
//    i = 4096 - i;
//    for (byte x = 0; x < COLUMNS; x++) {
//      for (byte y = 0; y < ROWS; y++) {
//        leds[XYsafe(x, y)] = CHSV(cos8(y * i / 50) + sin8(x * 5 + i / 10) + i, 255, 255);
//      }
//    }
//  }
//  FastLED.show();
//  counter++;
}

//==========================
// Pacifica
//==========================

// Add one layer of waves into the led array
void pacifica_one_layer( CRGBPalette16& p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff)
{
  uint16_t ci = cistart;
  uint16_t waveangle = ioff;
  uint16_t wavescale_half = (wavescale / 2) + 20;
  for( uint16_t i = 0; i < NUM_LEDS; i++) {
    waveangle += 250;
    uint16_t s16 = sin16( waveangle ) + 32768;
    uint16_t cs = scale16( s16 , wavescale_half ) + wavescale_half;
    ci += cs;
    uint16_t sindex16 = sin16( ci) + 32768;
    uint8_t sindex8 = scale16( sindex16, 240);
    CRGB c = ColorFromPalette( p, sindex8, bri, LINEARBLEND);
    leds[i] += c;
  }
}

// Add extra 'white' to areas where the four layers of light have lined up brightly
void pacifica_add_whitecaps()
{
  uint8_t basethreshold = beatsin8( 9, 55, 65);
  uint8_t wave = beat8( 7 );
  
  for( uint16_t i = 0; i < NUM_LEDS; i++) {
    uint8_t threshold = scale8( sin8( wave), 20) + basethreshold;
    wave += 7;
    uint8_t l = leds[i].getAverageLight();
    if( l > threshold) {
      uint8_t overage = l - threshold;
      uint8_t overage2 = qadd8( overage, overage);
      leds[i] += CRGB( overage, overage2, qadd8( overage2, overage2));
    }
  }
}

// Deepen the blues and greens
void pacifica_deepen_colors()
{
  for( uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i].blue = scale8( leds[i].blue,  145); 
    leds[i].green= scale8( leds[i].green, 200); 
    leds[i] |= CRGB( 2, 5, 7);
  }
}


void pacifica_loop()
{
  // Increment the four "color index start" counters, one for each wave layer.
  // Each is incremented at a different speed, and the speeds vary over time.
  static uint16_t sCIStart1, sCIStart2, sCIStart3, sCIStart4;
  static uint32_t sLastms = 0;
  uint32_t ms = GET_MILLIS();
  uint32_t deltams = ms - sLastms;
  sLastms = ms;
  uint16_t speedfactor1 = beatsin16(3, 179, 269);
  uint16_t speedfactor2 = beatsin16(4, 179, 269);
  uint32_t deltams1 = (deltams * speedfactor1) / 256;
  uint32_t deltams2 = (deltams * speedfactor2) / 256;
  uint32_t deltams21 = (deltams1 + deltams2) / 2;
  sCIStart1 += (deltams1 * beatsin88(1011,10,13));
  sCIStart2 -= (deltams21 * beatsin88(777,8,11));
  sCIStart3 -= (deltams1 * beatsin88(501,5,7));
  sCIStart4 -= (deltams2 * beatsin88(257,4,6));

  // Clear out the LED array to a dim background blue-green
  fill_solid( leds, NUM_LEDS, CRGB( 2, 6, 10));

  // Render each of four layers, with different scales and speeds, that vary over time
  pacifica_one_layer( pacifica_palette_1, sCIStart1, beatsin16( 3, 11 * 256, 14 * 256), beatsin8( 10, 70, 130), 0-beat16( 301) );
  pacifica_one_layer( pacifica_palette_2, sCIStart2, beatsin16( 4,  6 * 256,  9 * 256), beatsin8( 17, 40,  80), beat16( 401) );
  pacifica_one_layer( pacifica_palette_3, sCIStart3, 6 * 256, beatsin8( 9, 10,38), 0-beat16(503));
  pacifica_one_layer( pacifica_palette_3, sCIStart4, 5 * 256, beatsin8( 8, 10,28), beat16(601));

  // Add brighter 'whitecaps' where the waves lines up more
  pacifica_add_whitecaps();

  // Deepen the blues and greens a bit
  pacifica_deepen_colors();
  FastLED.show();
}

void FillLEDsFromPaletteColors(){
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, counter8, 255, currentBlending);
        counter8 += 3;
    }
    FastLED.show();
}
