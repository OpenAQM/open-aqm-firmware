#pragma once

#include <OaqmLogger.h>
#include <devices/interfaces/OaqmTemperatureProvider.h>
#include <devices/interfaces/OaqmHumidityProvider.h>
#include <devices/interfaces/OaqmTimeProvider.h>

namespace OaqmDevices {
class Virtual : public OaqmTemperatureProvider, public OaqmHumidityProvider, public OaqmTimeProvider {
  public:
    struct VirtualValues {
        float temperature = 42.0f;
        float pressure = 42.0f;
        float humidity = 42.0f;
    } values;

    Virtual(unsigned char priority = 0) : OaqmTemperatureProvider(), OaqmHumidityProvider(), OaqmTimeProvider(), priority(priority) {};
    virtual ~Virtual() {};

    virtual void setup() override {
        setenv("TZ", "UTC0", 1); // Force systems clock to correspond to UTC (this is especially important on POSIX systems)
    };
    virtual void update() override {};
    virtual void reset() override {};
    virtual void stop() override {};

    virtual inline const char* getName() override {
        return "Virtual";
    };

    virtual inline float getTemperature() override {
        return this->values.temperature;
    };
    virtual inline unsigned char getTemperatureProviderPriority() override {
        return this->priority;
    };


    virtual inline float getHumidity() override {
        return this->values.humidity;
    };
    virtual inline unsigned char getHumidityProviderPriority() override {
        return this->priority;
    };

    virtual time_t getUTCTime() override {
        return time(nullptr);
    };
    virtual void setUTCTime(const time_t& epoch) {
        OSW_LOG_W("Virtual device does not support setting the time");
    };
    virtual unsigned char getTimeProviderPriority() override {
        return this->priority;
    };
#ifdef OSW_EMULATOR
    virtual time_t getTimezoneOffset(const time_t& timestamp, const String& timezone) override;
#endif
  private:
    const unsigned char priority;
};
};