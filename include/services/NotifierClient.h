#ifndef OAQM_SERVICE_TASKNOTIFIERCLIENT_H
#define OAQM_SERVICE_TASKNOTIFIERCLIENT_H

#include <string>

#include "./services/OaqmServiceTaskNotifier.h"
#include "./services/OaqmServiceTasks.h"

class NotifierClient {
  public:
    NotifierClient(std::string publisher);

    NotificationData createNotification(std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> timeToFire,
                                        std::string message = {}, std::array<bool, 7> daysOfWeek = {}, bool isPersistent = {});

    NotificationData createNotification(int hours, int minutes,
                                        std::string message = {}, std::array<bool, 7> daysOfWeek = {}, bool isPersistent = {});

    std::vector<NotificationData> readNotifications();

    void deleteNotification(unsigned id);

  private:
    const std::string publisher{};
};

#endif