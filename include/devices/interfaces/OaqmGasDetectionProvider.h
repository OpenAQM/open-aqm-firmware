#pragma once

#include <list>

#include <devices/OaqmDevice.h>

class OaqmGasDetectionProvider : public OaqmDevice {
  public:
    virtual float getGasDetection() = 0;

    virtual unsigned char getGasDetectionProviderPriority() = 0;
    static const std::list<OaqmGasDetectionProvider*>* getAllGasDetectionDevices() {
        return &allDevices;
    };
  protected:
    OaqmGasDetectionProvider() : OaqmDevice() {
        this->allDevices.push_back(this);
    };
    ~OaqmGasDetectionProvider() {
        this->allDevices.remove(this);
    };
  private:
    static std::list<OaqmGasDetectionProvider*> allDevices;
};