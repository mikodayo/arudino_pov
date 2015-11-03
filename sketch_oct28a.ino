#include <iostream>
#include <string>

// common var
//========================
int leds[] = {6, 7, 8, 9, 10, 11, 12, 13};
#define NUMBER_OF_LEDS (sizeof(leds)/sizeof(int))

// lasor 
//========================
// lasor action fine
byte bitmap_fine[] = {
0b10000000,
0b11000000,
0b11100000,
0b11110000,
0b11111000,
0b11111100,
0b11111110,
0b11111111,
0b10000000,
0b11000000,
0b11100000,
0b11110000,
0b11111000,
0b11111100,
0b11111110,
0b11111111
};

// lasor no
byte bitmap_no[] = {
0b10000000,
0b11000000,
0b11100000,
0b11110000,
0b11111000,
0b11111100,
0b11111110,
0b11111111,
0b11111110,
0b11111100,
0b11111000,
0b11110000,
0b11100000,
0b11000000,
0b10000000,
0b10000000,
0b10000000,
0b11000000,
0b11100000,
0b11110000,
0b11111000,
0b11111100,
0b11111110,
0b11111111
};

// lasor one
byte bitmap_one[] = {
0b10000000,
0b01000000,
0b00100000,
0b00010000,
0b00001000,
0b00000100,
0b00000010,
0b00000001
};
// pov var
//========================
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
//========================

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
  short int menu = 5;
  unsigned long currentMillis = 0;
  unsigned long previousMillis = 0;
  unsigned int interval = 0;
  // game
  int card = 1; // H/L
  
  switch (menu) {
    case 1:
      // action fine
      output_led(bitmap_fine, sizeof(bitmap_fine)/sizeof(byte), 40);
      //output_led(bitmap_yes, sizeof(bitmap_yes)/sizeof(byte), 40);
      //output_led(bitmap_no, sizeof(bitmap_no)/sizeof(byte), 40);
      break;
    case 2:
      break;
    case 3:
      output_led(bitmap_pov, sizeof(bitmap_pov)/sizeof(byte), 4);
      break;
    case 5:
      // game HL
      //-------------------------
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
    case 6:
      // game NotB
      //-------------------------
      led_intro();
      break;
      
    case 7:
      // game Simon says
      //-------------------------
      led_intro();
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
  delay(delay_time);
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
//-------- common
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

//-------- Intro
void led_intro(){
  byte bitmap_intro[] = {
0b10000001,
0b11000011,
0b11100111,
0b11111111,
0b10000001,
0b11000011,
0b11100111,
0b11111111
};
  for (int i=0; i < 8; i++) {
    output_led(bitmap_intro, sizeof(bitmap_intro)/sizeof(byte), 100);
  }
}
//-------- condition
// Yes
void led_yes(){
  byte bitmap_yes[] = {
0b10000001,
0b11000011,
0b11100111,
0b11111111
};
  for (int i=0; i < 4; i++) {
    output_led(bitmap_yes, sizeof(bitmap_yes)/sizeof(byte), 40);
  }
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
void game_notb(int arry_order[]){
  for(int i=0; i<sizeof(arry_order)/sizeof(int); i++){
  }
  for(int i=0; i<20; i++) {}

}

// 指定されている配列のみHIGHにして、あとはLOWにする　実装途中
void led_flash_by_order_arry(int array_order[]) {
  for(int i=0; i<sizeof(leds)/sizeof(int); i++){
    if (i+1 == array_order[i])
  }
  
  delay(40):
}


