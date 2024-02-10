#ifndef NEO_PATTERN_H
#define NEO_PATTERN_H

// NeoPattern Class - derived from the Adafruit_NeoPixel class
class NeoPattern : public Adafruit_NeoPixel {
public:
  enum Pattern { NONE, RAINBOW_CYCLE, COLOR_WIPE, THEATER_CHASE, SCANNER, BRIGHT, HALF_BRIGHT };
  enum Direction { FORWARD, REVERSE };
  // Member Variables:
  Pattern ActivePattern;  // which pattern is running
  Direction direction;    // direction to run the pattern
  unsigned long Interval;    // milliseconds between updates
  unsigned long lastUpdate;  // last update of position

  uint32_t Color1, Color2;  // What colors are in use
  uint16_t TotalSteps;      // total number of steps in the pattern
  uint16_t Index;           // current step within the pattern

  uint8_t Red(uint32_t color);
  uint8_t Green(uint32_t color);
  uint8_t Blue(uint32_t color);
  void Update();
  void RainbowCycle(uint8_t interval, Direction dir = FORWARD);
  void RainbowCycleUpdate();
  void Increment();
  uint32_t Wheel(byte WheelPos);
  void Reverse();
  void ColorWipe(uint32_t color, uint8_t interval, Direction dir = FORWARD);
  void ColorWipeUpdate();
  void TheaterChase(uint32_t color1, uint32_t color2, uint8_t interval, Direction dir = FORWARD);
  void TheaterChaseUpdate();
  uint32_t DimColor(uint32_t color);
  void ColorSet(uint32_t color);
  void Scanner(uint32_t color1, uint8_t interval);
  void ScannerUpdate();
  void (*OnComplete)();  // Callback on completion of pattern

  // Constructor - calls base-class constructor to initialize strip
  NeoPattern(uint16_t pixels, uint8_t pin, uint8_t type, void (*callback)()) : Adafruit_NeoPixel(pixels, pin, type) {
    OnComplete = callback;
  }
};

#endif