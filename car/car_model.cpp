#include "car_model.h"

// How to initialize Adafruit Neopixel object:
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

#define NUM_LEDS 128
#define LED_OUTPUT_PIN 6

#define FULL_CAR_LIFE_POINTS 100
#define DEFAULT_DAMAGE 10

CarModel::CarModel() :
carId(UNINITIALIZED_CAR_ID),
isActive(false),
isFireLive(false),
team(CarMessage_TeamType_NO_TEAM),
ledStrip(NUM_LEDS, LED_OUTPUT_PIN, NEO_GRB + NEO_KHZ800),
lifePoints(FULL_CAR_LIFE_POINTS) {

}

CarModel::~CarModel() {
}

void CarModel::setIsActive(bool isActive) {
	// TODO: Something interesting goes here!
	this->isActive = isActive;
}

void CarModel::setAllLedColours(uint32_t rgb) {
	for (int i = 0; i < NUM_LEDS; i++) {
		this->ledStrip.setPixelColor(i, rgb);
	}
}

void CarModel::applyDamage() {
	if (this->lifePoints <= 0) {
		return;
	}

	this->lifePoints -= DEFAULT_DAMAGE;
	if (this->lifePoints <= 0) {
		this->lifePoints = 0;
		// TODO: Death of the car!
		//this->setIsActive(false);
	}
}

