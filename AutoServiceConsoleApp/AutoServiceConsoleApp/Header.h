#pragma once
void clearScreen();
bool drawLogo(int numberOfFile);
bool changeLogo();
bool getSettings();

template <typename T>
void userInputHandler(T & arg);

namespace settings
{
	int logoNumber;
}
