#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 1
#define DATA_PIN 0
#define CLOCK_PIN 1
#define BUTTON_PIN 2

CRGB leds[NUM_LEDS];

unsigned long previousMillis = 0;
const long interval = 1000;

void setup()
{
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  leds[0] = CRGB::Green;
  FastLED.show();
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    leds[0] = leds[0] ? CRGB::Black : CRGB::Green;
    FastLED.show();
  }
}