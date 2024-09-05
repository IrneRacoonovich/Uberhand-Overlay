#pragma once

#include "tesla.hpp"

#include <jansson.h>
#include <switch/services/hid.h>

#include <map>
#include <string>
#include <vector>

#define KEY_A HidNpadButton_A
#define KEY_B HidNpadButton_B
#define KEY_X HidNpadButton_X
#define KEY_Y HidNpadButton_Y
#define KEY_L HidNpadButton_L
#define KEY_R HidNpadButton_R
#define KEY_ZL HidNpadButton_ZL
#define KEY_ZR HidNpadButton_ZR
#define KEY_PLUS HidNpadButton_Plus
#define KEY_MINUS HidNpadButton_Minus
#define KEY_DUP HidNpadButton_Up
#define KEY_DDOWN HidNpadButton_Down
#define KEY_DLEFT HidNpadButton_Left
#define KEY_DRIGHT HidNpadButton_Right
#define KEY_SL HidNpadButton_AnySL
#define KEY_SR HidNpadButton_AnySR
#define KEY_LSTICK HidNpadButton_StickL
#define KEY_RSTICK HidNpadButton_StickR
#define KEY_UP (HidNpadButton_Up | HidNpadButton_StickLUp)
#define KEY_DOWN (HidNpadButton_Down | HidNpadButton_StickLDown)
#define KEY_LEFT (HidNpadButton_Left | HidNpadButton_StickLLeft)
#define KEY_RIGHT (HidNpadButton_Right | HidNpadButton_StickLRight)
#define touchPosition const HidTouchState
#define touchInput &touchPos
#define JoystickPosition HidAnalogStickState

// String path variables
const std::string configFileName = "config.ini";
const std::string settingsPath = "sdmc:/config/uberhand/";
const std::string settingsConfigIniPath = settingsPath + configFileName;
const std::string packageDirectory = "sdmc:/switch/.packages/";
const std::string overlayDirectory = "sdmc:/switch/.overlays/";
const std::string teslaSettingsConfigIniPath = "sdmc:/config/tesla/" + configFileName;
const std::string overlaysIniFilePath = settingsPath + "overlays.ini";
const std::string packagesIniFilePath = settingsPath + "packages.ini";
const std::string checkmarkChar = "\uE14B";

extern bool applied;
extern bool deleted;
extern bool resetValue;
extern std::string prevValue;

enum ShiftFocusMode {
    UpNum,
    DownNum,
    UpMax,
    DownMax
};

void scrollListItems(tsl::Gui* gui, ShiftFocusMode mode);

void copyTeslaKeyComboTouberhand();

bool isDangerousCombination(const std::string& patternPath);

struct ThreadArgs {
    bool* exitMT;
    std::vector<std::vector<std::string>> commands;
    tsl::elm::ListItem* listItem;
    int* errCode;
    std::string progress;
};

// Main interpreter
int interpretAndExecuteCommand(const std::vector<std::vector<std::string>>& commands,
                               std::string progress = "",
                               tsl::elm::ListItem* listItem = nullptr);

void MTinterpretAndExecute(void* args);

tsl::PredefinedColors defineColor(const std::string& strColor);

std::pair<std::string, int> dispCustData(const std::string& jsonPath, const std::string& kipPath = "/atmosphere/kips/loader.kip", bool spacing = false);

std::pair<std::string, int> dispRAMTmpl(const std::string& dataPath, const std::string& selectedItem);

bool verifyIntegrity(std::string check);

void removeLastNumericWord(std::string& str);

std::vector<std::string> parseString(const std::string& str, char delimiter);

std::string getVersion(json_t* json);

std::string getLinkOnLatest(json_t* json, int dEntry = 1);

std::map<std::string, std::string> packageUpdateCheck(const std::string& subConfigIniPath);

std::map<std::string, std::string> ovlUpdateCheck(std::map<std::string, std::string> currentOverlay);
