#ifndef CRASH_AND_BURN_PROTOCOL_PROTOCOL_WRITER_H_
#define CRASH_AND_BURN_PROTOCOL_PROTOCOL_WRITER_H_

#include "common.h"
#include "protocol.h"

namespace crashandburn {
namespace protocol {
    
class ProtocolWriter {
public:
    ProtocolWriter();
    ~ProtocolWriter();

    boolean writeStatusToSerial(boolean isActivated/*, uint8_t life, Syntax::Team team */);
    boolean writeCollisionEventToSerial(float accX, float accY, float accZ);
    boolean writeTippingOverEventToSerial();
    //boolean writeButtonPressedEventToSerial(Syntax::ButtonType button);
    
private:
    //static void writeCarIdToSerial(CarId id) { Serial.write(id); }

    static void writePacketStart() { Serial.print(Syntax::PKG_START_CHAR); }
    static void writePacketEnd()   { Serial.print(Syntax::PKG_END_CHAR); }
    static void writeDelimiter()   { Serial.print(Syntax::PARAM_DELIM_CHAR); }
    static void writePacketType(char type) { Serial.print(type); }

    DISALLOW_COPY_AND_ASSIGN(ProtocolWriter);
};
    
}
}


#endif // CRASH_AND_BURN_PROTOCOL_PROTOCOL_WRITER_H_
