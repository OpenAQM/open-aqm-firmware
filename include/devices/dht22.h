#pragma once

// #include <dht.h>

#include <devices/OaqmDevice.h>
#include <devices/interfaces/OaqmTemperatureProvider.h>
#include <devices/interfaces/OaqmHumidityProvider.h>

namespace OaqmDevices {
    class DHT22 : public OaqmTemperatureProvider, public OaqmHumidityProvider {
        DHT22() : OaqmTemperatureProvider(),  OaqmHumidityProvider() {};
        virtual ~DHT22() {};

        virtual void setup() override;
        virtual void update() override;
        virtual void reset() override {};
        virtual void stop() override {};

        virtual inline const char* getName() override {
        return "DHT22";
    };
    };
};