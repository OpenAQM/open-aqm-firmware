#pragma once

#include <memory>

#include <oaqm_util.h>
#include <oaqm_hal.h>
#include <devices/OaqmDevice.h>
// #if OAQM_PLATFORM_HARDWARE_BMA400 == 1
// #include <devices/bma400.h>
// #endif

#include <devices/esp32.h>
#include <devices/virtual.h>

class OaqmHal::Devices {
  public:
// #if OAQM_PLATFORM_HARDWARE_BMA400 == 1
//     OaqmDevices::BMA400* bma400;
// #endif
#if OAQM_PLATFORM_HARDWARE_VIRTUAL == 1
    OaqmDevices::Virtual* virtualDevice;
#endif
#if OAQM_PLATFORM_HARDWARE_ESP32 == 1
    OaqmDevices::NativeESP32* esp32;
#endif

    void setup(const bool& fromLightSleep);
    void update(); // Request devices to update their (cached) states
    void stop(const bool& toLightSleep);
  protected:
    Devices();
    ~Devices();
    friend OaqmHal;
    friend std::unique_ptr<OaqmHal::Devices>::deleter_type;
  private:
};