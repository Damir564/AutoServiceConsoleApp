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
    CHANGELOGO = 9,
    EXIT = 10
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


    int currentCommand;
    bool commandState = true;
    do
    {
        cout << "Введите Команду:" << endl;
        cin >> currentCommand;
        switch (currentCommand)
        {
        case CHANGELOGO:
            commandState = changeLogo(0);
            break;
        default:
            break;
        }
        if (!commandState)
        {
            system("pause");
            return -1;
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
        cout << "Файл Логотипа не найден" << endl;

        return false;
    }
    cout << logoFile.rdbuf() << endl;

    logoFile.close();
    return true;
}

bool changeLogo(int numberOfFile)
{
    string lines[100];
    string param;
    int value;
    int k, i;
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
    lines[k] = lines[k].insert(lines[k].find(' ') + 1, to_string(numberOfFile));
    settingsFile.clear();
    settingsFile.seekp(0);
    for (int j = 0; j != i; ++j)
    {
        settingsFile << lines[j] << endl;
    }

    settingsFile.close();
    return true;
}

void clearScreen()
{
    cout << string(100, '\n');
}

