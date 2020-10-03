#include <Adafruit_NeoPixel.h>
// https://github.com/adafruit/Adafruit_NeoPixel

#include <SimpleRotary.h>
// https://github.com/mprograms/SimpleRotary


#define R_BUTTON_PIN 2
#define G_BUTTON_PIN 3
#define B_BUTTON_PIN 4

#define R_DT_PIN 5
#define G_DT_PIN 6
#define B_DT_PIN 7

#define R_CLK_PIN 8
#define G_CLK_PIN 9
#define B_CLK_PIN 10


#define LED_BRIGHTNESS 50
#define LED_PIN 11
#define LED_DELAY 10

#define ROTATE_JUMP 25


Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, LED_PIN, NEO_GRB + NEO_KHZ800);

// Output
int16_t r = 0;
int16_t g = 0;
int16_t b = 0;

uint32_t currentColour;

SimpleRotary redRotary(R_CLK_PIN, R_DT_PIN, R_BUTTON_PIN);
SimpleRotary greenRotary(G_CLK_PIN, G_DT_PIN, G_BUTTON_PIN);
SimpleRotary blueRotary(B_CLK_PIN, B_DT_PIN, B_BUTTON_PIN);

void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(LED_BRIGHTNESS);
  strip.show(); // Turn all off
}

void loop() {
  // Check for rotation
  byte redDirection = redRotary.rotate();

  if (redDirection == 1) {
    r += ROTATE_JUMP;
  } else if (redDirection == 2) {
    r -= ROTATE_JUMP;
  }

  byte greenDirection = greenRotary.rotate();

  if (greenDirection == 1) {
    g += ROTATE_JUMP;
  } else if (greenDirection == 2) {
    g -= ROTATE_JUMP;
  }

  byte blueDirection = blueRotary.rotate();

  if (blueDirection == 1) {
    b += ROTATE_JUMP;
  } else if (blueDirection == 2) {
    b -= ROTATE_JUMP;
  }


  // Check if buttons have been pushed
  if (redRotary.push() == 1) {
    if (r > 10) {
      // Turn r off
      r = 0;
    } else {
      // Turn r on
      r = 255;
    }
  }

  if (greenRotary.push() == 1) {
    if (g > 10) {
      // Turn g off
      g = 0;
    } else {
      // Turn g on
      g = 255;
    }
  }

  if (blueRotary.push() == 1) {
    if (b > 10) {
      // Turn b off
      b = 0;
    } else {
      // Turn r on
      b = 255;
    }
  }


  // Validate our colours
  if (r > 255) {
    r = 255;
  } else if (r < 0) {
    r = 0;
  }

  if (g > 255) {
    g = 255;
  } else if (g < 0) {
    g = 0;
  }

  if (b > 255) {
    b = 255;
  } else if (b < 0) {
    b = 0;
  }

  uint32_t newColour = strip.Color(r, g, b);

  if (currentColour != newColour) {
    colorWipe(newColour);
    currentColour = newColour;
  }
}

// Fill the dots one after the other with a colour
void colorWipe(uint32_t c) {
  for (uint8_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(LED_DELAY);
  }
}
