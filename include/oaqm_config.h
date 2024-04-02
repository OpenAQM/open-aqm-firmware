#ifndef OAQM_CONFIG_H
#define OAQM_CONFIG_H

#ifdef OAQM_EMULATOR
#include <FakeMe.h> // Only used for Serial.*
#endif
#include <Preferences.h>

#include <OaqmLogger.h>
#include "config_defaults.h"

/**
 * This is basically a wrapper for the ESP32 lib Preferences.h -
 * it extends it by the functionality to ensure the nvs is using
 * the correct version (see class const); if not the config will
 * be reset on loading.
 * Please see the private variables for any reserved key names.
 * DO NOT TRY TO (OVER)WRITE THEM.
 */

class OaqmConfigKeyString;
class OaqmConfigKeyPassword;
class OaqmConfigKeyDropDown;
class OaqmConfigKeyUnsignedLong;
class OaqmConfigKeyInt;
class OaqmConfigKeyShort;
//class OaqmConfigKeyRGB;
class OaqmConfigKeyBool;
class OaqmConfigKeyDouble;
class OaqmConfigKeyFloat;

class OaqmConfig {
  public:
    const char* configNamespace = "oaqm-config";
    const char* configVersionKey = "ver";  // RESERVED KEY NAME - also do not use "v", as it is maybe already used.
    const short configVersionValue = 2;    // Change this when you want to clean the config on next boot
    const char* configBootCntKey = "bct";  // RESERVED KEY NAME

    static OaqmConfig* getInstance();
    static void resetInstance();

    void setup();
    void reset(bool clearWholeNVS);
    void enableWrite();
    void disableWrite();
    int getBootCount();
    String getCategoriesJson();
    String getFieldJson(String id);
    void setField(String id, String value);
    void notifyChange();
  protected:
    Preferences prefs; // for the config keys accessible
    bool readOnly = true; // explicit variable, as Preferences does not have a "read only" mode, which can be controlled without a end/begin call again
    ~OaqmConfig();

    friend std::unique_ptr<OaqmConfig>::deleter_type;
    friend OaqmConfigKeyString;
    friend OaqmConfigKeyPassword;
    friend OaqmConfigKeyDropDown;
    friend OaqmConfigKeyUnsignedLong;
    friend OaqmConfigKeyInt;
    friend OaqmConfigKeyShort;
    //friend OaqmConfigKeyRGB;
    friend OaqmConfigKeyBool;
    friend OaqmConfigKeyDouble;
    friend OaqmConfigKeyFloat;
  private:
    static std::unique_ptr<OaqmConfig> instance;

    OaqmConfig();
    void loadAllKeysFromNVS();
};

#endif