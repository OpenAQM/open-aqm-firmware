#pragma once

#include <Wire.h>
#include <RV-3028-C7.h>

#include <devices/interfaces/OaqmTimeProvider.h>
#include <devices/interfaces/OaqmTemperatureProvider.h>

namespace OaqmDevices {
class RV_3028_C7 : public OaqmTemperatureProvider, public OaqmTimeProvider {
  public:
    RV_3028_C7() : OaqmTemperatureProvider(), OaqmTimeProvider(), Rtc() {};
    virtual ~RV_3028_C7() {};

    virtual void setup() override;
    virtual void update() override;
    virtual void reset() override {};
    virtual void stop() override {};

    virtual inline const char* getName() override {
        return "RV_3028_C7";
    };

    virtual float getTemperature() override;
    virtual inline unsigned char getTemperatureProviderPriority() override {
        return 20;
    }; // This sensor is not sooo good...

    virtual time_t getUTCTime() override;
    virtual void setUTCTime(const time_t& epoch) override;
    virtual inline unsigned char getTimeProviderPriority() override {
        return 100;
    }; // This is a specialized device!
  private:
    RV3028 Rtc;
    uint32_t _utcTime = 0;
};
};