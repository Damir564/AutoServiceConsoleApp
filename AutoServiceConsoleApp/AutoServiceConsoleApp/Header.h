#pragma once
bool drawLogo(map_t& settingsMap);
bool changeLogo(map_t& settingsMap);
void onExitCommand();
bool getSettings(map_t& settingsMap);
bool printHelp();
bool clearScreen();

template <typename T>
void userInputHandler(T & arg);

