// common var
//========================
int leds[] = {6, 7, 8, 9, 10, 11, 12, 13};
#define NUMBER_OF_LEDS (sizeof(leds)/sizeof(int))
// pov var
//========================
#define DELAYMS 4
#define BITMAPLEN 27 // length bitmap
byte bitmap[] = {
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
0b11110011,
};
unsigned char pos = 0; // 現在のビットマップ中の位置
unsigned char i = 0;

// lasor is under constraction
//========================
#define FRAMES (sizeof(larson)/(sizeof(larson[0])))

void setup() {
  for (int led=0; led<NUMBER_OF_LEDS; led++) {
    pinMode(leds[led], OUTPUT);
  }
}
void loop(){
  // 1,lasor
  // 3,pov
  pov_avtokyo();
}
void pov_avtokyo(){
  for (int led=0; led<NUMBER_OF_LEDS; led++) {
    digitalWrite(leds[led], (bitmap[pos]>>led)&0b00000001);
  }
  if(pos++ == BITMAPLEN) pos = 0;
  delay(DELAYMS);
}
