
bool horizontal = false;
uint8_t colorCount = horizontal ? COLUMNS : ROWS;
bool reverseGradient = false;
bool addBlack = false;
bool randomizeDark = false;
uint8_t dir = 0;
int colorList[18][3];
uint8_t color1[3] = {0, 255, 149};
uint8_t color2[3] = {0, 136, 255};
uint8_t colorGrid[LED_COUNT][3]; // Plantear eliminar este dato para ahorrar memoria
bool gradientMode = false;
bool moveGradient = true;
int delayTime = 1000/10;

//===========================
// Serial
//===========================
char receivedChars[MAX_CHARS];
bool newData = false;
//===========================
// Modo
//===========================
uint8_t currentMode = 0; 
// 0 = reloj
// 1 = colores/degradados
// 2 = concentricHueShift
// 3 = Dibujo manual
// 4 = animacion por js


//================================
// Variables para efectos
//================================
// Hue
uint8_t hue = 0;
uint8_t minHue = 0;
uint8_t maxHue =255;
bool hueRotation = true;
int hueChangeSpeed = 1;
// Aleatoriedad
