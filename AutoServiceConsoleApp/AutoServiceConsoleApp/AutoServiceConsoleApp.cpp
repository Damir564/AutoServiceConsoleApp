#include "Header.h"

#include <iostream>
#include <fstream>
#include <string>
#include <locale>

using namespace std;

enum COMMANDS {
    EMPLOYEES = 1,
    ADDEMPLOYEE = 2,
    REMOVEEMPLOYEE = 3,
    PRICELIST,
    CHANGELOGO = 7,
    HELP = 8,
    RESTART = 9,
    EXIT = 0
};

int main()
{
    setlocale(LC_ALL, "RU");

    if (!getSettings(settings::logoNumber))
    {
        system("pause");
        return -1;
    }
    
    if (!drawLogo(settings::logoNumber))
    {
        system("pause");
        return -1;
    }
    cout << "����� ����������! ������� �������. ����� ������� ������ ������ ������� 8" << endl;


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
        case HELP:
            commandState = printHelp();
            break;
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

bool printHelp()
{
    cout << "������ ��������� ������:" << endl;
    cout << "1.\t������� ������ �����������" << endl;
    cout << "2.\t�������� � ������ �����������" << endl;
    cout << "3.\t������ �� ������ �����������" << endl;
    cout << "7.\t�������� ������� ���������" << endl;
    cout << "8.\t������� ������ ������" << endl;
    cout << "9.\t������������� ���������" << endl;
    cout << "10.\t����� �� ���������" << endl;
    return true;
}

bool getSettings(int & arg)
{
    arg = 0;

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
            arg = value;
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
    cout << "����� ����������! ������� �������. ����� ������� ������ ������ ������� 8" << endl;
    
    return true;
}

/*
* +������� printHelp()
* ������� ����������� ������ ����������� �� employee.dat/bool getEmployeeList(string & arr[]). ������: ��� �����_��������. 
* ����� ���� ����������� �� �����/void printEmployeeList(string & arr[]).
* ����������� ��������� �����������/ bool addEmployee(string & arr[]). ��������� - ���, �����.
* ����������� ������� �����������/ bool removeEmployee(string & arr[]). ��������� - ���, �����.
* ����������� ������ ������� ������������ ��������. bool getHistory(string & arr[]). ������: ��.��.�� ��������� ���������_������������ ������.
* ����������� ������ �� �����. void printHistory(string & arr[]).
* ����������� ��������� � ������� ������������. bool addHistory(string & arr[]). ��������� - ���������, ���������, ������.
* ����������� �������� ������� �� ������ int getIncome(int date1, int date2 = -1). if (date2 == -1)
*/

