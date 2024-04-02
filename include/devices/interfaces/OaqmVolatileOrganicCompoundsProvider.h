#pragma once

#include <list>

#include <devices/OaqmDevice.h>

class OaqmVolatileOrganicCompoundsProvider : public OaqmDevice {
  public:
    virtual float getVolatileOrganicCompounds() = 0;

    virtual unsigned char getVolatileOrganicCompoundsProviderPriority() = 0;
    static const std::list<OaqmVolatileOrganicCompoundsProvider*>* getAllVolatileOrganicCompoundsDevices() {
        return &allDevices;
    };
  protected:
    OaqmVolatileOrganicCompoundsProvider() : OaqmDevice() {
        this->allDevices.push_back(this);
    };
    ~OaqmVolatileOrganicCompoundsProvider() {
        this->allDevices.remove(this);
    };
  private:
    static std::list<OaqmVolatileOrganicCompoundsProvider*> allDevices;
};