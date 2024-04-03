#ifndef OAQM_SERVICE_TASKEXAMPLE_H
#define OAQM_SERVICE_TASKEXAMPLE_H

#include "oaqm_service.h"

class OaqmServiceTaskExample : public OaqmServiceTask {
  public:
    OaqmServiceTaskExample() {};
    virtual void setup() override;
    virtual void loop() override;
    virtual void stop() override;
    ~OaqmServiceTaskExample() {};

  private:
    time_t printLimit = 0;
};

#endif