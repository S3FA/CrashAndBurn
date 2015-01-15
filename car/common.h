#ifndef CRASH_AND_BURN_PROTOCOL_COMMON_H_
#define CRASH_AND_BURN_PROTOCOL_COMMON_H_

#include <Arduino.h>

#define SIZE_MAX 65535

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(const TypeName&);   \
void operator=(const TypeName&)

#endif // CRASH_AND_BURN_PROTOCOL_COMMON_H_
