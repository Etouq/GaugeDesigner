#ifndef _DATAIDENTIFIERS_H
#define _DATAIDENTIFIERS_H

#include <cstdint>

enum class SharedServerIds : uint8_t
{
    // server identifier
    SIMCONNECT_SERVER,
    GAUGE_DESIGNER_SERVER,
};

enum class DesignerIds : uint8_t
{
    REMOVE_AIRCRAFT_LIST,
    LOAD_AIRCRAFT_LIST,
    SAVE_AIRCRAFT
};

enum class ClientToDesignerIds : uint8_t
{
    CLIENT_NETWORK_VERSION,
    QUIT,
    LOAD_AIRCRAFT,
    AIRCRAFT_FILE_LIST
};


#endif   // DATAIDENTIFIERS_H
