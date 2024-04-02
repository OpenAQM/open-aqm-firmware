#ifndef OAQM_SERVICE_H
#define OAQM_SERVICE_H
#include <OaqmAppV1.h>

class OaqmServiceTask : public OaqmApp {
  public:
    OaqmServiceTask() : OaqmApp() {}
    virtual void setup() override;
    bool isRunning();
    virtual void stop() override;
    virtual ~OaqmServiceTask() {};

  private:
    bool taskEnabled = false;
};
#endif