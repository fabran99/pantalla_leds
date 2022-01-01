int coordsToPixel(int row, int col){
  return row * COLUMNS + col;
};

//======================================
// COLORS
//======================================

void shadeColor(int ar[3], int amt){
    ar[0] = max(min(255, ar[0] + amt), 0);
    ar[1] = max(min(255, ar[1] + amt), 0);
    ar[2] = max(min(255, ar[2] + amt), 0);
};

void generateGradient(int ar[][3], int color1[3], int color2[3], int colorCount, bool repeat=false, bool addBlack=false){
  float alpha = 0.0;
  int repeatLimit = (colorCount/2);
  for(int i = 0; i<colorCount; i++){
      if (addBlack && i == colorCount -1){
        ar[i][0] = 0;
        ar[i][1] = 0;
        ar[i][2] = 0;
        break;
      }
      if(repeat && i>repeatLimit){
        int prevIndex = repeatLimit-(i-repeatLimit);
        ar[i][0] = ar[prevIndex][0];
        ar[i][1] = ar[prevIndex][1];
        ar[i][2] = ar[prevIndex][2];
        
      }
      else{
        alpha+= (1.0/colorCount);
        ar[i][0] = color1[0] * alpha + (1-alpha)* color2[0];
        ar[i][1] = color1[1] * alpha + (1-alpha)* color2[1];
        ar[i][2] = color1[2] * alpha + (1-alpha)* color2[2];
      }
  }
};

//============================================
// Draw to strip
//============================================
void showMatrix(int matrix[ROWS][COLUMNS][3]){
//  Recorro la matriz y voy asignando cada color a la tira, finalmente hago show
  for(int row = 0; row < ROWS; row++){
    for(int col = 0; col < COLUMNS; col++){
      int currentPixel = row * COLUMNS + col;
      int currentColor[3] = {matrix[row][col][0],matrix[row][col][1],matrix[row][col][2]};
      strip.setPixelColor(currentPixel,
      strip.Color(currentColor[0],currentColor[1],currentColor[2]));  
    }  
  }
  strip.show();
};

void showColorList(int colors[LED_COUNT][3], bool randomizeDark){
  for(int i=0; i< LED_COUNT; i++){
    int currentColor[3] = {colors[i][0],colors[i][1],colors[i][2]};
    float n = random(0,10);
    if(randomizeDark && n > 7){
      shadeColor(currentColor, -15);
    }
//    Serial.print(i);
//    Serial.print(currentColor[0]);
//    Serial.print(",");
//    Serial.print(currentColor[1]);
//    Serial.print(",");
//    Serial.print(currentColor[2]);
//    Serial.println();
//    delay(10);
    strip.setPixelColor(i, strip.Color(currentColor[0],currentColor[1],currentColor[2]));  
  }
  strip.show();
};


//======================================
// UTILS
//======================================

void moveColorList(int ar[][3], int arlen, int dir){
    //  1 = derecha, el resto es izquierda
    int lastIndex = arlen -1;
    if(dir == 1){
      int edge[3] = {ar[lastIndex][0],ar[lastIndex][1], ar[lastIndex][2] };
      for(int i = lastIndex; i>=0; i--){
        for(int j = 0; j<3; j++){
          ar[i][j]=ar[i-1][j]  ;
        }
       
      }
      for(int i = 0; i<3; i++){
          ar[0][i]=edge[i] ;
       }
    }
    else{
      int edge[3] =  {ar[0][0],ar[0][1], ar[0][2] };
      for(int i = 0; i<lastIndex; i++){
        for(int j = 0; j<3; j++){
          ar[i][j]=ar[i+1][j]  ;
        }
       
      }
      for(int i = 0; i<3; i++){
          ar[lastIndex][i]=edge[i] ;
       }
    }
};

void getNumberPosition(int currentNumberPosition[NUMBER_HEIGHT][NUMBER_WIDTH], int number){
  for(int i = 0; i<NUMBER_HEIGHT;i++){
    for(int j = 0; j< NUMBER_WIDTH; j++){
      currentNumberPosition[i][j]=NUMBER_POSITIONS[number][i][j];
    }
  }
}

void getNumberRow(int row[NUMBER_WIDTH], int currentNumberPosition[NUMBER_HEIGHT][NUMBER_WIDTH], int rowN){
  for(int i = 0; i< NUMBER_WIDTH; i++){
    row[i] = currentNumberPosition[rowN][i];  
  }
}


//==================================
// Matrix generation
//==================================

void getGradientEffect(int ar[LED_COUNT][3], int colorList[][3], bool horizontal){
  for (int row = 0; row< ROWS; row++ ){
    for(int col = 0; col < COLUMNS; col++){
        int currentPixel = coordsToPixel(row, col);
        int currentColor[3] = {
          colorList[horizontal ? col : row][0], 
          colorList[horizontal ? col : row][1], 
          colorList[horizontal ? col : row][2] 
        };
        ar[currentPixel][0] = currentColor[0];
        ar[currentPixel][1] = currentColor[1];
        ar[currentPixel][2] = currentColor[2];
    }  
  }  
};

void getSingleColorEffect(int ar[LED_COUNT][3], int color[3]){
  for (int row = 0; row< ROWS; row++ ){
    for(int col = 0; col < COLUMNS; col++){
        int currentPixel = coordsToPixel(row, col);
        ar[currentPixel][0] = color[0];
        ar[currentPixel][1] = color[1];
        ar[currentPixel][2] = color[2];
    }  
  }  
}

//==============================================
// TIME
//==============================================
void getTimeDigits(int digits[4] ){
  tmElements_t tm;
  if(RTC.read(tm)){
    digits[0]= tm.Hour/10;
    digits[1]= tm.Hour%10;
    digits[2]= tm.Minute/10;
    digits[3]= tm.Minute%10;
  } 
}



void drawNumber(int number, int rowStart, int colStart, int colorList[LED_COUNT][3], bool showStrip=false, bool randomizeDark=false){
  int currentNumberPosition[NUMBER_HEIGHT][NUMBER_WIDTH];
  getNumberPosition(currentNumberPosition, number);
    for(int i = 0; i<NUMBER_HEIGHT; i++){
      int row[3];
      getNumberRow(row, currentNumberPosition, i);
      
      for(int j = 0; j< NUMBER_WIDTH; j++){
        if(row[j]==1){
          int pixel = coordsToPixel(rowStart+i, colStart+j);
          int currentColor[3] = {colorList[pixel][0],colorList[pixel][1],colorList[pixel][2]};
          if(randomizeDark && random(0,10)>7){
            shadeColor(currentColor, -40);  
          }
          strip.setPixelColor(pixel, 
            strip.Color(currentColor[0],currentColor[1],currentColor[2])
          );
        }
      }
    }
    if(showStrip){
      strip.show();  
    } 
}

void drawCurrentTime(int colorList[LED_COUNT][3], bool clockTick = true, bool randomizeDark = false){

  strip.clear();
  int timeDigits[4];
  getTimeDigits(timeDigits);
  // dibujo la hora
  for(int i = 0; i<4; i++){
    drawNumber(timeDigits[i], DIGIT_POSITIONS[i][0], DIGIT_POSITIONS[i][1], colorList, false,randomizeDark);
  }
  if(clockTick){
    drawNumber(10, DIGIT_POSITIONS[4][0], DIGIT_POSITIONS[4][1], colorList, false, randomizeDark);
  }
  strip.show();
}
