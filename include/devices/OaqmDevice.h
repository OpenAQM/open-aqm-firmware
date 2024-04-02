#pragma once

#include <set>

#include <Arduino.h>

class OaqmDevice {
  public:
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void reset() = 0;
    virtual void stop() = 0;

    virtual const char* getName() = 0;

    static const std::set<OaqmDevice*>* getAllDevices() {
        return &allDevices;
    };
  protected:
    OaqmDevice();
    virtual ~OaqmDevice();
  private:
    static std::set<OaqmDevice*> allDevices;
};