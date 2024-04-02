#pragma once

#include <list>

#include <devices/OaqmDevice.h>

class OaqmHumidityProvider : public OaqmDevice {
  public:
    virtual float getHumidity() = 0;

    virtual unsigned char getHumidityProviderPriority() = 0;
    static const std::list<OaqmHumidityProvider*>* getAllHumidityDevices() {
        return &allDevices;
    };
  protected:
    OaqmHumidityProvider() : OaqmDevice() {
        this->allDevices.push_back(this);
    };
    ~OaqmHumidityProvider() {
        this->allDevices.remove(this);
    };
  private:
    static std::list<OaqmHumidityProvider*> allDevices;
};