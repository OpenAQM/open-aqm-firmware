#pragma once

#include <devices/OaqmDevice.h>
#include <devices/interfaces/OaqmGasDetectionProvider.h>

namespace OaqmDevices {
    class MQ131 : public OaqmGasDetectionProvider {
        MQ131() : OaqmGasDetectionProvider() {};
        virtual ~MQ131() {};

        virtual void setup() override;
        virtual void update() override;
        virtual void reset() override {};
        virtual void stop() override {};

        virtual inline const char* getName() override {
        return "MQ131";
    };
    };
};