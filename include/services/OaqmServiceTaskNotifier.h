#ifndef OAQM_SERVICE_TASKNOTIFIER_H
#define OAQM_SERVICE_TASKNOTIFIER_H

#include <algorithm>
#include <map>

#include "../lib/date/date.h"
#include "oaqm_service.h"
#include "oaqm_ui.h"

class Notification {
  public:
    Notification(std::string publisher, std::string message = {}, std::array<bool, 7> daysOfWeek = {}, bool isPersistent = {})
        : publisher{std::move(publisher)}, message{std::move(message)}, daysOfWeek{std::move(daysOfWeek)}, isPersistent{isPersistent} {
        id = count;
        ++count;
    }

    unsigned getId() const {
        return id;
    }

    std::string getMessage() const {
        return message;
    }

    std::string getPublisher() const {
        return publisher;
    }

    std::array<bool, 7> getDaysOfWeek() const {
        return daysOfWeek;
    }

    bool getPersistence() const {
        return isPersistent;
    }

  private:
    unsigned id{};
    static unsigned count;
    const std::string publisher{};
    const std::string message{};
    const std::array<bool, 7> daysOfWeek{};
    const bool isPersistent{};
};

typedef std::pair<std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>, Notification> NotificationData;

class OaqmServiceTaskNotifier : public OaqmServiceTask {
  public:
    OaqmServiceTaskNotifier() {};
    virtual void setup() override;
    virtual void loop() override;
    virtual void stop() override;
    ~OaqmServiceTaskNotifier() {};

  private:
    friend class NotifierClient;

    NotificationData createNotification(std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> timeToFire, std::string publisher,
                                        std::string message = {}, std::array<bool, 7> daysOfWeek = {}, bool isPersistent = {});

    NotificationData createNotification(int hours, int minutes, std::string publisher,
                                        std::string message = {}, std::array<bool, 7> daysOfWeek = {}, bool isPersistent = {});

    std::vector<NotificationData> readNotifications(std::string publisher);

    void deleteNotification(unsigned id, std::string publisher);

    std::multimap<NotificationData::first_type, const NotificationData::second_type> scheduler{};

    std::mutex mutlimapMutex{};

    // For testing purposes (to access and test private members)
    friend class TestOaqmServiceTaskNotifier;
};

#endif