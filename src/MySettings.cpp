#include <Arduino.h>

#include <MyDebug.h>

#include <Preferences.h>
#include "mySettings.h"

MySettings::MySettings() {    
    myDebug->println(DEBUG_LEVEL_DEBUG, "[Settings]");
    active = false;
}

bool MySettings::start(const char* ns) {
    namespaceName = ns;
    active = prefs.begin(namespaceName.c_str(), false); // read/write mode
    if (active) {
        myDebug->println(DEBUG_LEVEL_DEBUG, "Settings started with namespace: %s", namespaceName.c_str());
    } else {
        myDebug->println(DEBUG_LEVEL_DEBUG, "Failed to start Preferences");
    }
    return active;
}

void MySettings::end() {
    prefs.end();
    active = false;
}

// ----- WRITE -----
void MySettings::writeByte(const char* key, byte value) {
    if (checkActive()) prefs.putUChar(key, value);
}

void MySettings::writeInt(const char* key, int value) {
    if (checkActive()) prefs.putInt(key, value);
}

void MySettings::writeFloat(const char* key, float value) {
    if (checkActive()) prefs.putFloat(key, value);
}

void MySettings::writeString(const char* key, const String& value) {
    if (checkActive()) prefs.putString(key, value);
}

void MySettings::writeBool(const char* key, bool value) {
    if (checkActive()) prefs.putBool(key, value);
}

// ----- READ -----
byte MySettings::readByte(const char* key, byte defaultValue) {
    return checkActive() ? prefs.getUChar(key, defaultValue) : defaultValue;
}

int MySettings::readInt(const char* key, int defaultValue) {
    return checkActive() ? prefs.getInt(key, defaultValue) : defaultValue;
}

float MySettings::readFloat(const char* key, float defaultValue) {
    return checkActive() ? prefs.getFloat(key, defaultValue) : defaultValue;
}

String MySettings::readString(const char* key, const String& defaultValue) {
    return MySettings::checkActive() ? prefs.getString(key, defaultValue) : defaultValue;
}

bool MySettings::readBool(const char* key, bool defaultValue) {
    return checkActive() ? prefs.getBool(key, defaultValue) : defaultValue;
}

// ----- MANAGEMENT -----
void MySettings::removeKey(const char* key) {
    if (checkActive()) prefs.remove(key);
}

void MySettings::clearAll() {
    if (checkActive()) prefs.clear();
}

bool MySettings::checkActive() {
    if (active) {
        return true;
    } else {
        myDebug->println(DEBUG_LEVEL_ERROR, "[Settings] Preferences not active!");
        return false;
    }    
}
