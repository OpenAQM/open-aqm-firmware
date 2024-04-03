#ifndef OAQM_SERVICE_WIFI_TRANSMISSON_H
#define OAQM_SERVICE_WIFI_TRANSMISSON_H

#include "oaqm_service.h"

class OaqmServiceWifiTransmission : public OaqmServiceTask {
  public:
    OaqmServiceWifiTransmission() {};
    virtual void setup() override;
    virtual void loop() override;
    virtual void stop() override;
    ~OaqmServiceWifiTransmission() {};

  private:
    time_t printLimit = 0;
};

#endif