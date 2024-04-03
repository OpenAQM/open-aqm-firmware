#pragma once

#include "oaqm_service.h"

class OaqmServiceTaskMemMonitor : public OaqmServiceTask {
  public:
    OaqmServiceTaskMemMonitor() {};
    virtual void setup() override;
    virtual void loop() override;
    void updateLoopTaskStats();  // Call this from the main loop regulary!
    void printStats();
    bool hasLowMemoryCondition();
    ~OaqmServiceTaskMemMonitor() {};

  private:
    unsigned core0high;
    unsigned core1high;
    unsigned heapHigh;
    bool lowMemoryCondition = false;
};