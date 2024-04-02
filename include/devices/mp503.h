#pragma once

#include <devices/OaqmDevice.h>
#include <devices/interfaces/OaqmVolatileOrganicCompoundsProvider.h>

namespace OaqmDevices {
    class MP503 : public OaqmVolatileOrganicCompoundsProvider {
        MP503() : OaqmVolatileOrganicCompoundsProvider() {};
        virtual ~MP503() {};

        virtual void setup() override;
        virtual void update() override;
        virtual void reset() override {};
        virtual void stop() override {};

        virtual inline const char* getName() override {
        return "MP503";
    };
    };
};