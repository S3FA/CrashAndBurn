#include "car.h"
#include "common.h"
#include "pb_decode.h"
#include "pb_encode.h"

bool serialOutputCallback(pb_ostream_t *stream, const uint8_t *buf, size_t count) {
	return Serial.write(buf, count) == count;
}

pb_ostream_t pbOutStream = {&serialOutputCallback, NULL, SIZE_MAX, 0};

void setup() {
	Serial.begin(115200);
}

void loop() {
	Serial.println("HERE");
}

