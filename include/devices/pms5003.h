#pragma once

#include <devices/OaqmDevice.h>
#include <devices/interfaces/OaqmParticulateMatterProvider.h>

namespace OaqmDevices {
    class PMS5003 : public OaqmParticulateMatterProvider {
        PMS5003() : OaqmParticulateMatterProvider() {};
        virtual ~PMS5003() {};

        virtual void setup() override;
        virtual void update() override;
        virtual void reset() override {};
        virtual void stop() override {};

        virtual inline const char* getName() override {
        return "PMS5003";
    };
    };
};