#pragma once

#include "sensor_reading.h"
#include <stdint.h>

/**
 * @brief Minimal interface for a temperature/humidity sensor.
 *
 * Call @c begin() once in setup(), then call @c tick() every loop iteration.
 * Read the last measurement with @c get().
 */
class IClimateSensor {
public:
    virtual ~IClimateSensor() = default;

    /// @brief Initialises the sensor hardware. Returns false if the sensor is not found.
    virtual bool begin() = 0;

    /// @brief Drives the sensor state machine. Pass current @c millis().
    virtual void tick(uint32_t nowMs) = 0;

    /// @brief Returns the most recent measurement.
    virtual SensorReading get() const = 0;
};
