#pragma once

#include <list>

#include <devices/OaqmDevice.h>

class OaqmParticulateMatterProvider : public OaqmDevice {
  public:
    virtual float getParticulateMatter() = 0;

    virtual unsigned char getParticulateMatterProviderPriority() = 0;
    static const std::list<OaqmParticulateMatterProvider*>* getAllParticulateMatterDevices() {
        return &allDevices;
    };
  protected:
    OaqmParticulateMatterProvider() : OaqmDevice() {
        this->allDevices.push_back(this);
    };
    ~OaqmParticulateMatterProvider() {
        this->allDevices.remove(this);
    };
  private:
    static std::list<OaqmParticulateMatterProvider*> allDevices;
};