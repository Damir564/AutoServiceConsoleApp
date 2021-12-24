#pragma once
bool drawLogo(map_t& settingsMap);
bool changeLogo(map_t& settingsMap);
void onExitCommand();
bool getSettings(map_t& settingsMap);
bool getEmployees(vectorPair_t& employeesList);
bool printEmployees(vectorPair_t& employeesList);
bool addEmployee(vectorPair_t& employeesList);
bool printHelp();
bool clearScreen();

template <typename T>
void userInputHandler(T & arg);

