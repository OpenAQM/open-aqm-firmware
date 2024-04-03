#ifndef OAQM_SERVICE_LORA_PEER_TO_PEER_H
#define OAQM_SERVICE_LORA_PEER_TO_PEER_H

#include "oaqm_service.h"

class OaqmServiceLoraPeerToPeer : public OaqmServiceTask {
  public:
    OaqmServiceLoraPeerToPeer() {};
    virtual void setup() override;
    virtual void loop() override;
    virtual void stop() override;
    ~OaqmServiceLoraPeerToPeer() {};

  private:
    time_t printLimit = 0;
};

#endif