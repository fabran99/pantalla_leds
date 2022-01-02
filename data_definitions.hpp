struct rgbColor
{
    int r;
    int g;
    int b;
};

struct namedColorList
{
    rgbColor red = {255, 60, 46};      //rojo
    rgbColor orange = {255, 123, 46};  //naranja
    rgbColor green = {133, 255, 46};   //verde
    rgbColor aqua = {46, 255, 157};    //verde agua
    rgbColor skyblue = {46, 234, 255}; //celeste
    rgbColor blue = {46, 109, 255};    //Azul
    rgbColor purple = {102, 46, 255};  //lila
    rgbColor violet = {168, 46, 255};  //violeta
    rgbColor pink = {255, 46, 182};    //rosa
    rgbColor salmon = {255, 46, 88};   //salmon
    rgbColor black = {0,0,0};   //negro
    rgbColor white = {255,255,255};   //blanco
};

struct globalConfig
{
    bool usingGradient = true;
    bool isHorizontalGradient = false;
    int gradientDirection = 1;
    int currentMode = 0;        // 0 = clock, 1 = animation
    int currentColorScheme = 1; // 0 = fixed, 1 = gradient, 2 = fixed with shades, 3 gradient with shades
};

struct gradient
{
    rgbColor color1;
    rgbColor color2;
    bool repeat;
    bool addBlack;
    int colorCount;
    rgbColor colorMatrix[LED_COUNT];
    rgbColor colorList[];
};

struct clockConfig
{
    bool active = true;
    bool showTick = true;
    int cicleCounter = 0;
    int delayTime = 200;
    bool randomizeDark = false;
};

struct timeDigits
{
    int hourFirst;
    int hourSecond;
    int minuteFirst;
    int minuteSecond;
};
