#pragma once

#include <list>

#include <devices/OaqmDevice.h>

class OaqmCarbonDioxideProvider : public OaqmDevice {
  public:
    virtual float getCarbonDioxide() = 0;

    virtual unsigned char getCarbonDioxideProviderPriority() = 0;
    static const std::list<OaqmCarbonDioxideProvider*>* getAllCarbonDioxideDevices() {
        return &allDevices;
    };
  protected:
    OaqmCarbonDioxideProvider() : OaqmDevice() {
        this->allDevices.push_back(this);
    };
    ~OaqmCarbonDioxideProvider() {
        this->allDevices.remove(this);
    };
  private:
    static std::list<OaqmCarbonDioxideProvider*> allDevices;
};