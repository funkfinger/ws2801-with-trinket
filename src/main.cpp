#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 1
#define DATA_PIN 0
#define CLOCK_PIN 1
#define BUTTON_PIN 2

CRGB leds[NUM_LEDS];

unsigned long previousMillis = 0;
const long interval = 200;
const int debounceTime = 100;
long buttonDownTimeLimit = 8000;
long currentDownTime = 0;
int colorIndex = 0;

CRGB colorArray[] = {CRGB::Green, CRGB::Red, CRGB::Purple, CRGB::BlanchedAlmond, CRGB::CadetBlue, CRGB::DarkGoldenrod};

bool debouncedButton()
{
  if (digitalRead(BUTTON_PIN) == HIGH)
  {
    currentDownTime = 0;
    return false;
  }
  if (currentDownTime > buttonDownTimeLimit)
    return true;
  currentDownTime += 1;
  return false;
}

void setup()
{
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  leds[0] = colorArray[colorIndex];
  FastLED.show();
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);
}

void loop()
{
  if (debouncedButton())
  {
    colorIndex = colorIndex > 5 ? 0 : colorIndex + 1;
  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    leds[0] = leds[0] ? CRGB::Black : colorArray[colorIndex];
    FastLED.show();
  }
}