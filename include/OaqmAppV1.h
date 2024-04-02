#pragma once
#include <oaqm_hal.h>

class OaqmAppV1 {
  public:
    virtual void setup() = 0;
    virtual void loop() = 0;
    virtual void stop() = 0;
};

typedef OaqmAppV1 OaqmApp; // For backwards compatibility