#pragma once

#include <stdint.h>
#include <math.h>

/// @brief One climate sensor measurement snapshot.
struct SensorReading {
    float    temperature = NAN;  ///< Celsius. NAN if not available.
    float    humidity    = NAN;  ///< Percent RH. NAN if not available.
    float    pressure    = NAN;  ///< hPa, reserved for future sensors. NAN if unused.
    uint32_t ts_ms       = 0;    ///< millis() timestamp of this reading.
    bool     ok          = false;///< true if temperature and humidity are valid.
    int      err         = 0;    ///< Non-zero error code on failure.
};
