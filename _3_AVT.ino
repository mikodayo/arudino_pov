#include <iostream>
#include <string>

// common var
// leds
int leds[] = {6, 7, 8, 9, 10, 11, 12, 13};
#define NUMBER_OF_LEDS (sizeof(leds)/sizeof(int))
#define MENU_1_LASOR 1
#define MENU_2_POV   2
#define MENU_3_NOTB  3
// menu
volatile unsigned int menu = 1;
// switch
int SWITCH_SOCKET = 2;
int ACTION_SWITCH_SOCKET = 3;
unsigned long led = 0;
// wait
unsigned long start = 0;
unsigned long now = 0;
unsigned long elapsed = 0;
// pov
unsigned char pos = 0;
unsigned char i = 0;
// binary
unsigned char pos_bin_start = 0;
unsigned char pos_bin = 0;
volatile unsigned int correct = 0;
// score
unsigned long correct_answer = 0;
unsigned long question = 0;
unsigned long score = 0;

// not begin
byte bitmap_bin_start[] =  {
0b00000001,
0b00000010,
0b00000011,
0b00000100,
0b00000111,
0b00000000,
0b00000111,
0b00000000,
0b00000111
};

// not b
byte error_binary_pos[] = {5,10,18,25,35,48,55,63,75,83,95,103,117,122,133,149,154,161,170,183,195,203,214,225,239,248,251};
byte error_binary[] = {
0b00000001,
0b00000010,
0b00000011,
0b11111111,
0b00000101,
0b00000110,
0b00000111,
0b00001000,
0b00001111,
0b00001010,
0b00001011,
0b00001100,
0b00001101,
0b00001110,
0b00001111,
0b00010000,
0b00110001,
0b00010010,
0b00010011,
0b00010100,
0b00010101,
0b00010110,
0b00010111,
0b10011000,
0b00011001,
0b00011010,
0b00011011,
0b00011100,
0b00011101,
0b00011110,
0b00011111,
0b00100000,
0b00100001,
0b00110011,
0b00100011,
0b00100100,
0b00100101,
0b00100110,
0b00100111,
0b00101000,
0b00101001,
0b00101010,
0b00101011,
0b00101100,
0b00101101,
0b00101110,
0b01101111,
0b00110000,
0b00110001,
0b00110010,
0b00110011,
0b00110100,
0b00110101,
0b00111110,
0b00110111,
0b00111000,
0b00111001,
0b00111010,
0b00111011,
0b00111100,
0b00111101,
0b10111110,
0b00111111,
0b01000000,
0b01000001,
0b01000010,
0b01000011,
0b01000100,
0b01000101,
0b01000110,
0b01000111,
0b01001000,
0b01001001,
0b01011011,
0b01001011,
0b01001100,
0b01001101,
0b01001110,
0b01001111,
0b01010000,
0b01010001,
0b01010111,
0b01010011,
0b01010100,
0b01010101,
0b01010110,
0b01010111,
0b01011000,
0b01011001,
0b01011010,
0b01011011,
0b01011100,
0b01011101,
0b01010110,
0b01011111,
0b01100000,
0b01100001,
0b01100010,
0b01100011,
0b01100100,
0b01100101,
0b11100100,
0b01100111,
0b01101000,
0b01101001,
0b01101010,
0b01101011,
0b01101100,
0b01101101,
0b01101110,
0b01101111,
0b01110000,
0b01110001,
0b01110010,
0b01110011,
0b01010100,
0b01110101,
0b01110110,
0b01110111,
0b01111000,
0b00011001,
0b01111010,
0b01111011,
0b01111100,
0b01111101,
0b01111110,
0b01111111,
0b10000000,
0b10000001,
0b10000010,
0b10000011,
0b11100110,
0b10000101,
0b10000110,
0b10000111,
0b10001000,
0b10001001,
0b10001010,
0b10001011,
0b10001100,
0b10001101,
0b10001110,
0b10001111,
0b10010000,
0b10010001,
0b10010010,
0b10010011,
0b00010100,
0b10010101,
0b10010110,
0b10010111,
0b10011000,
0b00010000,
0b10011010,
0b10011011,
0b10011100,
0b10011101,
0b10011110,
0b10011111,
0b10100100,
0b10100001,
0b10100010,
0b10100011,
0b10100100,
0b10100101,
0b10100110,
0b10100111,
0b10101000,
0b11111011,
0b10101010,
0b10101011,
0b10101100,
0b10101101,
0b10101110,
0b10101111,
0b10110000,
0b10110001,
0b10110010,
0b10110011,
0b10110100,
0b10110101,
0b10110111,
0b10110111,
0b10111000,
0b10111001,
0b10111010,
0b10111011,
0b10111100,
0b10111101,
0b10111110,
0b10111111,
0b11000000,
0b11000001,
0b11010010,
0b11000011,
0b11000100,
0b11000101,
0b11000110,
0b11000111,
0b11001000,
0b11001001,
0b11001011,
0b11001011,
0b11001100,
0b11001101,
0b11001110,
0b11001111,
0b11010000,
0b11010001,
0b11010010,
0b11010011,
0b11010100,
0b11011111,
0b11010110,
0b11010111,
0b11011000,
0b11011001,
0b11011010,
0b11011011,
0b11011100,
0b11011101,
0b11011110,
0b11011111,
0b11100001,
0b11100001,
0b11100010,
0b11100011,
0b11100100,
0b11100101,
0b11100110,
0b11100111,
0b11101000,
0b11101001,
0b11101010,
0b11101011,
0b11101100,
0b11101101,
0b11111110,
0b11101111,
0b11110000,
0b11110001,
0b11110010,
0b11110011,
0b11110100,
0b11110101,
0b11110110,
0b11110101,
0b11111000,
0b11111001,
0b11110010,
0b11111011,
0b11111100,
0b11111101,
0b11111110,
0b11111111
};
byte bitmap_bin[] =  {
0b00000001,
0b00000010,
0b00000011,
0b00000100,
0b00000101,
0b00000110,
0b00000111,
0b00001000,
0b00001001,
0b00001010,
0b00001011,
0b00001100,
0b00001101,
0b00001110,
0b00001111,
0b00010000,
0b00010001,
0b00010010,
0b00010011,
0b00010100,
0b00010101,
0b00010110,
0b00010111,
0b00011000,
0b00011001,
0b00011010,
0b00011011,
0b00011100,
0b00011101,
0b00011110,
0b00011111,
0b00100000,
0b00100001,
0b00100010,
0b00100011,
0b00100100,
0b00100101,
0b00100110,
0b00100111,
0b00101000,
0b00101001,
0b00101010,
0b00101011,
0b00101100,
0b00101101,
0b00101110,
0b00101111,
0b00110000,
0b00110001,
0b00110010,
0b00110011,
0b00110100,
0b00110101,
0b00110110,
0b00110111,
0b00111000,
0b00111001,
0b00111010,
0b00111011,
0b00111100,
0b00111101,
0b00111110,
0b00111111,
0b01000000,
0b01000001,
0b01000010,
0b01000011,
0b01000100,
0b01000101,
0b01000110,
0b01000111,
0b01001000,
0b01001001,
0b01001010,
0b01001011,
0b01001100,
0b01001101,
0b01001110,
0b01001111,
0b01010000,
0b01010001,
0b01010010,
0b01010011,
0b01010100,
0b01010101,
0b01010110,
0b01010111,
0b01011000,
0b01011001,
0b01011010,
0b01011011,
0b01011100,
0b01011101,
0b01011110,
0b01011111,
0b01100000,
0b01100001,
0b01100010,
0b01100011,
0b01100100,
0b01100101,
0b01100110,
0b01100111,
0b01101000,
0b01101001,
0b01101010,
0b01101011,
0b01101100,
0b01101101,
0b01101110,
0b01101111,
0b01110000,
0b01110001,
0b01110010,
0b01110011,
0b01110100,
0b01110101,
0b01110110,
0b01110111,
0b01111000,
0b01111001,
0b01111010,
0b01111011,
0b01111100,
0b01111101,
0b01111110,
0b01111111,
0b10000000,
0b10000001,
0b10000010,
0b10000011,
0b10000100,
0b10000101,
0b10000110,
0b10000111,
0b10001000,
0b10001001,
0b10001010,
0b10001011,
0b10001100,
0b10001101,
0b10001110,
0b10001111,
0b10010000,
0b10010001,
0b10010010,
0b10010011,
0b10010100,
0b10010101,
0b10010110,
0b10010111,
0b10011000,
0b10011001,
0b10011010,
0b10011011,
0b10011100,
0b10011101,
0b10011110,
0b10011111,
0b10100000,
0b10100001,
0b10100010,
0b10100011,
0b10100100,
0b10100101,
0b10100110,
0b10100111,
0b10101000,
0b10101001,
0b10101010,
0b10101011,
0b10101100,
0b10101101,
0b10101110,
0b10101111,
0b10110000,
0b10110001,
0b10110010,
0b10110011,
0b10110100,
0b10110101,
0b10110110,
0b10110111,
0b10111000,
0b10111001,
0b10111010,
0b10111011,
0b10111100,
0b10111101,
0b10111110,
0b10111111,
0b11000000,
0b11000001,
0b11000010,
0b11000011,
0b11000100,
0b11000101,
0b11000110,
0b11000111,
0b11001000,
0b11001001,
0b11001010,
0b11001011,
0b11001100,
0b11001101,
0b11001110,
0b11001111,
0b11010000,
0b11010001,
0b11010010,
0b11010011,
0b11010100,
0b11010101,
0b11010110,
0b11010111,
0b11011000,
0b11011001,
0b11011010,
0b11011011,
0b11011100,
0b11011101,
0b11011110,
0b11011111,
0b11100000,
0b11100001,
0b11100010,
0b11100011,
0b11100100,
0b11100101,
0b11100110,
0b11100111,
0b11101000,
0b11101001,
0b11101010,
0b11101011,
0b11101100,
0b11101101,
0b11101110,
0b11101111,
0b11110000,
0b11110001,
0b11110010,
0b11110011,
0b11110100,
0b11110101,
0b11110110,
0b11110111,
0b11111000,
0b11111001,
0b11111010,
0b11111011,
0b11111100,
0b11111101,
0b11111110,
0b11111111
};

void setup() {
  // for debug
  //Serial.begin(9600);
  // LED 6,7,8,9,10,11,12,13
  for (led=0; led<NUMBER_OF_LEDS; led++) {
    pinMode(leds[led], OUTPUT);
  }
  // switch
  pinMode(SWITCH_SOCKET,INPUT); // interruput button
  pinMode(ACTION_SWITCH_SOCKET,INPUT); // action button
  // interruption
  attachInterrupt(0, pressed, RISING);
  attachInterrupt(1, pressed_action, RISING);
}
void loop(){
  
  switch (menu) {
    case MENU_1_LASOR:// action fine
      // sum score
      if ( correct_answer != 0 && question != 0 ) {
        score = (double)correct_answer / (double)question  * 8;
      }
      for(;;){
        if(menu != 1) break;     
        led_off();
        led_lasor();
        // display score = current_answer/question * 8
        for(i=0; i<score; i++) {digitalWrite(leds[i], HIGH);}
        for(i=score;i<=NUMBER_OF_LEDS;i++){digitalWrite(leds[i], LOW);}
        myDelay(2000); 
      }      
      break;
    case MENU_2_POV: //pov
        led_intro();
        myDelay(100);
        for(;;) {
          if(menu != 2 ) break;
          pov();
        }
        break;
    case MENU_3_NOTB: // not binary
        led_intro();
        game_notb();
        pos_bin = 0;
        
        for(;;){
          if(menu != 3 ) break;  

          // errory binary
          for(i=0; i<sizeof(error_binary_pos)/sizeof(byte); i++){
            if ( pos_bin == error_binary_pos[i] ) {
              bitmap_bin[pos_bin] = error_binary[i];
              ++question;
            }
          }
          correct = 0;
          for (led=0; led<NUMBER_OF_LEDS; led++) {
            // display
            digitalWrite(leds[led], (bitmap_bin[pos_bin]>>led)&0b00000001);
          }
          myDelay(1000);            
          //if(pos_bin == 4){
          for(i=0; i<sizeof(error_binary_pos)/sizeof(byte); i++){
            if ( pos_bin == error_binary_pos[i] ) {
              if ( correct == 1){
                led_yes();led_off();
                ++correct_answer; 
              } else {
                led_no(); led_off();
              }
              break;
            }
          }
          if(pos_bin++ == sizeof(bitmap_bin)/sizeof(byte)) pos_bin = 0;     
        }
        break;
    default:
        menu = 1;
        break;
  }

}
// interrput when press the button
void pressed () {
  // change menu value
  if ( digitalRead( SWITCH_SOCKET) == 1 ) {
     menu = menu + 1;
    // TODO shold chattering! but can not use delay or millis()
    // while ( digitalRead ( SWITCH_SOCKET) == 1 )  {
    //   // wait for ms
    // } 
  }
}
void pressed_action(){
  if ( digitalRead( ACTION_SWITCH_SOCKET) == 1 ) {
     correct = 1;
  }
}

// !!notice!! mydelay can not user inside interrput.
void myDelay(unsigned long ms) {              // ms: duration
  // start: timestamp
  start = millis();           
  for (;;) {
    // now: timestamp
    now = millis();
    // elapsed: duration
    elapsed = now - start;
    if (elapsed >= ms)
      return;
  }
}

// led
//-----------------------------
//----------- common
// all off
void led_off() {
  for(i=0; i<8; i++) {digitalWrite(leds[i],LOW);};
  myDelay(400);
}
// 指定されている配列のみHIGHにして、あとはLOWにする
void led_flash_by_order_arry(int *array_order, int size) {
  for(led=0; led<sizeof(leds)/sizeof(int); led++){
    digitalWrite(leds[led],LOW);
  }
  for(i=0; i<size; i++){
    digitalWrite(leds[array_order[i]],HIGH);
  }
  myDelay(100);
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
  led_flash_by_order_arry(array_binary_1, sizeof(array_binary_1)/sizeof(int));
  led_flash_by_order_arry(array_binary_2, sizeof(array_binary_2)/sizeof(int));
  led_flash_by_order_arry(array_binary_3, sizeof(array_binary_3)/sizeof(int));
  led_flash_by_order_arry(array_binary_4, sizeof(array_binary_4)/sizeof(int));
  led_flash_by_order_arry(array_binary_5, sizeof(array_binary_5)/sizeof(int));
  led_flash_by_order_arry(array_binary_6, sizeof(array_binary_6)/sizeof(int));
  led_flash_by_order_arry(array_binary_7, sizeof(array_binary_7)/sizeof(int));
  led_flash_by_order_arry(array_binary_8, sizeof(array_binary_8)/sizeof(int));
}

//-------- condition
// Yes
void led_yes(){
  int array_binary_1[] = {0,7};// 0b10000001
  int array_binary_2[] = {0,1,6,7};//0b11000011
  int array_binary_3[] = {0,1,2,5,6,7};  //0b11100111
  int array_binary_4[] = {0,1,2,3,4,5,6,7};//0b11111111
  led_flash_by_order_arry(array_binary_1, sizeof(array_binary_1)/sizeof(int));
  led_flash_by_order_arry(array_binary_2, sizeof(array_binary_2)/sizeof(int));
  led_flash_by_order_arry(array_binary_3, sizeof(array_binary_3)/sizeof(int));
  led_flash_by_order_arry(array_binary_4, sizeof(array_binary_4)/sizeof(int));
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

  led_flash_by_order_arry(array_binary_1, sizeof(array_binary_1)/sizeof(int));
  led_flash_by_order_arry(array_binary_2, sizeof(array_binary_2)/sizeof(int));
  led_flash_by_order_arry(array_binary_3, sizeof(array_binary_3)/sizeof(int));
  led_flash_by_order_arry(array_binary_4, sizeof(array_binary_4)/sizeof(int));
  led_flash_by_order_arry(array_binary_5, sizeof(array_binary_5)/sizeof(int));
  led_flash_by_order_arry(array_binary_6, sizeof(array_binary_6)/sizeof(int));
  led_flash_by_order_arry(array_binary_7, sizeof(array_binary_7)/sizeof(int));
  led_flash_by_order_arry(array_binary_8, sizeof(array_binary_8)/sizeof(int));
  led_flash_by_order_arry(array_binary_9, sizeof(array_binary_9)/sizeof(int));
  led_flash_by_order_arry(array_binary_10, sizeof(array_binary_10)/sizeof(int));
  led_flash_by_order_arry(array_binary_11, sizeof(array_binary_11)/sizeof(int));
  led_flash_by_order_arry(array_binary_12, sizeof(array_binary_12)/sizeof(int));
  led_flash_by_order_arry(array_binary_13, sizeof(array_binary_13)/sizeof(int));
  led_flash_by_order_arry(array_binary_14, sizeof(array_binary_14)/sizeof(int));
  led_flash_by_order_arry(array_binary_15, sizeof(array_binary_15)/sizeof(int));
  led_flash_by_order_arry(array_binary_16, sizeof(array_binary_16)/sizeof(int));
  led_flash_by_order_arry(array_binary_17, sizeof(array_binary_17)/sizeof(int));
  led_flash_by_order_arry(array_binary_18, sizeof(array_binary_18)/sizeof(int));
  led_flash_by_order_arry(array_binary_19, sizeof(array_binary_19)/sizeof(int));
  led_flash_by_order_arry(array_binary_20, sizeof(array_binary_20)/sizeof(int));
  led_flash_by_order_arry(array_binary_21, sizeof(array_binary_21)/sizeof(int));
  led_flash_by_order_arry(array_binary_22, sizeof(array_binary_22)/sizeof(int));
}

//-------- game
void pov(){
  // pov
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
  for (led=0; led<NUMBER_OF_LEDS; led++) {
    digitalWrite(leds[led], (bitmap_pov[pos]>>led)&0b00000001);
  }
  if(pos++ == sizeof(bitmap_pov)/sizeof(byte)) pos = 0;
  myDelay(5);
}
// Not B begining
void game_notb(){
  pos_bin_start = 0;
  for(i=0; i < sizeof(bitmap_bin_start)/sizeof(byte); i++) {
    for(led=0; led<NUMBER_OF_LEDS; led++){
      digitalWrite(leds[led], (bitmap_bin_start[pos_bin_start]>>led)&0b00000001);
    }
    if(pos_bin_start++ == sizeof(bitmap_bin_start)/sizeof(byte)) pos_bin_start = 0;
    myDelay(1000);
  }
  led_no();
  led_off();
}

void notb_wrong_led(){
  // wrong led pattern
  digitalWrite(leds[led], (0b00000001>>led)&0b00000001);
  start = millis();           
  myDelay(1000);
  if (correct == 1) {
    led_yes();
    led_off();
  } else {
    led_no();
    led_off();
  }  
}
