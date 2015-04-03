#ifndef GLOBAL
#define GLOBAL

/**
 * @file global.h Defines global properties and glob enums.
 */
namespace QtXBee {

/**
 * @brief The DeviceType enum
 */
enum DeviceType {
    Coordinator,
    Router,
    EndDevice
};

/**
 * @brief The HardwareVersion enum
 */
enum HardwareVersion {
    XBeeSerie1 = 0x17,      /**< XBee Serie 1 hardware version */
    XBeeSerie1Pro,          /**< XBee Serie 1 Pro hardware version */
    XBeeSeriel2,            /**< XBee Serie 2 hardware version */
    XBeeSerie2Pro,          /**< XBee Serie 2 hardware version */
    XBeeSerieUnknown        /**< Unkown/Invalid hardware version */
};

} // END namespace

#endif // GLOBAL

