#ifndef PB_ARDUINO_DECODE_H_
#define PB_ARDUINO_DECODE_H_

#include <Stream.h>
#include "pb_decode.h"

void pb_istream_from_stream(Stream &stream, pb_istream_t &istream);

#endif // PB_ARDUINO_DECODE_H_
