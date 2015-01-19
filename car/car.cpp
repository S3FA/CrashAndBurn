
#include "car.h"
#include "common.h"
#include "pb_arduino_decode.h"
#include "pb_arduino_encode.h"

#include "server_to_car.pb.h"

// Protobuf output stream and message objects
pb_ostream_t pbOutStream;
// Protobuf input stream and message objects
pb_istream_t pbInStream;
ServerMessage incomingMsg;

Stream* serialStream = &Serial;

void setup() {
	// Setup the output and input serial streams and callbacks
	Serial.begin(115200);
	pb_ostream_from_stream(*serialStream, pbOutStream);
	pb_istream_from_stream(*serialStream, pbInStream);
}

void loop() {
	// Serial read/input operations
	if (serialStream->available() >= ServerMessage_size &&
		pb_decode(&pbInStream, ServerMessage_fields, &incomingMsg)) {

		switch (incomingMsg.type) {
			case ServerMessage_MessageType_STATUS_QUERY:
				break;
			case ServerMessage_MessageType_SET_LED_COLOUR_CMD:
				break;
			case ServerMessage_MessageType_SET_IS_ACTIVE_CMD:
				break;
			case ServerMessage_MessageType_SHOOT_FIRE_CMD:
				break;
			case ServerMessage_MessageType_COLLISION_INFO:
				break;
			default:
				// Shouldn't happen.
				assert(false);
				break;
		}

	}

}

