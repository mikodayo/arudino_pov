#include <iostream>
#include <string>

// common var
//========================
int leds[] = {6, 7, 8, 9, 10, 11, 12, 13};
#define NUMBER_OF_LEDS (sizeof(leds)/sizeof(int))


unsigned char pos = 0; // 現在のビットマップ中の位置
unsigned char i = 0;

void setup() {
  // debug start
  Serial.begin(9600);
  // debug end
  for (int led=0; led<NUMBER_OF_LEDS; led++) {
    pinMode(leds[led], OUTPUT);
  }
}
void loop(){

  //--------------------var
  // common
  short int menu = 6;
  unsigned long currentMillis = 0;
  unsigned long previousMillis = 0;
  unsigned int interval = 0;
  // game
  int card = 1; // H/L
  
  switch (menu) {
    case 1:// action fine
      led_fine();
      break;
    case 2:
      break;
    case 3:// pov
      pov();
      break;
    case 5:// game HL
      led_intro();
      game_hl();            
      while(1){
        // 最初のカード      
        card = rand()%8+1;
        // スイッチが押された時breakしてここにくる。
        // cardと入力したH/Lが合っているかここでチェック
        currentMillis = millis();
        previousMillis = 0;
        while(1) {
          if ( currentMillis - previousMillis >= 5000 ) {
            previousMillis = currentMillis;             
            led_flash_by_order(card); 
            
          } else {
            // 5秒待っても入力がなかったら次のカードを表示
            break;
          }
        }
      }
      break;
    case 6:// game NotB
      led_intro();
      game_notb();
      notb();
      break;
      
    case 7:// game Simon says
      led_intro();
      game_symon();
      symon();
      break;
      
    default:
      break;
  }

}

// basic led function
void output_led(byte bitmap[], int bitmap_length, int delay_time){
  for (int led=0; led<NUMBER_OF_LEDS; led++) {
    digitalWrite(leds[led], (bitmap[pos]>>led)&0b00000001);
  }
  if(pos++ == bitmap_length) pos = 0;
  delay(40);
}

// output one led
void output_one_led(int led_position){
  for (int led=0; led<NUMBER_OF_LEDS; led++) {
    if( led==led_position ) {
       digitalWrite(leds[led],HIGH);
    } else {
       digitalWrite(leds[led],LOW);
    }
  } 
  delay(1000);
}


// led
//-----------------------------
//----------- common
// 指定した本数のLEDを左から一度にFLASHする 連続点灯必須
void led_flash_by_order(int order) {
  for(int i=0; i<order; i++) {digitalWrite(leds[i], HIGH);}
  for(int j=order;j<=8;j++){digitalWrite(leds[j], LOW);}
  delay(40);
}
// all off
void led_off() {
  for(int i=0; i<8; i++) {digitalWrite(leds[i],LOW);};
  delay(40);
}
// 指定されている配列のみHIGHにして、あとはLOWにする
void led_flash_by_order_arry(int *array_order, int size) {
  for(int led=0; led<sizeof(leds)/sizeof(int); led++){
    digitalWrite(leds[led],LOW);
  }
  for(int i=0; i<size; i++){
    digitalWrite(leds[array_order[i]],HIGH);
  }
  delay(40);
}
//-------- Intro
void led_intro(){
led_yes();
led_yes();
}
// lasor
void led_lasor(){
  int array_binary_1[] = {0}; //0b10000000
  int array_binary_2[] = {0,1};//0b11000000
  int array_binary_3[] = {0,1,2};//0b11000000
  int array_binary_4[] = {0,1,2,3};//0b11100000
  int array_binary_5[] = {0,1,2,3,4};//0b11110000
  int array_binary_6[] = {0,1,2,3,4,5};//0b11111000
  int array_binary_7[] = {0,1,2,3,4,5,6};//0b11111000
  int array_binary_8[] = {0,1,2,3,4,5,6,7};//0b11111000
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_1, sizeof(array_binary_1)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_2, sizeof(array_binary_2)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_3, sizeof(array_binary_3)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_4, sizeof(array_binary_4)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_5, sizeof(array_binary_5)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_6, sizeof(array_binary_6)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_7, sizeof(array_binary_7)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_8, sizeof(array_binary_8)/sizeof(int));}
}
// fine
void led_fine(){
  led_lasor();
  led_lasor();  
}


//-------- condition
// Yes
void led_yes(){
  int array_binary_1[] = {0,7};// 0b10000001
  int array_binary_2[] = {0,1,6,7};//0b11000011
  int array_binary_3[] = {0,1,2,5,6,7};  //0b11100111
  int array_binary_4[] = {0,1,2,3,4,5,6,7};//0b11111111
  for(int i=0; i<3; i++){led_flash_by_order_arry(array_binary_1, sizeof(array_binary_1)/sizeof(int));}
  for(int i=0; i<3; i++){led_flash_by_order_arry(array_binary_2, sizeof(array_binary_2)/sizeof(int));}
  for(int i=0; i<3; i++){led_flash_by_order_arry(array_binary_3, sizeof(array_binary_3)/sizeof(int));}
  for(int i=0; i<3; i++){led_flash_by_order_arry(array_binary_4, sizeof(array_binary_4)/sizeof(int));}
}

void led_no(){
  int array_binary_1[] = {0}; //0b10000000
  int array_binary_2[] = {0,1};//0b11000000
  int array_binary_3[] = {0,1,2};//0b11000000
  int array_binary_4[] = {0,1,2,3};//0b11100000
  int array_binary_5[] = {0,1,2,3,4};//0b11110000
  int array_binary_6[] = {0,1,2,3,4,5};//0b11111000
  int array_binary_7[] = {0,1,2,3,4,5,6};//0b11111000
  int array_binary_8[] = {0,1,2,3,4,5,6,7};//0b11111000
  int array_binary_9[] = {0,1,2,3,4,5,6};//0b11111000
  int array_binary_10[] = {0,1,2,3,4,5};//0b11111000
  int array_binary_11[] = {0,1,2,3,4};//0b11110000
  int array_binary_12[] = {0,1,2,3};//0b11100000
  int array_binary_13[] = {0,1,2};//0b11000000
  int array_binary_14[] = {0,1};//0b11000000
  int array_binary_15[] = {0}; //0b10000000
  int array_binary_16[] = {0,1};//0b11000000
  int array_binary_17[] = {0,1,2};//0b11000000
  int array_binary_18[] = {0,1,2,3};//0b11100000
  int array_binary_19[] = {0,1,2,3,4};//0b11110000
  int array_binary_20[] = {0,1,2,3,4,5};//0b11111000
  int array_binary_21[] = {0,1,2,3,4,5,6};//0b11111000
  int array_binary_22[] = {0,1,2,3,4,5,6,7};//0b11111000

  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_1, sizeof(array_binary_1)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_2, sizeof(array_binary_2)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_3, sizeof(array_binary_3)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_4, sizeof(array_binary_4)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_5, sizeof(array_binary_5)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_6, sizeof(array_binary_6)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_7, sizeof(array_binary_7)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_8, sizeof(array_binary_8)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_9, sizeof(array_binary_9)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_10, sizeof(array_binary_10)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_11, sizeof(array_binary_11)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_12, sizeof(array_binary_12)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_13, sizeof(array_binary_13)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_14, sizeof(array_binary_14)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_15, sizeof(array_binary_15)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_16, sizeof(array_binary_16)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_17, sizeof(array_binary_17)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_18, sizeof(array_binary_18)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_19, sizeof(array_binary_19)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_20, sizeof(array_binary_20)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_21, sizeof(array_binary_21)/sizeof(int));}
  for(int i=0; i<2; i++){led_flash_by_order_arry(array_binary_22, sizeof(array_binary_22)/sizeof(int));}
}
//-------- pov
// pov var
//========================
void pov(){
  byte bitmap_pov[] = {
0b11111100,
0b00100010,
0b00100001,
0b00100010,
0b11111100,
0b00000000,
0b00111111,
0b01000000,
0b10000000,
0b01000000,
0b00111111,
0b00000000,
0b00000001,
0b00000001,
0b11111111,
0b00000001,
0b00000001,
0b00000000,
0b11111111,
0b11111111,
0b00000000,
0b00000000,
0b11011111,
0b11011111,
0b11010011,
0b11110011,
0b11110011
};
  output_led(bitmap_pov, sizeof(bitmap_pov)/sizeof(byte), 4);
}

//-------- game
// HL begining
void game_hl(){
  for(int i=0; i<2; i++ ) {
    // 点滅間隔をforで調整
    for(int j=0; j<20; j++ ) {led_flash_by_order(1);}
    for(int j=0; j<20; j++) {led_flash_by_order(8);}
  }
  for(int i=0; i<30; i++){led_off();}
}
// Not B begining
void game_notb(){
  // {0,1,2,3,4,5,6,7}
  int array_binary_1[] = {0};
  int array_binary_2[] = {1};
  int array_binary_3[] = {0,1};  
  int array_binary_4[] = {2};
  int array_binary_5[] = {0,2}; 
  int array_binary_6[] = {2}; // wrong binarycode correct is {1,2}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_1, sizeof(array_binary_1)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_2, sizeof(array_binary_2)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_3, sizeof(array_binary_3)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_4, sizeof(array_binary_4)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_5, sizeof(array_binary_5)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_6, sizeof(array_binary_6)/sizeof(int));}
  
  for(int i=0; i<30; i++){led_off();}
  led_no();
  for(int i=0; i<30; i++){led_off();}
  
}

// GAME
// 途中に間違ったbinaryを混ぜてwait to push the button.
// 何秒か待つがもし入らなかったら、NOを表示して先頭に戻る。
// 255までいけたらWINのPOV
//---------------------------
void notb() {
  int array_binary_1[] = {0};
  int array_binary_2[] = {1};
  int array_binary_3[] = {0,1};  
  int array_binary_4[] = {2};
  int array_binary_5[] = {0,2}; 
  int array_binary_6[] = {1,2};
  int array_binary_7[] = {0,1,2};
  int array_binary_8[] = {3};
  int array_binary_9[] = {0,3};
  int array_binary_10[] = {1,3};
  int array_binary_11[] = {0,1,3};
  int array_binary_12[] = {2,3};
  int array_binary_13[] = {0,2,3};
  int array_binary_14[] = {1,2,3};
  int array_binary_15[] = {0,1,2,3};
  int array_binary_16[] = {4};
  int array_binary_17[] = {0,4};
  int array_binary_18[] = {1,4};

  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_1, sizeof(array_binary_1)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_2, sizeof(array_binary_2)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_3, sizeof(array_binary_3)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_4, sizeof(array_binary_4)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_5, sizeof(array_binary_5)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_6, sizeof(array_binary_6)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_7, sizeof(array_binary_7)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_8, sizeof(array_binary_8)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_9, sizeof(array_binary_9)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_10, sizeof(array_binary_10)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_11, sizeof(array_binary_11)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_12, sizeof(array_binary_12)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_13, sizeof(array_binary_13)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_14, sizeof(array_binary_14)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_15, sizeof(array_binary_15)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_16, sizeof(array_binary_16)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_17, sizeof(array_binary_17)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_18, sizeof(array_binary_18)/sizeof(int));}
  
}
void symon() {
  int array_binary_1[] = {0};
  int array_binary_2[] = {1};
  int array_binary_3[] = {0,1};  
  int array_binary_4[] = {2};
  int array_binary_5[] = {0,2}; 
  int array_binary_6[] = {1,2};
  int array_binary_7[] = {0,1,2};
  int array_binary_8[] = {3};
  int array_binary_9[] = {0,3};
  int array_binary_10[] = {1,3};
  int array_binary_11[] = {0,1,3};
  int array_binary_12[] = {2,3};
  int array_binary_13[] = {0,2,3};
  int array_binary_14[] = {1,2,3};
  int array_binary_15[] = {0,1,2,3};
  int array_binary_16[] = {4};
  int array_binary_17[] = {0,4};
  int array_binary_18[] = {1,4};

  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_1, sizeof(array_binary_1)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_2, sizeof(array_binary_2)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_3, sizeof(array_binary_3)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_4, sizeof(array_binary_4)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_5, sizeof(array_binary_5)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_6, sizeof(array_binary_6)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_7, sizeof(array_binary_7)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_8, sizeof(array_binary_8)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_9, sizeof(array_binary_9)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_10, sizeof(array_binary_10)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_11, sizeof(array_binary_11)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_12, sizeof(array_binary_12)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_13, sizeof(array_binary_13)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_14, sizeof(array_binary_14)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_15, sizeof(array_binary_15)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_16, sizeof(array_binary_16)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_17, sizeof(array_binary_17)/sizeof(int));}
  for(int i=0; i<20; i++){led_flash_by_order_arry(array_binary_18, sizeof(array_binary_18)/sizeof(int));}
  
}
