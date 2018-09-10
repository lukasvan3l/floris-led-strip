#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NUM_LIGHTS 8
#define LIGHTS_PIN 6
#define BUTTON_PINK_PIN 9

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LIGHTS, LIGHTS_PIN, NEO_GRBW + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  pinMode(9, INPUT_PULLUP);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
//  colorWipe(strip.Color(255, 0, 0), 20); // Red
//  colorWipe(strip.Color(0, 255, 0), 20); // Green
//  colorWipe(strip.Color(0, 0, 255), 20); // Blue

//  theaterChase(strip.Color(127, 127, 127), 50); // White
//  theaterChase(strip.Color(127, 0, 0), 50); // Red
//  theaterChase(strip.Color(0, 0, 127), 50); // Blue

//  rainbow(20);
//  rainbowCycle(20);
//  theaterChaseRainbow(50);

//    strip.setPixelColor(0, strip.Color(255,0,0));
//    strip.setPixelColor(1, strip.Color(0,255,0));
//    strip.setPixelColor(2, strip.Color(0,0,255));
//    strip.setPixelColor(3, strip.Color(255,0,0));
//    strip.setPixelColor(4, strip.Color(0,255,0));
//    strip.setPixelColor(5, strip.Color(0,0,255));
//    strip.setPixelColor(6, strip.Color(255,0,0));
//    strip.setPixelColor(7, strip.Color(0,255,0));
//    strip.show();
    

//    police1fast(10);

  if (digitalRead(BUTTON_PINK_PIN) == LOW) {
    police1slow(10);
  }

//    police2(15, 200);

//    knightRider(5, 20);

}

void police2(int count, int duration) {
  uint32_t blue = strip.Color(0, 0, 255); 
  uint32_t red = strip.Color(255,0,0);
  uint32_t off = strip.Color(0,0,0);

  for (int j = 0; j < count; j++) {
    for (int i = 0; i < NUM_LIGHTS; i++) {
      if (i % 2 == 0) {
        strip.setPixelColor(i, blue);
      } else {
        strip.setPixelColor(i, off);
      }
    }
    strip.show();
    delay(duration);
    for (int i = 0; i < NUM_LIGHTS; i++) {
      if (i % 2 == 0) {
        strip.setPixelColor(i, off);
      } else {
        strip.setPixelColor(i, red);
      }
    }
    strip.show();
    delay(duration);
  }

  allOff();
}

void police1slow(int count) {
  uint32_t blue = strip.Color(0, 0, 255); 
  uint32_t red = strip.Color(255,0,0);
  int lightDuration = 300;
  int delayDuration = 75;

  for (int i = 0; i < count; i++) {
    police1Blink(0, red, lightDuration);
    delay(delayDuration);
    police1Blink((NUM_LIGHTS / 2), blue, lightDuration);
    delay(delayDuration);
  }

  allOff();
}

void police1fast(int count) {
  uint32_t blue = strip.Color(0, 0, 255); 
  uint32_t red = strip.Color(255,0,0);
  int lightDuration = 75;
  int delayDuration = 75;

  for (int i = 0; i < count; i++) {
    police1Blink(0, red, lightDuration);
    delay(delayDuration);
    police1Blink(0, red, lightDuration);
    delay(delayDuration*2);
    police1Blink((NUM_LIGHTS / 2), blue, lightDuration);
    delay(delayDuration);
    police1Blink((NUM_LIGHTS / 2), blue, lightDuration);
    delay(delayDuration*2);
  }

  allOff();
}

void police1Blink(int startLed, uint32_t color, int duration) {
  for (int i = startLed; i < startLed + (NUM_LIGHTS / 2); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
  delay(duration);
  for (int i = startLed; i < startLed + (NUM_LIGHTS / 2); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

void knightRider(int loops, int timer) {
    int count = 0;

    uint32_t low = strip.Color(0, 0, 0); 
    uint32_t high = strip.Color(255,0,0);

    // Flash Lights
    for(int i = 0; i < loops; i++){
        for (count=0;count<7;count++) {
            knightRiderDot(count, high);
            delay(timer);
            knightRiderDot(count+1, high);
            delay(timer);
            knightRiderDot(count, low);
            delay(timer*2);
        }
        for (count=7;count>=0;count--) {
            knightRiderDot(count, high);
            delay(timer);
            knightRiderDot(count-1, high);
            delay(timer);
            knightRiderDot(count, low);
            delay(timer*2);
        }
    }

    allOff();
}

void allOff() {
  for( int i = 0; i<NUM_LIGHTS; i++){
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }   
  strip.show();
}

// i = 0 - 7, for the pixels in KITT's ledbar, represented by 19 neopixels
void knightRiderDot(int i, uint32_t highorlow) {
  int ppk = NUM_LIGHTS / 7; // 19
  for (int j = ppk*i; j < (ppk*i+ppk); j++) {
    strip.setPixelColor(j, highorlow); 
  }
  strip.show();
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
