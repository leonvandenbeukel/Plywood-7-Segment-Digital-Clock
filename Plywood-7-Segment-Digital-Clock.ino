/*

Indexes of LEDs (2 per segment):

    47 46        33 32            17 16        3  2
  48     45    34     31        18     15    4      1
  49     44    35     30   29   19     14    5      0
    57 56        43 42            27 26       13 12
  50     55    36     41   28   20     25    6     11
  51     54    37     40        21     24    7     10 
    52 53        38 39            22 23        8  9
    
*/

#include <FastLED.h>
#define NUM_LEDS 58
#define DATA_PIN 6 
CRGB LEDs[NUM_LEDS];

byte nrOfLEDsPerSegment = 2;
void displayNumber(byte, byte);
void displayDots();
bool startupRun = false;

void setup() {
  // Initialize LED strip
  FastLED.delay(3000);
  
  // Check if you're LED strip is a RGB or GRB version (third parameter)
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(LEDs, NUM_LEDS);
}

void loop() {

  if (!startupRun) {
    int dly = 50;
  
    for (byte j=0; j<4; j++) {
      for (byte i=0; i<11; i++) {
        displayNumber(i, j);
        delay(dly);
      }
    }
    startupRun = true;
  }

  displayDots();
  displayNumber(2,0);
  displayNumber(5,1);
  displayNumber(0,2);
  displayNumber(1,3);
  
return;
  


return;

 for (int i=0; i<NUM_LEDS; i++){
   // allOff();

    //byte index = i * 2;
    if (i>0) 
      LEDs[i-1] = CRGB::Black;  
    else 
      LEDs[NUM_LEDS -1] = CRGB::Black;  
    
    LEDs[i] = CRGB::Magenta;  
    FastLED.show();
    delay(5);
  }

return;

  for (int i=0; i<7; i++){
    allOff();

    byte index = i * 2;
    
    LEDs[index] = CRGB::Red;
    LEDs[index + 1] = CRGB::Red;
    FastLED.show();
    delay(300);
  } 

}

void displayNumber(byte number, byte segment) {

  // segment from left to right: 3, 2, 1, 0
  byte startindex = 0;
  switch (segment) {
    case 0:
      startindex = 0;
      break;
    case 1:
      startindex = 14;
      break;
    case 2:
      startindex = 30;
      break;
    case 3:
      startindex = 44;
      break;    
  }

/*

Indexes of LEDs (2 per segment):

    47 46        33 32            17 16        3  2
  48     45    34     31        18     15    4      1
  49     44    35     30   29   19     14    5      0
    57 56        43 42            27 26       13 12
  50     55    36     41   28   20     25    6     11
  51     54    37     40        21     24    7     10 
    52 53        38 39            22 23        8  9
    
*/

  int numbers[] = {
    0b00111111111111,  // 0
    0b00110000000011,  // 1
    0b11001111001111,  // 2
    0b11111100001111,  // 3
    0b11110000110011,  // 4
    0b11111100111100,  // 5
    0b11111111111100,  // 6
    0b00110000001111,  // 7
    0b11111111111111,  // 8
    0b11111100111111,  // 9
    0b00000000000000,  // 10 off       
  };

  for (byte i=0; i<14; i++){
    LEDs[i + startindex] = ((numbers[number] & 1 << i) == 1 << i) ? CRGB::Red : CRGB::Black;
  }

  FastLED.show();  
}

void allOff() {

  for (int i=0; i<NUM_LEDS; i++){
    LEDs[i] = CRGB::Black;
  }
  FastLED.show();
  
}

void allOn(CRGB color) {

  for (int i=0; i<NUM_LEDS; i++){
    LEDs[i] = color;
  }
  FastLED.show();
  
}

void displayDots() {
   LEDs[28] = CRGB::Red;
   LEDs[29] = CRGB::Red;    
   FastLED.show();
}
