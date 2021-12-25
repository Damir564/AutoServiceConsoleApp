#pragma once
bool drawLogo(map_t& settingsMap);
bool changeLogo(map_t& settingsMap);
void onExitCommand();
bool getSettings(map_t& settingsMap);
bool printHelp();
bool clearScreen();

bool getEmployees(vectorPair_t& employeesList);
bool printEmployees(vectorPair_t& employeesList);
bool addEmployee(vectorPair_t& employeesList);
bool removeEmployee(vectorPair_t& employeesList);

bool getHistory();

template <typename T>
void userInputHandler(T & arg);
