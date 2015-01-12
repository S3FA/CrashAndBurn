#ifndef CRASH_AND_BURN_PROTOCOL_PROTOCOL_READER_H_
#define CRASH_AND_BURN_PROTOCOL_PROTOCOL_READER_H_

#include "common.h"
#include "protocol.h"

namespace crashandburn {
namespace protocol {

// Event Callback Definitions *****************************

// Server to Car Event Callbacks ------------------------------------
    
/**
 * Car Collision Events
 * Happens when a car collision has occurred. This event
 * is sent from the server to all cars.
 * Parameters: The identifiers of the two cars that collided.
 */
typedef void (*OnCarCollision)(CarId, CarId);

class ProtocolReader {
public:
    ProtocolReader();
    ~ProtocolReader();
    
    void readFromSerial();
    
    // Callbacks
    void setCarCollisionCallback(OnCarCollision* cb) { this->carCollisionCb = cb; }
    
private:
    // Callback members
    OnCarCollision* carCollisionCb;
    
    static CarId readCarIdFromSerial() { return Serial.read(); }
    
    void readCarCollisionEventFromSerial(long startReadTimeInMillis);
    
    DISALLOW_COPY_AND_ASSIGN(ProtocolReader);
};
    
}
}

#endif // CRASH_AND_BURN_PROTOCOL_PROTOCOL_READER_H_
