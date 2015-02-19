
#include "car.h"
#include "common.h"
#include "car_model.h"
#include "pb_arduino_decode.h"
#include "pb_arduino_encode.h"
#include "server_to_car.pb.h"
#include "car_to_server.pb.h"

// Protobuf output stream and message objects
pb_ostream_t pbOutStream;
// Protobuf input stream and message objects
pb_istream_t pbInStream;

// Protobuf message objects for incoming data
ServerMessage incomingMsg = ServerMessage_init_default;

// Object for maintaining car state information
CarModel carModel;

Stream* serialStream = &Serial;

void setup() {
	// Setup the output and input serial streams and callbacks
	Serial.begin(115200);
	pb_ostream_from_stream(*serialStream, pbOutStream);
	pb_istream_from_stream(*serialStream, pbInStream);
}

bool sendInfoMsg() {
	CarMessage outgoingMsg = CarMessage_init_default;

	outgoingMsg.type = CarMessage_MessageType_CAR_STATUS_INFO;
	outgoingMsg.has_carId = true;
	outgoingMsg.has_isActiveStatus = true;
	outgoingMsg.has_isFireLiveStatus = true;
	outgoingMsg.has_ledColour = true;

	// We assume that the following variables have been initialized to the correct state
	outgoingMsg.carId = carModel.getCarId();
	outgoingMsg.isActiveStatus = carModel.getIsActive();
	outgoingMsg.isFireLiveStatus = carModel.getIsFireLive();
	outgoingMsg.ledColour = carModel.getLedColour();

	return pb_encode(&pbOutStream, CarMessage_fields, &outgoingMsg);
}

bool sendFireShotMsg(const FireType& fireType) {
	CarMessage outgoingMsg = CarMessage_init_default;
	outgoingMsg.type = CarMessage_MessageType_FIRE_SHOT_EVENT;

	outgoingMsg.has_fireType = true;
	outgoingMsg.fireType = fireType;

	return pb_encode(&pbOutStream, CarMessage_fields, &outgoingMsg);
}

void setLedColour(const ServerMessage& ledMsg) {
	if (!ledMsg.has_ledColour ||
		ledMsg.type != ServerMessage_MessageType_SET_LED_COLOUR_CMD) {

		assert(false);
		return;
	}

	carModel.setAllLedColours(ledMsg.ledColour);
}

void setIsActive(const ServerMessage& isActiveMsg) {
	if (!isActiveMsg.has_isActive ||
		isActiveMsg.type != ServerMessage_MessageType_SET_IS_ACTIVE_CMD) {

		assert(false);
		return;
	}

	carModel.setIsActive(isActiveMsg.isActive);
}

void shootFire(const ServerMessage& fireMsg) {
	if (!fireMsg.has_fireType ||
		fireMsg.type != ServerMessage_MessageType_SHOOT_FIRE_CMD) {

		assert(false);
		return;
	}

	// TODO: Shoot the fire HERE
	switch (fireMsg.fireType) {

		case FireType_NO_FIRE:
			// Do nothing
			return;

		case FireType_SMALL_BURST:
			break;
		case FireType_MEDIUM_BURST:
			break;
		case FireType_LARGE_BURST:
			break;

		default:
			assert(false);
			return;
	}

	// Fire was officially shot, tell the server about it
	sendFireShotMsg(fireMsg.fireType);
}

void readSerial() {

	// Serial read/input operations
	if (serialStream->available() >= ServerMessage_size &&
		pb_decode(&pbInStream, ServerMessage_fields, &incomingMsg)) {

		switch (incomingMsg.type) {
			case ServerMessage_MessageType_STATUS_QUERY:
				sendInfoMsg();
				break;

			case ServerMessage_MessageType_SET_LED_COLOUR_CMD:
				setLedColour(incomingMsg);
				break;

			case ServerMessage_MessageType_SET_IS_ACTIVE_CMD:
				setIsActive(incomingMsg);
				break;

			case ServerMessage_MessageType_SHOOT_FIRE_CMD:
				shootFire(incomingMsg);
				break;

			default:
				// Shouldn't happen.
				assert(false);
				break;
		}
	}
}


void loop() {
	readSerial();
}

