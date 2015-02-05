#ifndef CRASHANDBURN_CAR_CAR_MODEL_H_
#define CRASHANDBURN_CAR_CAR_MODEL_H_

#include <Adafruit_NeoPixel.h>
#include "car_to_server.pb.h"

#define UNINITIALIZED_CAR_ID -1


class CarModel {
public:
	CarModel();
	~CarModel();

	int32_t getCarId() const { return this->carId; }
	bool getIsActive() const { return this->isActive; }
	bool getIsFireLive() const { return this->isFireLive; }
	CarMessage_TeamType getTeam() const { return this->team; }
	uint32_t getLedColour() const { return this->ledStrip.getPixelColor(0); }

	void setIsActive(bool isActive);
	void setAllLedColours(uint32_t rgb);

	void applyDamage();

private:
	int32_t carId;
	bool isActive;
	bool isFireLive;
	CarMessage_TeamType team;
	Adafruit_NeoPixel ledStrip;

	float lifePoints; // 0 to 100 life, 0 means the car is dead

};

#endif // CRASHANDBURN_CAR_CAR_MODEL_H_
