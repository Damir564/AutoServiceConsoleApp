#pragma once
void clearScreen();
bool drawLogo(int numberOfFile);
bool changeLogo(int numberOfFile);
bool getSettings();

namespace settings
{
	int logoNumber;
}
