#pragma once
bool drawLogo(int numberOfFile);
bool changeLogo();
bool getSettings();
void onExitCommand();
bool clearScreen();

template <typename T>
void userInputHandler(T & arg);

namespace settings
{
	int logoNumber;
}
