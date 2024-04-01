#pragma once

#include <memory>

#include <oaqm_util.h>
#include <oaqm_hal.h>
#include <devices/OaqmDevice.h>
#if OAQM_PLATFORM_HARDWARE_BMA400 == 1
#include <devices/bma400.h>
#endif
#if OAQM_PLATFORM_HARDWARE_QMC5883L == 1
#include <devices/qmc5883l.h>
#endif
#if OAQM_PLATFORM_HARDWARE_BME280 == 1
#include <devices/bme280.h>
#endif
#if OAQM_PLATFORM_HARDWARE_DS3231MZ == 1
#include <devices/ds3231mz.h>
#endif
#include <devices/esp32.h>
#include <devices/virtual.h>

class OaqmHal::Devices {
  public:
#if OAQM_PLATFORM_HARDWARE_BMA400 == 1
    OaqmDevices::BMA400* bma400;
#endif
#if OAQM_PLATFORM_HARDWARE_QMC5883L == 1
    OaqmDevices::QMC5883L* qmc5883l;
#endif
#if OAQM_PLATFORM_HARDWARE_BME280 == 1
    OaqmDevices::BME280* bme280;
#endif
#if OAQM_PLATFORM_HARDWARE_DS3231MZ == 1
    OaqmDevices::DS3231MZ* ds3231mz;
#endif
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