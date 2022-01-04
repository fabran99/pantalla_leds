const int ROWS = 6;
const int COLUMNS = 18;
const int LED_COUNT = ROWS * COLUMNS;
const int LED_BRIGHTNESS = 20;

const int NUMBER_HEIGHT = 6;
const int NUMBER_WIDTH = 3;
const int RANDOM_SHADE = 7;
const int SHADE_AMT =100;

const int NUMBER_POSITIONS[11][15] = {
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
const int NUMBER_QUANTITY[11]={14, 6, 12, 12, 10, 12,14, 8, 15, 13,2};
