#ifndef OAQM_SERVICE_MANAGER_H
#define OAQM_SERVICE_MANAGER_H
#include "oaqm_hal.h"
#include "oaqm_service.h"

// #ifdef OAQM_EMULATOR
// #include <thread>
// #endif

class OaqmServiceManager {
  public:
    static OaqmServiceManager& getInstance() {
        if(instance == nullptr) {
            instance.reset(new OaqmServiceManager());
        }
        return *instance.get();
    }
    static void resetInstance() {
        instance.reset();
    }

    //Temp workaround until #137 is done
#ifdef OAQM_FEATURE_WIFI
#define _SERVICE_WIFI 1
#else
#define _SERVICE_WIFI 0
#endif
    const unsigned workerStackSize = 1024 + (7168 * _SERVICE_WIFI); // If wifi is active, set to same size as core 0
    const unsigned workerStartupDelay = 2000;
    const unsigned workerLoopDelay = 10;

    void setup();
    void loop();
    void stop();

  protected:
    ~OaqmServiceManager() {
        this->stop();
    };

    friend std::unique_ptr<OaqmServiceManager>::deleter_type;
  private:
    static std::unique_ptr<OaqmServiceManager> instance;
// #ifndef OAQM_EMULATOR
//     TaskHandle_t core0worker;
// #else
    std::unique_ptr<std::jthread> core0worker;
// #endif
    bool active = false;

    OaqmServiceManager() {};
    void worker();
};
#endif