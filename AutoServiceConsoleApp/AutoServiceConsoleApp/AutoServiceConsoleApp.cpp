#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <vector>
#include <map>

using namespace std;

using map_t = map<string, int>;
using vectorPair_t = vector<pair<string, long long>>;

#include "Header.h"

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

struct ProgramInfo
{
    ProgramInfo(){}
    ~ProgramInfo(){}
    map_t settingsMap;
    vectorPair_t employeesList;
    vectorPair_t historyList;
};

ProgramInfo progInfo;

int main()
{
    setlocale(LC_ALL, "RU");

    if (!getSettings(progInfo.settingsMap))
    {
        system("pause");
        return -1;
    }

    if (!getEmployees(progInfo.employeesList))
    {
        system("pause");
        return -1;
    }
    
    if (!drawLogo(progInfo.settingsMap))
    {
        system("pause");
        return -1;
    }
    cout << "����� ����������! ����� ������� ������ ������ ������� 8" << endl;

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
        case EMPLOYEES:
            commandState = printEmployees(progInfo.employeesList);
            break;
        case ADDEMPLOYEE:
            commandState = addEmployee(progInfo.employeesList);
            break;
        case HELP:
            commandState = printHelp();
            break;
        case CHANGELOGO:
            commandState = changeLogo(progInfo.settingsMap);
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

bool addEmployee(vectorPair_t& employeesList)
{
    int currentParam;
    cout << "��� ����, ����� �������� ������ ����������, �������� ���������� ����������� ����������� (0 - ��������� �����)" << endl;
    do
    {
        userInputHandler<>(currentParam);
        if (!currentParam)
        {
            onExitCommand();
            return true;
        }
    } while (currentParam < 0);

    string buffer;
    string name;
    long long number;
    int separator;
    ofstream employeesFile("..\\Debug\\employees.dat", ios_base::binary && ios_base::app);
    if (!employeesFile.is_open())
    {
        cout << "���� ����������� �� ������" << endl;
        return false;
    }
    for (int i = 0; i != currentParam; ++i)
    {
        // userInputHandler<string>(buffer);
        cout << endl;
        getline(cin, buffer);
        separator = buffer.rfind(' ');
        name = buffer.substr(0, separator);
        // cout << name << endl;
        if (buffer.find('+'))
            separator = buffer.find('+');
        number = stoll(buffer.substr(separator + 1, buffer.size() - separator - 1));
        employeesList.push_back({ name, number });
        // buffer = name + " +" + to_string(number) + "\n";
        //employeesFile.write(buffer.c_str(), sizeof(char) * buffer.size());
    }
    employeesFile.close();

    return true;
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

bool getSettings(map_t& settingsMap)
{
    string param;
    int value;
    ifstream settingsFile("..\\Debug\\settings.txt");
    if (!settingsFile.is_open())
    {
        cout << "���� �������� �� ������" << endl;
        return false;
    }
    while (settingsFile >> param >> value)
    {
        settingsMap[param] = value;
    }
    settingsFile.close();
    return true;
}

bool printEmployees(vectorPair_t& employeesList)
{
    for (vectorPair_t::iterator i = employeesList.begin(); i != employeesList.end(); ++i)
    {
        cout << i->first << ". ��������: +" << i->second << endl;
    }

    return true;
}

bool getEmployees(vectorPair_t& employeesList)
{
    string name = "";
    long long number = 0;
    ifstream employeesFile("..\\Debug\\employees.dat", ios_base::binary);
    if (!employeesFile.is_open())
    {
        cout << "���� ����������� �� ������" << endl;
        return false;
    }
    char c = '>';
    bool readNumber = false;

    while (employeesFile)
    {
        employeesFile.read(&c, 1);
        if (!readNumber && c != '+' && c != '\n')
        {
            name = name + c;
        }
        else if (c == '+')
        {
            readNumber = true;
        }
        else if (readNumber && c != ' ' && c != '\r')
        {
            number = number * 10 + (c - '0');
        }
        else if (readNumber && (c == ' ' || c == '\r'))
        {
            readNumber = false;
            name.erase(name.end());
            employeesList.push_back({ name, number });

            name = "";
            number = 0;
        }
    }
    employeesFile.close();
    return true;
}

bool drawLogo(map_t& settingsMap)
{
    const string PATHS[2] = { "..\\Debug\\logo.txt" , "..\\Debug\\logo2.txt" };
    ifstream logoFile(PATHS[settingsMap["logoNumber"]]);
    if (!logoFile.is_open())
    {
        cout << "���� �������� �� ������" << endl;

        return false;
    }
    cout << logoFile.rdbuf() << endl;

    logoFile.close();
    return true;
}

bool changeLogo(map_t& settingsMap)
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
    settingsMap["logoNumber"] = currentParam;
    ofstream settingsFile("..\\Debug\\settings.txt");
    if (!settingsFile.is_open())
    {
        return false;
    }
    for (map_t::iterator i = settingsMap.begin(); i != settingsMap.end(); ++i)
    {
        settingsFile << i->first << " " << i->second <<  endl;
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
    drawLogo(progInfo.settingsMap);
    cout << "����� ����������! ������� �������. ����� ������� ������ ������ ������� 8" << endl;
    
    return true;
}

/*
* +������� printHelp()
* +������� ����������� ������ ����������� �� employee.dat/bool getEmployees(string & arr[]). ������: ��� �����_��������. 
* +����� ���� ����������� �� �����/void printEmployees(string & arr[]).
* ����������� ��������� �����������/ bool addEmployee(string & arr[]). ��������� - ���, �����.
* ����������� ������� �����������/ bool removeEmployee(string & arr[]). ��������� - ���, �����.
* ����������� ������ ������� ������������ ��������. bool getHistory(string & arr[]). ������: ��.��.�� ��������� ���������_������������ ������.
* ����������� ������ �� �����. void printHistory(string & arr[]).
* ����������� ��������� � ������� ������������. bool addHistory(string & arr[]). ��������� - ���������, ���������, ������.
* ����������� �������� ������� �� ������ int getIncome(int date1, int date2 = -1). if (date2 == -1)
*/

