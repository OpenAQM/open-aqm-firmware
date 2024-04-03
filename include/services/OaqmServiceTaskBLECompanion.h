#ifndef OAQM_SERVICE_COMPANION_H
#define OAQM_SERVICE_COMPANION_H

#include <BLECharacteristic.h>
#include <BLEDevice.h>
#include <oaqm_hal.h>
#include <functional>
#include <string>

#include "oaqm_service.h"

#define NOTIFICATION_SERVICE_UID "30412632-6339-46e3-ad9e-bcfa9a766854"

#define NOTIFICATION_BRDCST_CHAR "23dac1dc-ca00-47ed-a5fa-e3b9da959685"

struct NotificationDetails {
    unsigned int uid;
    std::string app;
    std::string contents;
};

class OaqmServiceTaskBLECompanion : public OaqmServiceTask {
  public:
    OaqmServiceTaskBLECompanion(void) {};
    virtual void setup() override;
    virtual void loop() override;
    virtual void stop() override;
    ~OaqmServiceTaskBLECompanion() {};

    void setNotificationCallback(std::function<void(NotificationDetails)> cb);
    void startAdvertising();
    void stopAdvertising();

  private:
    BLEServer* bleServer = NULL;
    BLEService* notificationService = NULL;
    BLECharacteristic* notificationChar = NULL;

    std::function<void(NotificationDetails)> notificationCallback;

    friend class NotificationCallback;
};

#endif