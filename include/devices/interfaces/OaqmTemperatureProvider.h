#pragma once

#include <list>

#include <devices/OaqmDevice.h>

class OaqmTemperatureProvider : public OaqmDevice {
  public:
    virtual float getTemperature() = 0;

    virtual unsigned char getTemperatureProviderPriority() = 0;
    static const std::list<OaqmTemperatureProvider*>* getAllTemperatureDevices() {
        return &allDevices;
    };
  protected:
    OaqmTemperatureProvider() : OaqmDevice() {
        this->allDevices.push_back(this);
    };
    ~OaqmTemperatureProvider() {
        this->allDevices.remove(this);
    };
  private:
    static std::list<OaqmTemperatureProvider*> allDevices;
};