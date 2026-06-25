#include "Sht31ClimateSensor.h"

static constexpr int kErrOk         = 0;
static constexpr int kErrNotFound   = 1;
static constexpr int kErrNoData     = 2;
static constexpr int kErrReadFail   = 3;
static constexpr int kErrOutOfRange = 4;

static constexpr uint8_t kCandidates[] = {0x44, 0x45};

Sht31ClimateSensor::Sht31ClimateSensor(TwoWire* bus, uint32_t pollMs)
    : bus_(bus), dev_(0x44, bus), pollMs_(pollMs) {}

bool Sht31ClimateSensor::begin() {
    if (!bus_) { setError(0, kErrNotFound); return false; }
    // Probe deferred to first tick() — setup() остаётся быстрым, чтобы Improv
    // handleSerial успел перехватить байты от portal'а до окончания setup.
    last_ = {};
    return true;
}

void Sht31ClimateSensor::tick(uint32_t nowMs) {
    // Lazy probe: первый tick — пробуем 0x44/0x45, ставим foundAddr_ или silent-fail.
    if (!probeDone_) {
        probeDone_ = true;
        for (uint8_t addr : kCandidates) {
            bus_->beginTransmission(addr);
            if (bus_->endTransmission() == 0) {
                foundAddr_ = addr;
                dev_       = SHT31(addr, bus_);
                dev_.begin();
                dev_.requestData();
                prevMs_    = nowMs;
                return;
            }
        }
        setError(nowMs, kErrNotFound);
        return;
    }
    if (!foundAddr_) return;   // нет sensor — silent

    if ((nowMs - prevMs_) < pollMs_) return;
    prevMs_ = nowMs;

    if (!dev_.dataReady()) { setError(nowMs, kErrNoData);   return; }
    if (!dev_.readData())  { setError(nowMs, kErrReadFail); dev_.requestData(); return; }

    float t = dev_.getTemperature();
    float h = dev_.getHumidity();

    if (isnan(t) || isnan(h) || t < -40.0f || t > 125.0f || h < 0.0f || h > 100.0f) {
        setError(nowMs, kErrOutOfRange);
        dev_.requestData();
        return;
    }

    last_.temperature = t;
    last_.humidity    = h;
    last_.pressure    = NAN;
    last_.ts_ms       = nowMs;
    last_.ok          = true;
    last_.err         = kErrOk;

    dev_.requestData();
}

void Sht31ClimateSensor::setError(uint32_t nowMs, int errCode) {
    last_.temperature = NAN;
    last_.humidity    = NAN;
    last_.pressure    = NAN;
    last_.ts_ms       = nowMs;
    last_.ok          = false;
    last_.err         = errCode;
}
