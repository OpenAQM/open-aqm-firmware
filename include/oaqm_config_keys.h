#ifndef OAQM_CONFIG_TYPES_H
#define OAQM_CONFIG_TYPES_H

#include <vector>
#include <WString.h>

#include <stdexcept>

#include "oaqm_config.h"

// Forward declarations: All OaqmConfigKey types
class OaqmConfigKeyString;
class OaqmConfigKeyPassword;
class OaqmConfigKeyDropDown;
class OaqmConfigKeyUnsignedLong;
class OaqmConfigKeyInt;
class OaqmConfigKeyShort;
class OaqmConfigKeyBool;
class OaqmConfigKeyDouble;
class OaqmConfigKeyFloat;
class OaqmConfigKeyRGB;

// All externally accessible keys are listed here (add them to oaqm_config_keys.cpp oaqmConfigKeys for config ui)
namespace OaqmConfigAllKeys {
#ifdef OAQM_FEATURE_WIFI
extern OaqmConfigKeyString hostname;
extern OaqmConfigKeyBool hostPasswordEnabled;
extern OaqmConfigKeyPassword hostPass;
#ifdef OAQM_FEATURE_WIFI_ONBOOT
extern OaqmConfigKeyBool wifiBootEnabled;
#endif
extern OaqmConfigKeyBool wifiAlwaysNTPEnabled;
extern OaqmConfigKeyBool wifiAutoAP;
extern OaqmConfigKeyString wifiSsid;
extern OaqmConfigKeyPassword wifiPass;
extern OaqmConfigKeyString fallbackWifiSsid1st;
extern OaqmConfigKeyPassword fallbackWifiPass1st;
extern OaqmConfigKeyString fallbackWifiSsid2nd;
extern OaqmConfigKeyPassword fallbackWifiPass2nd;
#endif
// extern OaqmConfigKeyRGB themeBackgroundColor;
// extern OaqmConfigKeyRGB themeBackgroundDimmedColor;
// extern OaqmConfigKeyRGB themeForegroundColor;
// extern OaqmConfigKeyRGB themeForegroundDimmedColor;
// extern OaqmConfigKeyRGB themePrimaryColor;
// extern OaqmConfigKeyRGB themeInfoColor;
// extern OaqmConfigKeyRGB themeSuccessColor;
// extern OaqmConfigKeyRGB themeWarningColor;
// extern OaqmConfigKeyRGB themeDangerColor;
extern OaqmConfigKeyShort oaqmAppV2ButtonDoublePress;
extern OaqmConfigKeyShort oaqmAppV2ButtonLongPress;
extern OaqmConfigKeyShort oaqmAppV2ButtonVeryLongPress;
extern OaqmConfigKeyShort settingDisplayTimeout;
extern OaqmConfigKeyShort settingDisplayBrightness;
extern OaqmConfigKeyBool settingDisplayOverlays;
extern OaqmConfigKeyBool settingDisplayOverlaysForced;
extern OaqmConfigKeyBool settingDisplayDualHourTick;
extern OaqmConfigKeyBool raiseToWakeEnabled;
extern OaqmConfigKeyShort raiseToWakeSensitivity;
extern OaqmConfigKeyBool tapToWakeEnabled;
extern OaqmConfigKeyBool lightSleepEnabled;
extern OaqmConfigKeyBool buttonToWakeEnabled;
extern OaqmConfigKeyDropDown dateFormat;
extern OaqmConfigKeyBool timeFormat;
extern OaqmConfigKeyString timezonePrimary;
extern OaqmConfigKeyString timezoneSecondary;
extern OaqmConfigKeyShort resetDay;
extern OaqmConfigKeyDropDown settingDisplayDefaultWatchface;
#ifdef OAQM_FEATURE_WEATHER
extern OaqmConfigKeyString weatherApiKey;
extern OaqmConfigKeyString weatherLocation1;
extern OaqmConfigKeyString weatherState1;
#endif
}  // namespace OaqmConfigAllKeys

/**
 * @brief This enum holds all known type-ids of the web interface
 *
 */
enum class OaqmConfigKeyTypedUIType: char {
    STRING = 'S',
    PASSWORD = 'P',
    DROPDOWN = 'd',
    ULONG = 'L',
    INT = 'I',
    SHORT = 'i',
    RGB = 'R',
    BOOL = 'C',
    DOUBLE = 'D',
    FLOAT = 'F'
};

/**
 * Config key interface - this enforces the key must
 * be serializeale from and to Strings (used for the data.json)
 * for the configuration UI and also holds all accessible
 * metadata for displaying it.
 */
class OaqmConfigKey {
  public:
    OaqmConfigKey(const OaqmConfigKeyTypedUIType& cType, const char* id, const char* section, const char* label, const char* help)
        : id(id), section(section), label(label), help(help), type(cType) {}
    virtual const String toString() const = 0;
    virtual const String toDefaultString() const = 0;
    virtual void fromString(const char* from) = 0;
    const char* id;
    const char* section;
    const char* label;
    const char* help;
    const OaqmConfigKeyTypedUIType type;

  protected:
    virtual void loadValueFromNVS() = 0;
    friend OaqmConfig;
};

// This holds a reference to all compiled config keys, so we can e.g. iterate over them
extern const unsigned char oaqmConfigKeysCount;
extern OaqmConfigKey* oaqmConfigKeys[];

/**
 * This is a typed config key, this enforces any implementing key
 * must have a default and respective getter and setters.
 */
template <typename T>
class OaqmConfigKeyTyped : public OaqmConfigKey {
  public:
    OaqmConfigKeyTyped(const OaqmConfigKeyTypedUIType& configUiType, const char* id, const char* section, const char* label, const char* help,
                      const T def)
        : OaqmConfigKey(configUiType, id, section, label, help), def(def) {
        // Nothing in here
    }
    const T def;
    T val;  // This is a cached value to reduce the reading of the nvs during e.g. rendering
    virtual const T get() const {
        return this->val;
    };
    virtual void set(const T& var) {
        this->val = var;
    };
};

/**
 * A typed config key implementation for loading & storing strings -> string
 * This key type is NOT cached. Do NOT call this periodically!
 */
class OaqmConfigKeyString : public OaqmConfigKeyTyped<String> {
  public:
    OaqmConfigKeyString(const char* id, const char* section, const char* label, const char* help, const String& def)
        : OaqmConfigKeyTyped(OaqmConfigKeyTypedUIType::STRING, id, section, label, help, String(def)) {}
    const String toDefaultString() const {
        return this->def;
    }
    const String get() const {
        OAQM_LOG_D("Loading string from nvs: ", this->id); // Log to annoy devs to use some caching
        return OaqmConfig::getInstance()->prefs.getString(this->id, this->def);
    };
    void set(const String& var) {
        if(OaqmConfig::getInstance()->readOnly) return;
        OaqmConfig::getInstance()->prefs.putString(this->id, var);
    }
    const String toString() const {
        return this->get();
    }
    void fromString(const char* from) {
        this->set(String(from));
    }
    void loadValueFromNVS() {/* Ignored */};
};

/**
 * A typed config key implementation for loading & storing strings as passwords -> input:password
 * This key type is NOT cached. Do NOT call this periodically!
 */
class OaqmConfigKeyPassword : public OaqmConfigKeyTyped<String> {
  public:
    OaqmConfigKeyPassword(const char* id, const char* section, const char* label, const char* help, const String& def)
        : OaqmConfigKeyTyped(OaqmConfigKeyTypedUIType::PASSWORD, id, section, label, help, String(def)) {}
    const String toDefaultString() const {
        return this->def;
    }
    const String get() const {
        OAQM_LOG_D("Loading password from nvs: ", this->id); // Log to annoy devs to use some caching
        return OaqmConfig::getInstance()->prefs.getString(this->id, this->def);
    };
    void set(const String& var) {
        if(OaqmConfig::getInstance()->readOnly) return;
        OaqmConfig::getInstance()->prefs.putString(this->id, var);
    }
    const String toString() const {
        return this->get();
    }
    void fromString(const char* from) {
        this->set(String(from));
    }
    void loadValueFromNVS() {/* Ignored */};
};

/**
 * A typed config key implementation for loading & storing strings as a drop down list -> string
 * This key type is NOT cached. Do NOT call this periodically!
 */
class OaqmConfigKeyDropDown : public OaqmConfigKeyTyped<String> {
  public:
    OaqmConfigKeyDropDown(const char* id, const char* section, const char* label, std::vector<const char*> options, size_t defaultOptionIndex) :
        OaqmConfigKeyTyped(OaqmConfigKeyTypedUIType::DROPDOWN, id, section, label, nullptr, String(options.at(defaultOptionIndex))) {
        this->setOptions(options);
    }
    OaqmConfigKeyDropDown(const char* id, const char* section, const char* label, std::vector<const char*> options, const String& def) :
        OaqmConfigKeyDropDown(id, section, label, options, this->getOptionIndex(options, def)) {}

    const String toDefaultString() const {
        return this->def;
    }
    const String get() const {
        OAQM_LOG_D("Loading drop-down from nvs: ", this->id); // Log to annoy devs to use some caching
        return OaqmConfig::getInstance()->prefs.getString(this->id, this->def);
    }
    void set(const String& var) {
        this->checkValidOption(var);
        if(OaqmConfig::getInstance()->readOnly) return;
        OaqmConfig::getInstance()->prefs.putString(this->id, var);
    }
    const String toString() const {
        return this->get();
    }
    void fromString(const char* from) {
        this->set(String(from));
    }
    void loadValueFromNVS() {/* Ignored */};

    std::vector<const char*> getOptions() const {
        return this->options;
    }
  private:
    std::vector<const char*> options;
    std::string optionsStr; // Used as cache reference for the c_str() call by setOptions

    static size_t getOptionIndex(const std::vector<const char*>& options, const String& option) {
        for (size_t i = 0; i < options.size(); i++) {
            if (option == options.at(i))
                return i;
        }
        throw std::invalid_argument("Option not found in options list");
    }

    void setOptions(const std::vector<const char*>& options) {
        this->options = options;
        this->optionsStr.clear();
        for(auto it = this->options.begin(); it != this->options.end(); ++it) {
            this->optionsStr.append(*it);
            if(std::next(it) != this->options.end())
                this->optionsStr.append(",");
        }
        this->help = this->optionsStr.c_str();
    }

    void checkValidOption(const String& val) {
        // Check if var is in the list of options
        for(auto it = this->options.begin(); it != this->options.end(); ++it) {
            if (val == *it)
                return;
        }
        // If we reach this line, the value was not valid!
        throw std::invalid_argument("Invalid option value for dropdown key!");
    }
};

/**
 * A typed config key implementation for loading & storing unsigned longs -> input:number
 */
class OaqmConfigKeyUnsignedLong : public OaqmConfigKeyTyped<unsigned long> {
  public:
    OaqmConfigKeyUnsignedLong(const char* id, const char* section, const char* label, const char* help,
                             const unsigned long& def)
        : OaqmConfigKeyTyped(OaqmConfigKeyTypedUIType::ULONG, id, section, label, help, def) {}
    const String toDefaultString() const {
        return String(this->def);
    }
    void set(const unsigned long& var) {
        if(OaqmConfig::getInstance()->readOnly or this->val == var) return;
        OaqmConfigKeyTyped::set(var);
        OaqmConfig::getInstance()->prefs.putULong(this->id, var);
    }
    const String toString() const {
        return String(this->get());
    }
    void fromString(const char* from) {
        this->set(String(from).toInt());
    }
    void loadValueFromNVS() {
        this->val = OaqmConfig::getInstance()->prefs.getULong(this->id, this->def);
    };
};

/**
 * A typed config key implementation for loading & storing ints -> input:number
 */
class OaqmConfigKeyInt : public OaqmConfigKeyTyped<int> {
  public:
    OaqmConfigKeyInt(const char* id, const char* section, const char* label, const char* help, const int& def)
        : OaqmConfigKeyTyped(OaqmConfigKeyTypedUIType::INT, id, section, label, help, def) {}
    const String toDefaultString() const {
        return String(this->def);
    }
    void set(const int& var) {
        if(OaqmConfig::getInstance()->readOnly or this->val == var) return;
        OaqmConfigKeyTyped::set(var);
        OaqmConfig::getInstance()->prefs.putInt(this->id, var);
    }
    const String toString() const {
        return String(this->get());
    }
    void fromString(const char* from) {
        this->set(String(from).toInt());
    }
    void loadValueFromNVS() {
        this->val = OaqmConfig::getInstance()->prefs.getInt(this->id, this->def);
    };
};

/**
 * A typed config key implementation for loading & storing shorts -> input:number
 */
class OaqmConfigKeyShort : public OaqmConfigKeyTyped<short> {
  public:
    OaqmConfigKeyShort(const char* id, const char* section, const char* label, const char* help, const short& def)
        : OaqmConfigKeyTyped(OaqmConfigKeyTypedUIType::SHORT, id, section, label, help, def) {}
    const String toDefaultString() const {
        return String(this->def);
    }
    void set(const short& var) {
        if(OaqmConfig::getInstance()->readOnly or this->val == var) return;
        OaqmConfigKeyTyped::set(var);
        OaqmConfig::getInstance()->prefs.putShort(this->id, var);
    }
    const String toString() const {
        return String(this->get());
    }
    void fromString(const char* from) {
        this->set(String(from).toInt());
    }
    void loadValueFromNVS() {
        this->val = OaqmConfig::getInstance()->prefs.getShort(this->id, this->def);
    };
};

/**
 * A typed config key implementation for loading & storing rgb888 values -> HTML5 ColorPicker
 */
// class OaqmConfigKeyRGB : public OaqmConfigKeyTyped<uint32_t> {
//   public:
//     OaqmConfigKeyRGB(const char* id, const char* section, const char* label, const char* help, const uint32_t& def)
//         : OaqmConfigKeyTyped(OaqmConfigKeyTypedUIType::RGB, id, section, label, help, def) {}
//     const String toDefaultString() const {
//         return String(this->def);
//     }
//     void set(const uint32_t& var) {
//         if(OaqmConfig::getInstance()->readOnly or this->val == var) return;
//         OaqmConfigKeyTyped::set(var);
//         OaqmConfig::getInstance()->prefs.putUInt(this->id, var);
//     }
//     const String toString() const {
//         return "#" + String(this->get(), HEX);
//     }
//     void fromString(const char* from) {
//         if(strlen(from) > 2)
//             from += 1; // skip the leading #
//         this->set((uint32_t)(strtol(from, NULL, 16))); // parse the hex-string to a number
//     }
//     void loadValueFromNVS() {
//         this->val = OaqmConfig::getInstance()->prefs.getUInt(this->id, this->def);
//     };
// };

/**
 * A typed config key implementation for loading & storing bools -> input:checkbox
 */
class OaqmConfigKeyBool : public OaqmConfigKeyTyped<bool> {
  public:
    OaqmConfigKeyBool(const char* id, const char* section, const char* label, const char* help, const bool& def)
        : OaqmConfigKeyTyped(OaqmConfigKeyTypedUIType::BOOL, id, section, label, help, def) {}
    const String toDefaultString() const {
        return String(this->def);
    }
    void set(const bool& var) {
        if(OaqmConfig::getInstance()->readOnly or this->val == var) return;
        OaqmConfigKeyTyped::set(var);
        OaqmConfig::getInstance()->prefs.putBool(this->id, var);
    }
    const String toString() const {
        return this->get() ? "true" : "false";
    }
    void fromString(const char* from) {
        this->set(String(from) == "true");
    }
    void loadValueFromNVS() {
        this->val = OaqmConfig::getInstance()->prefs.getBool(this->id, this->def);
    };
};

/**
 * A typed config key implementation for loading & storing doubles -> input:number
 */
class OaqmConfigKeyDouble : public OaqmConfigKeyTyped<double> {
  public:
    OaqmConfigKeyDouble(const char* id, const char* section, const char* label, const char* help, const double& def)
        : OaqmConfigKeyTyped(OaqmConfigKeyTypedUIType::DOUBLE, id, section, label, help, def) {}
    const String toDefaultString() const {
        return String(this->def);
    }
    void set(const double& var) {
        if(OaqmConfig::getInstance()->readOnly or this->val == var) return;
        OaqmConfigKeyTyped::set(var);
        OaqmConfig::getInstance()->prefs.putDouble(this->id, var);
    }
    const String toString() const {
        return String(this->get());
    }
    void fromString(const char* from) {
        this->set(String(from).toDouble());
    }
    void loadValueFromNVS() {
        this->val = OaqmConfig::getInstance()->prefs.getDouble(this->id, this->def);
    };
};

/**
 * A typed config key implementation for loading & storing floats -> input:number
 */
class OaqmConfigKeyFloat : public OaqmConfigKeyTyped<float> {
  public:
    OaqmConfigKeyFloat(const char* id, const char* section, const char* label, const char* help, const float& def)
        : OaqmConfigKeyTyped(OaqmConfigKeyTypedUIType::FLOAT, id, section, label, help, def) {}
    const String toDefaultString() const {
        return String(this->def);
    }
    void set(const float& var) {
        if(OaqmConfig::getInstance()->readOnly or this->val == var) return;
        OaqmConfigKeyTyped::set(var);
        OaqmConfig::getInstance()->prefs.putFloat(this->id, var);
    }
    const String toString() const {
        return String(this->get());
    }
    void fromString(const char* from) {
        this->set(String(from).toFloat());
    }
    void loadValueFromNVS() {
        this->val = OaqmConfig::getInstance()->prefs.getFloat(this->id, this->def);
    };
};

#endif