#include <Adafruit_NeoPixel.h>
// https://github.com/adafruit/Adafruit_NeoPixel

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
// https://github.com/PaulStoffregen/Encoder

#include <ezButton.h>
// https://arduinogetstarted.com/tutorials/arduino-button-library


#define R_BUTTON_PIN 2
#define G_BUTTON_PIN 3
#define B_BUTTON_PIN 4

#define BUTTON_DEBOUNCE_TIME 2

#define LED_BRIGHTNESS 25
#define LED_PIN 11


Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, LED_PIN, NEO_GRB + NEO_KHZ800);

// Output
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;

uint32_t currentColour;

ezButton redButton(R_BUTTON_PIN);
ezButton greenButton(G_BUTTON_PIN);
ezButton blueButton(B_BUTTON_PIN);

void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(LED_BRIGHTNESS);
  strip.show(); // Turn all off

  // Init buttons
  redButton.setDebounceTime(BUTTON_DEBOUNCE_TIME);
  greenButton.setDebounceTime(BUTTON_DEBOUNCE_TIME);
  blueButton.setDebounceTime(BUTTON_DEBOUNCE_TIME);
}

void loop() {
  redButton.loop();
  greenButton.loop();
  blueButton.loop();


  // Check if buttons have been pushed
  if (redButton.isPressed()) {
    Serial.println("Red button pushed");
    if (r > 0) {
      // Turn r off
      r = 0;
    } else {
      // Turn r on
      r = 255;
    }
  }

  if (greenButton.isPressed()) {
    Serial.println("Green button pushed");
    if (g > 0) {
      // Turn g off
      g = 0;
    } else {
      // Turn g on
      g = 255;
    }
  }

  if (blueButton.isPressed()) {
    Serial.println("Blue button pushed");
    if (b > 0) {
      // Turn b off
      b = 0;
    } else {
      // Turn r on
      b = 255;
    }
  }

  uint32_t newColour = strip.Color(r, g, b);

  if (currentColour != newColour) {
    Serial.print("Changing colour to ");
    Serial.println(newColour);
    colorWipe(newColour);
    currentColour = newColour;
  }
}

// Fill the dots one after the other with a colour
void colorWipe(uint32_t c) {
  uint8_t wait = 5;
  for (uint8_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
