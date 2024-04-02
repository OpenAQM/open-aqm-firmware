#pragma once

#include <memory>

#include <oaqm_hal.h>
#include <devices/interfaces/OaqmTemperatureProvider.h>
#include <devices/interfaces/OaqmHumidityProvider.h>

#if OAQM_PLATFORM_ENVIRONMENT == 1
class OaqmHal::Environment {
  public:
    void updateProviders(); // Retrieve all environment sensors
    void reset(); // Reset all data on environment sensors

#if OAQM_PLATFORM_ENVIRONMENT_TEMPERATURE == 1
    float getTemperature();
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
    OaqmTemperatureProvider* tempSensor = nullptr;
    OaqmHumidityProvider* humiSensor = nullptr;
};
#endif