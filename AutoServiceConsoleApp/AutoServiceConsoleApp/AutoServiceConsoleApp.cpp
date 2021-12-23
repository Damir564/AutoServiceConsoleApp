#include "Header.h"

#include <iostream>
#include <fstream>
#include <string>
#include <locale>

using namespace std;

enum COMMANDS {
    EMPLOYEES,
    PARTS,
    PRICELIST,
    CHANGELOGO = 7,
    HELP = 8,
    RESTART = 9,
    EXIT = 0
};

int main()
{
    setlocale(LC_ALL, "RU");

    if (!getSettings())
    {
        system("pause");
        return -1;
    }
    
    if (!drawLogo(settings::logoNumber))
    {
        system("pause");
        return -1;
    }


    int currentCommand = 0;
    bool commandState = true;
    do
    {
        if (!commandState)
        {
            system("pause");
            return -1;
        }
        cout << "������� �������:" << endl;
        userInputHandler<>(currentCommand);
        switch (currentCommand)
        {
        case CHANGELOGO:
            commandState = changeLogo();
            break;
        case RESTART:
            commandState = clearScreen();
            break;
        default:
            break;
        }
    } while (currentCommand != EXIT);

    system("pause");
    return 0;
}

bool getSettings()
{
    settings::logoNumber = 0;

    string param;
    int value;
    ifstream settingsFile("..\\Debug\\settings.txt");
    if (!settingsFile.is_open())
    {
        return false;
    }
    while (settingsFile >> param >> value)
    {
        if (param == "logoNumber")
            settings::logoNumber = value;
    }
    settingsFile.close();
    return true;
}

bool drawLogo(int numberOfile)
{
    const string PATHS[2] = { "..\\Debug\\logo.txt" , "..\\Debug\\logo2.txt" };
    ifstream logoFile(PATHS[numberOfile]);
    if (!logoFile.is_open())
    {
        cout << "���� �������� �� ������" << endl;

        return false;
    }
    cout << logoFile.rdbuf() << endl;

    logoFile.close();
    return true;
}

bool changeLogo()
{
    int currentParam;
    cout  << "�������� �������:\n\t1 - �����\n\t2 - ������\n0 - ��������� �����" << endl;
    do
    {
        userInputHandler<>(currentParam);
        if (!currentParam)
        {
            onExitCommand();
            return true;
        }
    } while (currentParam != 1 && currentParam != 2);
    currentParam -= 1;
    settings::logoNumber = currentParam;
    string lines[100];
    string param;
    int value;
    int k = -1, i;
    fstream settingsFile("..\\Debug\\settings.txt");
    if (!settingsFile.is_open())
    {
        return false;
    }
    for (i = 0; settingsFile >> param >> value; ++i)
    {
        if (param == "logoNumber")
            k = i;
        lines[i] = param + " " + to_string(value);
    }
    
    lines[k] = lines[k].erase(lines[k].find(' ') + 1, lines[k].length() - lines[k].find(' ') - 1);
    lines[k] = lines[k].insert(lines[k].find(' ') + 1, to_string(currentParam));
    settingsFile.clear();
    settingsFile.seekp(0);
    for (int j = 0; j != i; ++j)
    {
        settingsFile << lines[j] << endl;
    }

    settingsFile.close();
    return true;
}

template <typename T>
void userInputHandler(T & arg)
{
    cout << "���� >> ";
    cin >> arg;
}

void onExitCommand()
{
    cout << "<����������� �������>" << endl;
}

bool clearScreen()
{
    system("cls");
    drawLogo(settings::logoNumber);
    
    return true;
    //cout << string(100, '\n');
}

