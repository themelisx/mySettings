#ifndef SETTINGS_h
#define SETTINGS_h
#include <Arduino.h>

#include <Preferences.h>

extern MyDebug *myDebug;

class MySettings {
private:
    Preferences prefs;
    bool active;
    String namespaceName;

    bool checkActive();
public:
    MySettings();

    bool start(const char* ns = "app");
    void end();

    // ----- WRITE -----
    void writeByte(const char* key, byte value);
    void writeInt(const char* key, int value);
    void writeFloat(const char* key, float value);
    void writeString(const char* key, const String& value);
    void writeBool(const char* key, bool value);

    // ----- READ -----
    byte readByte(const char* key, byte defaultValue = 0);
    int readInt(const char* key, int defaultValue = 0);
    float readFloat(const char* key, float defaultValue = 0.0);
    String readString(const char* key, const String& defaultValue = "");
    bool readBool(const char* key, bool defaultValue = false);

    // ----- MANAGEMENT -----
    void removeKey(const char* key);
    void clearAll();


};
#endif