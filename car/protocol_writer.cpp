#include "protocol_writer.h"

using namespace crashandburn::protocol;

ProtocolWriter::ProtocolWriter() {
}

ProtocolWriter::~ProtocolWriter() {
}

boolean ProtocolWriter::writeStatusToSerial(boolean isActivated) {
  ProtocolWriter::writePacketStart();
  ProtocolWriter::writePacketType(Syntax::CAR_STATUS_MSG_CHAR);
  
  Serial.print(isActivated ? 1 : 0);
  // TODO: More stuff here
  
  ProtocolWriter::writePacketEnd();
  return true;
}

boolean ProtocolWriter::writeCollisionEventToSerial(float accX, float accY, float accZ) {
  // Make sure the acceleration is normalized (to avoid large floating point numbers)
  if (accX > 1 || accX < -1 || accY > 1 || accY < -1 || accZ > 1 || accZ < -1) {
    
    float mag = sqrt(accX*accX + accY*accY + accZ*accZ);
    if (mag <= 0.00001) {
      // This should never happen
      return false;
    }
    
    accX /= mag;
    accY /= mag;
    accZ /= mag;
  }
  
  ProtocolWriter::writePacketStart();
  ProtocolWriter::writePacketType(Syntax::CAR_COLLISION_EVENT_CHAR);
  
  Serial.print(accX, Syntax::NUM_FLT_DECIMALS);
  ProtocolWriter::writeDelimiter();
  Serial.print(accY, Syntax::NUM_FLT_DECIMALS);
  ProtocolWriter::writeDelimiter();
  Serial.print(accZ, Syntax::NUM_FLT_DECIMALS);
  
  ProtocolWriter::writePacketEnd();
  
  return true;
}

boolean ProtocolWriter::writeTippingOverEventToSerial() {
  
  ProtocolWriter::writePacketStart();
  ProtocolWriter::writePacketType(Syntax::CAR_TIPPING_OVER_EVENT_CHAR);
  ProtocolWriter::writePacketEnd();
  
  return true;
}

