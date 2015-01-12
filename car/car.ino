
#include "protocol_reader.h"
#include "protocol_writer.h"

using namespace crashandburn::protocol;

ProtocolWriter protocolWriter;
ProtocolReader protocolReader;

// Callback Setup
OnCarCollision collisionCallback;

namespace crashandburn {
namespace protocol {

void OnCarCollisionCallback(CarId carId0, CarId carId1) {
  
}

}
}

void setup() {
  Serial.begin(9600);
  
  collisionCallback = &OnCarCollisionCallback;
  protocolReader.setCarCollisionCallback(&collisionCallback);

}

void loop() {
  protocolReader.readFromSerial();
  
}


