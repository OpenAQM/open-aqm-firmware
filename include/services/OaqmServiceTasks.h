#include "oaqm_service.h"

class OaqmServiceTaskBLECompanion;
class OaqmServiceTaskExample;
class OaqmServiceTaskMemMonitor;
class OaqmServiceTaskNotifier;
#ifdef OAQM_FEATURE_WIFI
class OaqmServiceTaskWiFi;
class OaqmServiceTaskWebserver;
#endif
namespace OaqmServiceAllTasks {
#if SERVICE_BLE_COMPANION == 1
extern OaqmServiceTaskBLECompanion bleCompanion;
#endif
// extern OaqmServiceTaskExample example;
#ifdef OAQM_FEATURE_WIFI
extern OaqmServiceTaskWiFi wifi;
extern OaqmServiceTaskWebserver webserver;
#endif
#if OAQM_SERVICE_NOTIFIER == 1
extern OaqmServiceTaskNotifier notifier;
#endif
extern OaqmServiceTaskMemMonitor memory;
}

extern const unsigned char oaqmServiceTasksCount;
extern OaqmServiceTask* oaqmServiceTasks[];
