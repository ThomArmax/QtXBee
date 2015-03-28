#ifndef GLOBAL
#define GLOBAL

namespace QtXBee {

enum DeviceType {
    Coordinator,
    Route,
    EndDevice
};

enum HardwareVersion {
    XBeeSerieUnknown = 0,
    XBeeSerie1 = 0x17,
    XBeeSerie1Pro,
    XBeeSeriel2,
    XBeeSerie2Pro
};

} // END namespace

#endif // GLOBAL

