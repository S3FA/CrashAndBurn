#ifndef PB_ARDUINO_ENCODE_H_
#define PB_ARDUINO_ENCODE_H_

#include <Print.h>
#include "pb_encode.h"

void pb_ostream_from_stream(Print &stream, pb_ostream_t &ostream);

#endif /* PB_ARDUINO_ENCODE_H_ */
