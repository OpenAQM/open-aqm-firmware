#ifndef OAQM_HAL_H
#define OAQM_HAL_H

#include <memory>
#include <list>
#include <optional>

#include <Arduino.h>
#include <Wire.h>
#include <Preferences.h>
#include "hal/oaqm_filesystem.h"
#include "hal/button.h"
#include <devices/interfaces/OaqmTimeProvider.h>
#include "oaqm_config_keys.h"
#include "oaqm_pins.h"

class OaqmHal {
  public:
    static OaqmHal* getInstance();
    static void resetInstance();

    class Devices;
    Devices* devices() const {
        return this->_devices.get();
    };

#if OAQM_PLATFORM_ENVIRONMENT == 1
    class Environment;
    Environment* environment() const {
        return this->_environment.get();
    };
#endif


    class WakeUpConfig final {
      public:
        time_t time = 0;
        // WARNING: These pointers must still be valid e.g. AFTER a deep sleep!
        void (*selected)(void) = nullptr;
        void (*used)(void) = nullptr;
        void (*expired)(void) = nullptr;
      protected:
        size_t id = 0;
        friend class OaqmHal;
    };

    // Setup
    void setup(bool fromLightSleep);
    void setupFileSystem(void);
    void setupButtons(void);
    void setupDisplay();
    void setupPower(bool fromLightSleep);

    // Stop
    void stop(bool toLightSleep);
    void stopPower();

    // Buttons (Engine-Style)
    void checkButtons();
    bool btnIsDown(Button btn);
    unsigned long btnIsDownFor(Button btn);
    unsigned long btnIsDownSince(Button btn);
    bool btnHasGoneUp(Button btn);
    bool btnHasGoneDown(Button btn);
    void clearButtonState(Button btn);
    bool btnIsTopAligned(Button btn);
    bool btnIsLeftAligned(Button btn);
    void getButtonCoordinates(Button btn, int16_t& x, int16_t& y);

    // DEPRECATED button methods, use OaqmAppV2::onButton instead
    bool btnIsDoubleClick(Button btn);
    bool btnIsLongPress(Button btn);
    void suppressButtonUntilUp(Button btn);

    // Display
    void setBrightness(uint8_t b, bool storeToNVS = true);
    void increaseBrightness(uint8_t v);
    void decreaseBrightness(uint8_t v);
    void displayOff();
    void displayOn();
    void requestDisableDisplayBuffer();
    void requestEnableDisplayBuffer();
    void disableDisplayBuffer();
    void enableDisplayBuffer();
    bool displayBufferEnabled();
    unsigned long screenOnTime();
    unsigned long screenOffTime();

    /**
     * @brief Get the screen brightness from 0 to 255.
     *
     * @param bool checkHardware If true, we check the brightness on the hardware before return it.
     * @return uint8_t
     */
    uint8_t screenBrightness(bool checkHardware = false);

    // Arduino_Canvas_Graphics2D* getCanvas(void);
    // Graphics2DPrint* gfx();
    // void flushCanvas();
    // void loadPNGfromProgmem(Graphics2D* target, const unsigned char* array, unsigned int length);

    // Power
    bool isCharging(void);
    uint16_t getBatteryRaw(const uint16_t numAvg = 8);
    // float getBatteryVoltage(void);
    void updatePowerStatistics(uint16_t currBattery);
    uint8_t getBatteryPercent();
    void setCPUClock(uint8_t mhz);
    uint8_t getCPUClock();
    void deepSleep();
    void lightSleep();
    void handleWakeupFromLightSleep();
    void noteUserInteraction();
    void handleDisplayTimout();

    // Power: WakeUpConfigs
    size_t addWakeUpConfig(const WakeUpConfig& config);
    void removeWakeUpConfig(size_t configId);

    // General time stuff
    void updateTimeProvider();
    void updateTimezoneOffsets();

    // UTC Time
    void setUTCTime(const time_t& epoch);
    time_t getUTCTime();
    void getUTCTime(uint32_t* hour, uint32_t* minute, uint32_t* second);

    // Offset getters for primary / secondary time (cached!)
    time_t getTimezoneOffsetPrimary();
    time_t getTimezoneOffsetSecondary();

    // New time functions with offset
    time_t getTime(time_t& offset);
    void getTime(time_t& offset, uint32_t* hour, uint32_t* minute, uint32_t* second, bool* afterNoon = nullptr);
    void getDate(time_t& offset, uint32_t* day, uint32_t* weekDay);
    void getDate(time_t& offset, uint32_t* day, uint32_t* month, uint32_t* year);
    const char* getWeekday(time_t& offset, uint32_t* setWDay = nullptr);

    // For backward compatibility: Local time functions (= primary timezone)
    inline void getLocalTime(uint32_t* hour, uint32_t* minute, uint32_t* second, bool* afterNoon = nullptr) {
        this->getTime(this->timezoneOffsetPrimary, hour, minute, second, afterNoon);
    }
    inline uint32_t getLocalTime() {
        return this->getTime(this->timezoneOffsetPrimary);
    }
    inline void getLocalDate(uint32_t* day, uint32_t* weekDay) {
        this->getDate(this->timezoneOffsetPrimary, day, weekDay);
    };
    inline void getLocalDate(uint32_t* day, uint32_t* month, uint32_t* year) {
        this->getDate(this->timezoneOffsetPrimary, day, month, year);
    };
    inline const char* getLocalWeekday(uint32_t* sWDay = nullptr) {
        return this->getWeekday(this->timezoneOffsetPrimary, sWDay);
    };

    // For backward compatibility: Dual time functions (= secondary timezone)
    inline void getDualTime(uint32_t* hour, uint32_t* minute, uint32_t* second, bool* afterNoon = nullptr) {
        this->getTime(this->timezoneOffsetSecondary, hour, minute, second, afterNoon);
    }
    inline uint32_t getDualTime() {
        return this->getTime(this->timezoneOffsetSecondary);
    }
    inline void getDualDate(uint32_t* day, uint32_t* weekDay) {
        this->getDate(this->timezoneOffsetSecondary, day, weekDay);
    };
    inline void getDualDate(uint32_t* day, uint32_t* month, uint32_t* year) {
        this->getDate(this->timezoneOffsetSecondary, day, month, year);
    };
    inline const char* getDualWeekday(uint32_t* sWDay = nullptr) {
        return this->getWeekday(this->timezoneOffsetSecondary, sWDay);
    };

    bool _requestDisableBuffer = false;
    bool _requestEnableBuffer = false;

  private:
    //Arduino_Canvas_Graphics2D* canvas = nullptr;

    static OaqmHal* instance;
    OaqmTimeProvider* timeProvider = nullptr;
    unsigned long _screenOnSince = 0;
    unsigned long _screenOffSince = 0;
    unsigned long _lastUserInteraction = 0;

    // array of available buttons for iteration (e.g. handling)
    int _count[BTN_NUMBER];
    int _count2[BTN_NUMBER];
    bool _btnLastState[BTN_NUMBER];
    bool _btnIsDown[BTN_NUMBER];
    bool _btnGoneUp[BTN_NUMBER];
    bool _btnSuppressUntilUpAgain[BTN_NUMBER];
    bool _btnGoneDown[BTN_NUMBER];
    unsigned long _btnIsDownMillis[BTN_NUMBER];
    unsigned long _btnIsUpMillis[BTN_NUMBER];
    bool _btnDoubleClickTimeout[BTN_NUMBER];
    bool _btnClicked[BTN_NUMBER];
    bool _btnLongPress[BTN_NUMBER]; 
    bool _btnShutdown[BTN_NUMBER];
    unsigned long _btnDoubleClickMillis[BTN_NUMBER];
    bool _btnDoubleClick[BTN_NUMBER];
    uint8_t _btnDetectDoubleClickCount[BTN_NUMBER];
    bool _btnLongPress[BTN_NUMBER];

    uint8_t _brightness = 0;
    bool _hasGPS = false;
    bool _debugGPS = false;
    bool _isLightSleep = false;

    time_t timezoneOffsetPrimary = 0;
    time_t timezoneOffsetSecondary = 0;

    Preferences powerPreferences;
    FileSystemHal* fileSystem;

    std::unique_ptr<Devices> _devices = nullptr;
#if OAQM_PLATFORM_ENVIRONMENT == 1
    std::unique_ptr<Environment> _environment = nullptr;
#endif

    std::list<WakeUpConfig> _wakeUpConfigs;
    WakeUpConfig* _lightSleepWakeUpConfig = nullptr;
    size_t _wakeUpConfigIdCounter = 0;
    std::mutex _wakeUpConfigsMutex;

    OaqmHal(FileSystemHal* fs);
    ~OaqmHal();
    void doSleep(bool deepSleep);
    uint16_t getBatteryRawMin();
    uint16_t getBatteryRawMax();
    void expireWakeUpConfigs();
    WakeUpConfig* selectWakeUpConfig();
    void persistWakeUpConfig(OaqmHal::WakeUpConfig* config, bool toLightSleep);
    //std::optional<WakeUpConfig> readAndResetWakeUpConfig(bool fromLightSleep);
    void resetWakeUpConfig(bool useLightSleep);
};

#endif

#include "hal/devices.h"
#include "hal/environment.h"