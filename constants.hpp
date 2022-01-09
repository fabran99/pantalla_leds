const uint8_t ROWS = 6;
const uint8_t COLUMNS = 18;
const uint8_t LED_COUNT = ROWS * COLUMNS;
const uint8_t LED_BRIGHTNESS =25;

const uint8_t NUMBER_HEIGHT = 6;
const uint8_t NUMBER_WIDTH = 3;
const uint8_t RANDOM_SHADE = 7;
const uint8_t SHADE_AMT =100;
//Mensajes
const byte MAX_CHARS = 32;

const uint8_t NUMBER_POSITIONS[11][15] PROGMEM= {
  {0, 1, 2, 18, 20, 36, 38, 54, 56, 72, 74, 90, 91, 92},
  {2, 20, 38, 56, 74, 92},
  {0, 1, 2, 20, 36, 37, 38, 54, 72, 90, 91, 92},
  {0, 1, 2, 20, 36, 37, 38, 56, 74, 90, 91, 92},
  {0, 2, 18, 20, 36, 37, 38, 56, 74, 92},
  {0, 1, 2, 18, 36, 37, 38, 56, 74, 90, 91, 92},
  {0, 1, 2, 18, 36, 37, 38, 54, 56, 72, 74, 90, 91, 92},
  {0, 1, 2, 20, 38, 56, 74, 92},
  {0, 1, 2, 18, 20, 36, 37, 38, 54, 56, 72, 74, 90, 91, 92},
  {0, 1, 2, 18, 20, 36, 37, 38, 56, 74, 90, 91, 92},
  {19, 73}
};
const uint8_t NUMBER_QUANTITY[11] PROGMEM={14, 6, 12, 12, 10, 12,14, 8, 15, 13,2};
