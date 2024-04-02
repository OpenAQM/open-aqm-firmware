#pragma once

#include <devices/OaqmDevice.h>
#include <devices/interfaces/OaqmCarbonDioxideProvider.h>

namespace OaqmDevices {
    class MHZ19B : public OaqmCarbonDioxideProvider {
        MHZ19B() : OaqmCarbonDioxideProvider() {};
        virtual ~MHZ19B() {};

        virtual void setup() override;
        virtual void update() override;
        virtual void reset() override {};
        virtual void stop() override {};

        virtual inline const char* getName() override {
        return "MHZ19B";
    };
    };
};