/*
  
 Leon van den Beukel - 2019 

 Licence: Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0) (https://creativecommons.org/licenses/by-nc-sa/4.0/)
    
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <time.h>
#include <FastLED.h>
#include <EEPROM.h>

const char *WIFI_NETWORK_NAME = "***";              // Change to your wifi network name
const char *WIFI_PASSWORD = "***";                  // Change to your wifi password
float timeZone = 1.0;                               // Change this value to your local timezone (in my case +1 for Amsterdam)
const int DAY_LIGHT_OFFSET_SECONDS = 3600;          // Daylight saving

const char *TIME_SERVER = "pool.ntp.org";
const int EPOCH_1_1_2019 = 1546300800;
time_t now;

#define NUM_LEDS 58
#define DATA_PIN 6 
CRGB LEDs[NUM_LEDS];

byte nrOfLEDsPerSegment = 2;
void displayNumber(byte, byte);
void displayDots();

#define BTN_PIN D8

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )
CRGB colors[] = {CRGB::Red, CRGB::RoyalBlue, CRGB::Green, CRGB::Yellow, CRGB::Magenta, CRGB::White, CRGB::Blue};
byte colorSize = arr_len(colors);
byte colorIndex = 0;
CRGB color = colors[colorIndex];

void setup() { 

  pinMode(BTN_PIN, INPUT);

  // Initialize LED strip
  FastLED.delay(2000);
  
  // Check if you're LED strip is a RGB or GRB version (third parameter)
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(LEDs, NUM_LEDS);

  Serial.begin(115200);          
  
  WiFi.begin(WIFI_NETWORK_NAME, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  configTime(timeZone, DAY_LIGHT_OFFSET_SECONDS, TIME_SERVER);

  while (now < EPOCH_1_1_2019)
  {
    now = time(nullptr);
    delay(500);
    Serial.print("*");
  }

  // If color is stored previously, than restore
  EEPROM.begin(1);
  colorIndex = EEPROM.read(0);
  if (colorIndex >= 0) {
    color = colors[colorIndex];
    Serial.print("Previous color found: ");
    Serial.println(colorIndex);
  } else {
    Serial.print("Previous color not found: ");
    Serial.println(colorIndex);
  }
}

void loop() {

  int buttonState = digitalRead(BTN_PIN);
  if (buttonState == HIGH) {
    Serial.println("Button Pushed");
    colorIndex += 1;
    if (colorIndex >= colorSize)
      colorIndex = 0;
    
    color = colors[colorIndex];
    
    EEPROM.write(0, colorIndex); 
    EEPROM.end();
    Serial.print("Color index stored: ");
    Serial.println(colorIndex);  
  }

  struct tm *timeinfo;
  time(&now);
  timeinfo = localtime(&now);

  int hour = timeinfo->tm_hour;
  int mins = timeinfo->tm_min;

  byte h1 = hour / 10;
  byte h2 = hour % 10;
  byte m1 = mins / 10;
  byte m2 = mins % 10;

  displayDots();
  
  if (h1 > 0)
    displayNumber(h1,3);
    
  displayNumber(h2,2);
  displayNumber(m1,1);
  displayNumber(m2,0);

  delay(150);
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
    LEDs[i + startindex] = ((numbers[number] & 1 << i) == 1 << i) ? color : CRGB::Black;
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
   LEDs[28] = color;
   LEDs[29] = color;    
   FastLED.show();
}
