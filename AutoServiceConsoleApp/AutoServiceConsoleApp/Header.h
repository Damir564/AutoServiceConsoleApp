#pragma once
bool drawLogo(map_t& settingsMap);
bool changeLogo(map_t& settingsMap);
void onExitCommand();
bool getSettings(map_t& settingsMap);
bool printHelp();
bool startProgram(ProgramInfo& progInfo);

bool getEmployees(vectorPair_t& employeesList);
bool printEmployees(vectorPair_t& employeesList);
bool addEmployee(vectorPair_t& employeesList);
bool removeEmployee(vectorPair_t& employeesList);

bool getHistory(vectorPair_t& historyList, long long& earnings);
bool addHistory(vectorPair_t& employeesList);
bool printHistory(vectorPair_t& historyList);
bool printEarnings(long long& earnings);

template <typename T>
void userInputHandler(T & arg);

namespace arguments
{
	string username;
}

