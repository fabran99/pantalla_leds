
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
uint8_t currentMode = 9; 
// 0 = reloj
// 1 = colores/degradados
// 2 = concentricHueShift
// 3 = Dibujo manual
// 4 = animacion por js
// 5 = puntos random
// 6 = efecto matrix
// 7 = arcoiris random
// 8 = particulas voladoras
// 9 = pacifica


//================================
// Variables para efectos
//================================
// Hue
uint8_t hue = 140;
uint8_t minHue = 0;
uint8_t maxHue =255;
bool hueRotation = true;
int hueChangeSpeed = 20;
int vx = 16;
int vy = 8;
int px = 0;
int py = 4;
long counter=0;

// pacifica
CRGBPalette16 pacifica_palette_1 = 
    { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117,
      0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x14554B, 0x28AA50 };
CRGBPalette16 pacifica_palette_2 = 
    { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
      0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x0C5F52, 0x19BE5F };
CRGBPalette16 pacifica_palette_3 = 
    { 0x000208, 0x00030E, 0x000514, 0x00061A, 0x000820, 0x000927, 0x000B2D, 0x000C33, 
      0x000E39, 0x001040, 0x001450, 0x001860, 0x001C70, 0x002080, 0x1040BF, 0x2060FF };
