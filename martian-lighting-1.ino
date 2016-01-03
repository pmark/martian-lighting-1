
#include <inttypes.h>
#include "application.h"
#include "neopixel.h"

bool lightSwitchOn = false;
bool blink = false;
bool blinkOff = false;
uint32_t lastBlinkTimestamp = 0;

// neopixel
#define PIXEL_PIN D6
#define PIXEL_COUNT 10
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setLightOn(const char *event, const char *data) {
	lightSwitchOn = true;
}

void setLightOff(const char *event, const char *data) {
	lightSwitchOn = false;
}

void setBlinkOn(const char *event, const char *data) {
	blink = true;
}

void setBlinkOff(const char *event, const char *data) {
	blink = false;
	blinkOff = false;
}

void rainbow(uint8_t wait);

void setup() {
	strip.begin();
	strip.show();
    Spark.subscribe("light", setLightOn);
    Spark.subscribe("nolight", setLightOff);
    Spark.subscribe("blink", setBlinkOn);
    Spark.subscribe("noblink", setBlinkOff);

    lightSwitchOn = false;
    // Serial.begin(9600);
}
 
void loop() {

	if (blink) {
		rainbow(20);
		// for(uint16_t i=0; i<strip.numPixels(); i++) {
		// 	strip.setPixelColor(i, strip.Color(0, 0, 255));
		// }
		// strip.show();
		// delay(100);
	}
	else {
		for(uint16_t i=0; i<strip.numPixels(); i++) {
			strip.setPixelColor(i, strip.Color(15, 0, 0));
		}
		strip.show();
		delay(100);
	}
}

// neopixel
void rainbow(uint8_t wait) {
	uint16_t i, j;

	for(j=0; j<256; j++) {
		// if (lightSwitchOn) {		
			float scale = blinkScale();
			for(i=0; i<strip.numPixels(); i++) {
				strip.setPixelColor(i, uint32_t(scale * Wheel((i+j) & 255)));
			}

			strip.show();
			delay(wait);
		// }
	}
}

float blinkScale() {
	float scale = (blinkOff ? 0.0 : 1.0);
	unsigned long now = millis();

	if (lastBlinkTimestamp == 0) {
		lastBlinkTimestamp = now;
	}

	if (blink) {
		if (now - lastBlinkTimestamp > 2000) {
			blinkOff = !blinkOff;
			lastBlinkTimestamp = now;
		}		
	}

	return scale;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	if(WheelPos < 85) {
		return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	} else if(WheelPos < 170) {
		WheelPos -= 85;
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	} else {
		WheelPos -= 170;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}

// end neopixel
