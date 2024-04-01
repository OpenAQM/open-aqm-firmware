#pragma once

#include <memory>

#include <oaqm_hal.h>
#include <devices/interfaces/OaqmTemperatureProvider.h>
#include <devices/interfaces/OaqmAccelerationProvider.h>
#include <devices/interfaces/OaqmMagnetometerProvider.h>
#include <devices/interfaces/OaqmHumidityProvider.h>
#include <devices/interfaces/OaqmPressureProvider.h>

#if OAQM_PLATFORM_ENVIRONMENT == 1
class OaqmHal::Environment {
  public:
    void updateProviders(); // Retrieve all environment sensors
    void reset(); // Reset all data on environment sensors

#if OAQM_PLATFORM_ENVIRONMENT_TEMPERATURE == 1
    float getTemperature();
#endif

#if OAQM_PLATFORM_ENVIRONMENT_PRESSURE == 1
    float getPressure();
#endif

#if OAQM_PLATFORM_ENVIRONMENT_HUMIDITY == 1
    float getHumidity();
#endif

  protected:
    Environment() {}
    ~Environment() {}
    friend OaqmHal;
    friend std::unique_ptr<OaqmHal::Environment>::deleter_type;
  private:
#ifdef OAQM_FEATURE_STATS_STEPS
    uint32_t _stepsCache[7] = {0};
    uint32_t _stepsSum = 0;
    uint32_t _stepsLastDoW = 0;
#endif
    OaqmTemperatureProvider* tempSensor = nullptr;
    OaqmAccelerationProvider* accelSensor = nullptr;
    OaqmHumidityProvider* humiSensor = nullptr;
};
#endif