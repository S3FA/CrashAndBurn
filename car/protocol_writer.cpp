#include "protocol_writer.h"

using namespace crashandburn::protocol;

ProtocolWriter::ProtocolWriter() {
}

ProtocolWriter::~ProtocolWriter() {
}

boolean ProtocolWriter::writeStatusToSerial(CarId id, boolean isActive) {
  ProtocolWriter::writePacketStart();
  ProtocolWriter::writePacketType(Syntax::CAR_STATUS_MSG_CHAR);
  
  ProtocolWriter::writeCarId(id);
  ProtocolWriter::writeDelimiter();
  ProtocolWriter::writeBoolean(isActive);
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

boolean ProtocolWriter::writeFireShotEventToSerial(Syntax::FlameType fireType) {
  ProtocolWriter::writePacketStart();
  ProtocolWriter::writePacketType(Syntax::CAR_LOCAL_DEADMAN_EVENT_CHAR);
  Serial.print(static_cast<int>(fireType));
  ProtocolWriter::writePacketEnd();
  
  return true;
}

boolean ProtocolWriter::writeLocalDeadmanEventToSerial(boolean isFireOn) {
  
  ProtocolWriter::writePacketStart();
  ProtocolWriter::writePacketType(Syntax::CAR_LOCAL_DEADMAN_EVENT_CHAR);
  ProtocolWriter::writeBoolean(isFireOn);
  ProtocolWriter::writePacketEnd();
  
  return true;
}

boolean ProtocolWriter::writeTippingOverEventToSerial() {
  
  ProtocolWriter::writePacketStart();
  ProtocolWriter::writePacketType(Syntax::CAR_TIPPING_OVER_EVENT_CHAR);
  ProtocolWriter::writePacketEnd();
  
  return true;
}

