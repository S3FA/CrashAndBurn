#ifndef CRASH_AND_BURN_PROTOCOL_PROTOCOL_H_
#define CRASH_AND_BURN_PROTOCOL_PROTOCOL_H_

#include "common.h"

namespace crashandburn {
namespace protocol {

// Core type definitions for the protocol
typedef char CarId;


class Syntax {
public:
    // Delimiters
    static const char PKG_START_CHAR   = '{';
    static const char PKG_END_CHAR     = '}';
    static const char PARAM_DELIM_CHAR = ',';
    
    // Event identifiers
    static const char CAR_COLLISION_EVENT_CHAR     = 'C';
    static const char CAR_TIPPING_OVER_EVENT_CHAR  = 'T';
    static const char CAR_STATUS_MSG_CHAR          = 'S';
    static const char CAR_LOCAL_DEADMAN_EVENT_CHAR = 'D';
    
    // Misc. specifiers
    static const int NUM_FLT_DECIMALS = 4;
    
    enum Team {
      SparklePonyTeam = 0,
      DeathTeam = 1
    };
    enum FlameType {
      ShortBurst = 0,
      MediumBurst = 1,
      LongBurst = 2
    };
    
      
private:
    Syntax(){}
    ~Syntax(){}
    

    DISALLOW_COPY_AND_ASSIGN(Syntax);
};

}
}

#endif // CRASH_AND_BURN_PROTOCOL_PROTOCOL_H_
