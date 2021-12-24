#pragma once
bool drawLogo(int numberOfFile);
bool changeLogo();
bool getSettings(int & arg);
void onExitCommand();
bool printHelp();
bool clearScreen();

template <typename T>
void userInputHandler(T & arg);

namespace settings
{
	int logoNumber;
}
