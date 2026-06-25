#pragma once

#include "IClimateSensor.h"
#include <Wire.h>
#include <SHT31.h>

/**
 * @brief IClimateSensor implementation for the SHT31 temperature/humidity sensor.
 *
 * Uses the RobTillaart/SHT31 library with async (requestData/readData) API so
 * that @c tick() never blocks the loop.
 *
 * @c begin() probes both standard SHT31 addresses (0x44 and 0x45) and uses
 * whichever responds. Returns @c false if neither is found — the device then
 * runs normally without a sensor.
 *
 * Usage:
 * @code
 * Wire.begin(SDA_PIN, SCL_PIN);
 * Sht31ClimateSensor sensor(&Wire);
 * bool ok = sensor.begin();  // auto-detects 0x44 or 0x45
 * if (ok) HAL_LOG_INFO("MAIN", "SHT31 at 0x%02X", sensor.foundAddr());
 * // in loop():
 * sensor.tick(millis());
 * @endcode
 */
class Sht31ClimateSensor : public IClimateSensor {
public:
    /**
     * @param bus    TwoWire instance, already initialised with Wire.begin().
     * @param pollMs How often to request a new reading. Default: 1000 ms.
     */
    explicit Sht31ClimateSensor(TwoWire* bus, uint32_t pollMs = 1000);

    /// @brief Probes 0x44 and 0x45; initialises the first one that responds.
    bool          begin() override;
    void          tick(uint32_t nowMs) override;
    SensorReading get() const override { return last_; }

    /// @brief Returns the I2C address that responded during @c begin(). 0 if not found.
    uint8_t foundAddr() const { return foundAddr_; }

private:
    void setError(uint32_t nowMs, int errCode);

    TwoWire*      bus_;
    SHT31         dev_;
    uint32_t      pollMs_;
    uint32_t      prevMs_    = 0;
    uint8_t       foundAddr_ = 0;
    bool          probeDone_ = false;
    SensorReading last_;
};
