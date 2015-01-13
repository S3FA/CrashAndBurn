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

    boolean writeStatusToSerial(CarId id, boolean isActive/*, uint32_t colour, Syntax::Team team */);
    boolean writeCollisionEventToSerial(float accX, float accY, float accZ);
    boolean writeFireShotEventToSerial(Syntax::FlameType fireType);
    boolean writeLocalDeadmanEventToSerial(boolean isFireOn);
    //boolean writeButtonPressedEventToSerial(Syntax::ButtonType button);
    
    
    boolean writeTippingOverEventToSerial(); // Might not be a thing
    
private:
    static void writeCarId(CarId id) { Serial.write(id); }
    static void writePacketStart() { Serial.print(Syntax::PKG_START_CHAR); }
    static void writePacketEnd()   { Serial.print(Syntax::PKG_END_CHAR); }
    static void writeDelimiter()   { Serial.print(Syntax::PARAM_DELIM_CHAR); }
    static void writePacketType(char type) { Serial.print(type); }
    static void writeBoolean(boolean b) { Serial.print(b ? 1 : 0); }

    DISALLOW_COPY_AND_ASSIGN(ProtocolWriter);
};
    
}
}


#endif // CRASH_AND_BURN_PROTOCOL_PROTOCOL_WRITER_H_
