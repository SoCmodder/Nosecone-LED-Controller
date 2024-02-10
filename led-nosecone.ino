#include <Adafruit_NeoPixel.h>
#include "NeoPattern.h"

#define LED_PIN 28
#define NUM_LEDS 33
#define FADE_DELAY 10

void OnComplete();

//TUTORIAL: https://learn.adafruit.com/multi-tasking-the-arduino-part-3/put-it-all-together-dot-dot-dot
NeoPattern Strip1(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800, &OnComplete);

int selectedPattern = 0;

void setup() {
  Strip1.begin();
  Strip1.RainbowCycle(10);
  //Strip1.Scanner(Strip1.Color(0, 0, 255), 10);
}

void loop() {
  Strip1.Update();
}

void OnComplete() {
  switch (Strip1.ActivePattern) {
    case NeoPattern::RAINBOW_CYCLE:
      break;
    case NeoPattern::COLOR_WIPE:
      break;  
    case NeoPattern::THEATER_CHASE:
      break;   
  }
}

void switchPattern() {
  Strip1.Index = 0;
  Strip1.Color1 = Strip1.Color(0, 255, 255);
  switch (Strip1.ActivePattern) {
    case NeoPattern::NONE:
      Strip1.ActivePattern = NeoPattern::RAINBOW_CYCLE;
      Strip1.Interval = 50;
      Strip1.TotalSteps = 255;
      break;
    case NeoPattern::RAINBOW_CYCLE:
      Strip1.ActivePattern = NeoPattern::COLOR_WIPE;
      Strip1.Interval = 50;
      Strip1.TotalSteps = Strip1.numPixels();
      break;
    case NeoPattern::COLOR_WIPE:
      Strip1.ActivePattern = NeoPattern::THEATER_CHASE;
      Strip1.Interval = 50;
      Strip1.TotalSteps = Strip1.numPixels();
      break;  
    case NeoPattern::THEATER_CHASE:
      Strip1.ActivePattern = NeoPattern::BRIGHT;
      Strip1.ColorSet(Strip1.Color(255, 255, 255));
      break;
    case NeoPattern::BRIGHT:
      Strip1.ActivePattern = NeoPattern::HALF_BRIGHT;
      Strip1.ColorSet(Strip1.Color(127, 127, 127));
      break;
    case NeoPattern::HALF_BRIGHT:
      Strip1.ActivePattern = NeoPattern::SCANNER;
      Strip1.Interval = 10;
      Strip1.TotalSteps = Strip1.numPixels(); 
      Strip1.Color1 = Strip1.Color(255, 0, 0);
      break;  
    case NeoPattern::SCANNER:
      Strip1.ActivePattern = NeoPattern::NONE;
      Strip1.ColorSet(Strip1.Color(0, 0, 0));
      break;  
  }
}


