#include <Adafruit_NeoPixel.h>
#include "NeoPattern.h"

// Returns the Red component of a 32-bit color
uint8_t NeoPattern::Red(uint32_t color) {
  return (color >> 16) & 0xFF;
}

// Returns the Green component of a 32-bit color
uint8_t NeoPattern::Green(uint32_t color) {
  return (color >> 8) & 0xFF;
}

// Returns the Blue component of a 32-bit color
uint8_t NeoPattern::Blue(uint32_t color) {
  return color & 0xFF;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t NeoPattern::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

// Update the Rainbow Cycle Pattern
void NeoPattern::RainbowCycleUpdate() {
  for (int i = 0; i < numPixels(); i++) {
    setPixelColor(i, Wheel(((i * 256 / numPixels()) + Index) & 255));
  }
  show();
  Increment();
}

// Update the pattern
void NeoPattern::Update() {
  if ((millis() - lastUpdate) > Interval) {  // time to update
    lastUpdate = millis();
    switch (ActivePattern) {
      case RAINBOW_CYCLE:
        RainbowCycleUpdate();
        break;
      case COLOR_WIPE:
        ColorWipeUpdate();
        break;
      case THEATER_CHASE:
        TheaterChaseUpdate();
        break;
      case SCANNER:
        ScannerUpdate();
        break; 
      default:
        break;
    }
  }
}

// Initialize for a RainbowCycle
void NeoPattern::RainbowCycle(uint8_t interval, Direction dir) {
  ActivePattern = RAINBOW_CYCLE;
  Interval = interval;
  TotalSteps = 255;
  Index = 0;
  direction = dir;
}

// Increment the Index and reset at the end
void NeoPattern::Increment() {
  if (direction == FORWARD) {
    Index++;
    if (Index >= TotalSteps) {
      Index = 0;
      if (OnComplete != NULL) {
        OnComplete();  // call the comlpetion callback
      }
    }
  } else  // Direction == REVERSE
  {
    --Index;
    if (Index <= 0) {
      Index = TotalSteps - 1;
      if (OnComplete != NULL) {
        OnComplete();  // call the comlpetion callback
      }
    }
  }
}

// Reverse direction of the pattern
void NeoPattern::Reverse() {
  if (direction == FORWARD) {
    direction = REVERSE;
    Index = TotalSteps - 1;
  } else {
    direction = FORWARD;
    Index = 0;
  }
}

// Initialize for a ColorWipe
void NeoPattern::ColorWipe(uint32_t color, uint8_t interval, Direction dir) {
  ActivePattern = COLOR_WIPE;
  Interval = interval;
  TotalSteps = numPixels();
  Color1 = color;
  Index = 0;
  direction = dir;
}

// Update the Color Wipe Pattern
void NeoPattern::ColorWipeUpdate() {
  setPixelColor(Index, Color1);
  show();
  Increment();
}

// Initialize for a Theater Chase
void NeoPattern::TheaterChase(uint32_t color1, uint32_t color2, uint8_t interval, Direction dir) {
  ActivePattern = THEATER_CHASE;
  Interval = interval;
  TotalSteps = numPixels();
  Color1 = color1;
  Color2 = color2;
  Index = 0;
  direction = dir;
}

// Update the Theater Chase Pattern
void NeoPattern::TheaterChaseUpdate() {
  for (int i = 0; i < numPixels(); i++) {
    if ((i + Index) % 3 == 0) {
      setPixelColor(i, Color1);
    } else {
      setPixelColor(i, Color2);
    }
  }
  show();
  Increment();
}

// Initialize for a SCANNNER
void NeoPattern::Scanner(uint32_t color1, uint8_t interval) {
  ActivePattern = SCANNER;
  Interval = interval;
  TotalSteps = (numPixels() - 1) * 2;
  Color1 = color1;
  Index = 0;
}

// Update the Scanner Pattern
void NeoPattern::ScannerUpdate() {
  for (int i = 0; i < numPixels(); i++) {
    if (i == Index)  // Scan Pixel to the right
    {
      setPixelColor(i, Color1);
    } else if (i == TotalSteps - Index)  // Scan Pixel to the left
    {
      setPixelColor(i, Color1);
    } else  // Fading tail
    {
      setPixelColor(i, DimColor(getPixelColor(i)));
    }
  }
  show();
  Increment();
}

// Return color, dimmed by 75% (used by scanner)
uint32_t NeoPattern::DimColor(uint32_t color) {
  uint32_t dimColor = Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
  return dimColor;
}

// Set all pixels to a color (synchronously)
void NeoPattern::ColorSet(uint32_t color) {
  for (int i = 0; i < numPixels(); i++) {
    setPixelColor(i, color);
  }
  show();
}
