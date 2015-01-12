
#include "protocol_reader.h"

using namespace crashandburn::protocol;

#define MAX_SERIAL_READ_TIME_IN_MS 3000

#define MAX_READ_TIME_RETURN_CHECK(startTimeMs, currTimeMs) \
currTimeMs = millis(); \
if (abs(currTimeMs - startTimeMs) > MAX_SERIAL_READ_TIME_IN_MS) { return; }

ProtocolReader::ProtocolReader(): carCollisionCb(NULL) {
}

ProtocolReader::~ProtocolReader() {
}

void ProtocolReader::readFromSerial() {
    
    // The protocol specifies that a package must be AT LEAST 3 bytes large
    if (Serial.available() < 3) {
        return;
    }
    
    long startTimeInMillis = millis();
    long currTimeInMillis  = startTimeInMillis;
    
    // Keep reading through the serial buffer until we get to the start of
    // an incoming package
    while (Serial.available() > 0 &&
           Serial.peek() != Syntax::PKG_START_CHAR) {
        
        Serial.read();
        MAX_READ_TIME_RETURN_CHECK(startTimeInMillis, currTimeInMillis);
    }
    
    while (Serial.available() == 0) {
        MAX_READ_TIME_RETURN_CHECK(startTimeInMillis, currTimeInMillis);
    }
    
    char tempReadByte;
    
    // Read through the starting character in the package
    tempReadByte = Serial.read();
    if (tempReadByte == Syntax::PKG_START_CHAR) {
        
        // The next character will define what type of package we're dealing with
        while (Serial.available() == 0) {
            MAX_READ_TIME_RETURN_CHECK(startTimeInMillis, currTimeInMillis);
        }
        tempReadByte = Serial.read();
        
        switch (tempReadByte) {
            case Syntax::CAR_COLLISION_EVENT_CHAR:
                readCarCollisionEventFromSerial(startTimeInMillis);
                break;
                
            default:
                // Invalid protocol, package type was not identified
                return;
        }
        
        
    }
    else {
        // This should never happen.
        // (If we get here then for some reason the package's starting character
        // wasn't the starting character)
    }
    
    /*
    // If there's still serial data available, keep reading through the serial buffer
    // until we get to the end of the package or the start of another
    while (Serial.available() > 0 &&
           Serial.peek() != Syntax::PKG_END_CHAR &&
           Serial.peek() != Syntax::PKG_START_CHAR) {
        
        Serial.read();
        MAX_READ_TIME_RETURN_CHECK(startTimeInMillis, currTimeInMillis);
    }
    if (Serial.available() > 0 && Serial.peek() == Syntax::PKG_END_CHAR) {
        Serial.read();
    }
    */
}

void ProtocolReader::readCarCollisionEventFromSerial(long startReadTimeInMillis) {
    long currTimeInMillis = startReadTimeInMillis;
    
    // We expect two CarId identifiers for the two colliding car identifiers
    while (Serial.available() == 0) {
        MAX_READ_TIME_RETURN_CHECK(startReadTimeInMillis, currTimeInMillis);
    }
    
    CarId carId0 = readCarIdFromSerial();
    
    while (Serial.available() == 0) {
        MAX_READ_TIME_RETURN_CHECK(startReadTimeInMillis, currTimeInMillis);
    }
    
    CarId carId1 = readCarIdFromSerial();
    
    if (this->carCollisionCb != NULL) {
        (*this->carCollisionCb)(carId0, carId1);
    }
}
