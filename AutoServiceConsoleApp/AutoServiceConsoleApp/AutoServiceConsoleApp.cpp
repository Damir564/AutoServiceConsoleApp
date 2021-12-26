#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <vector>
#include <Windows.h>
#include <map>

using namespace std;

using map_t = map<string, int>;
using vectorPair_t = vector<pair<string, long long>>;

enum COMMANDS {
    EXIT,
    EMPLOYEES,
    ADDEMPLOYEE,
    REMOVEEMPLOYEE,
    HISTORY,
    ADDHISTORY,
    EARNINGS,
    CHANGELOGO,
    HELP,
    RESTART,
};

struct ProgramInfo
{
    ProgramInfo() : earnings(0){}
    ~ProgramInfo(){}
    void clear()
    {
        earnings = 0;
        settingsMap.clear();
        employeesList.clear();
        historyList.clear();
    }
    map_t settingsMap;
    vectorPair_t employeesList;
    vectorPair_t historyList;
    long long earnings;
};

#include "Header.h"

int main()
{
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ProgramInfo progInfo;
    if (!startProgram(progInfo))
    { 
        std::system("pause");
        return -1;
    }

    int currentCommand = 0;
    bool commandState = true;
    do
    {
        if (!commandState)
        {
            std::system("pause");
            return -1;
        }
        cout << "������� �������:" << endl;
        userInputHandler(currentCommand);
        switch (currentCommand)
        {
        case EMPLOYEES:
            commandState = printEmployees(progInfo.employeesList);
            break;
        case ADDEMPLOYEE:
            commandState = addEmployee(progInfo.employeesList);
            break;
        case REMOVEEMPLOYEE:
            commandState = removeEmployee(progInfo.employeesList);
            break;
        case HISTORY:
            commandState = printHistory(progInfo.historyList);
            break;
        case ADDHISTORY:
            commandState = addHistory(progInfo.historyList);
            break;
        case EARNINGS:
            commandState = printEarnings(progInfo.earnings);
            break;
        case HELP:
            commandState = printHelp();
            break;
        case CHANGELOGO:
            commandState = changeLogo(progInfo.settingsMap);
            break;
        case RESTART:
            commandState = startProgram(progInfo);
            break;
        case EXIT:
            break;
        default:
            cout << "������ ����� �������" << endl;
            break;
        }
    } while (currentCommand != EXIT);

    std::system("pause");
    return 0;
}

bool printHelp()
{
    cout << "������ ��������� ������:" << endl;
    cout << "1.\t������� ������ �����������" << endl;
    cout << "2.\t�������� � ������ �����������" << endl;
    cout << "3.\t������ �� ������ �����������" << endl;
    cout << "4.\t������� �������" << endl;
    cout << "5.\t�������� � �������" << endl;
    cout << "6.\t������� ���������" << endl;
    cout << "7.\t�������� ������� ���������" << endl;
    cout << "8.\t������� ������ ������" << endl;
    cout << "9.\t������������� ���������" << endl;
    cout << "10.\t����� �� ���������" << endl;
    return true;
}

bool addEmployee(vectorPair_t& employeesList)
{
    int currentParam;
    cout << "��� ����, ����� �������� ����� �����������, ������� ���������� ����������� ����������� (0 - ��������� �����)" << endl;
    userInputHandler(currentParam);
    if (cin.fail())
    {
        cout << "������ �����! �� ����� �� �����." << endl;
        return false;
    }
    if (!currentParam)
    {
        onExitCommand();
        return true;
    }

    ofstream employeesFile("..\\Debug\\employees.dat", ios_base::binary | ios_base::app);
    if (!employeesFile.is_open())
    {
        cout << "���� ����������� �� ������" << endl;
        return false;
    }
    cout << "������� ������ � ������ ����������: ��� �����_��������" << endl;
    string buffer;
    string name;
    string temp;
    long long number;
    int separator;
    for (int i = 0; i != currentParam; ++i)
    {
        userInputHandler(buffer);
        separator = buffer.rfind(' ');
        name = buffer.substr(0, separator);
        if (buffer.rfind('+') != string::npos)
            separator = buffer.rfind('+');
        temp = buffer.substr(separator + 1, buffer.size() - separator - 1);
        number = stoll(temp);
        employeesList.push_back({ name, number });
        buffer = name + " +" + temp + "\n";
        employeesFile.write(buffer.c_str(), sizeof(char) * buffer.size());
    }
    employeesFile.close();

    return true;
}

bool removeEmployee(vectorPair_t& employeesList)
{
    int currentParam;
    cout << "��� ����, ����� ������� ����������� �� ������, ������� ���������� ��������� ����������� (0 - ��������� �����)" << endl;
    userInputHandler(currentParam);
    if (cin.fail())
    {
        cout << "������ �����! �� ����� �� �����." << endl;
        return false;
    }
    if (!currentParam)
    {
        onExitCommand();
        return true;
    }

    cout << "������� ��� ���������� ����������" << endl;
    string name;
    map_t posMap;
    for (vectorPair_t::iterator i = employeesList.begin(); i != employeesList.end(); ++i)
    {
        posMap[i->first] = i - employeesList.begin();
    }
    for (int i = 0; i != currentParam; ++i)
    {
        userInputHandler(name);
        if (posMap.find(name) == posMap.end())
        {
            cout << "������ ��������� �� ������" << endl;
            return false;
        }
        else
        {
            employeesList.erase(employeesList.begin() + posMap[name]);
        }
    }
    ofstream employeesFile("..\\Debug\\employees.dat", ios_base::binary);
    if (!employeesFile.is_open())
    {
        cout << "���� ����������� �� ������" << endl;
        return false;
    }
    string buffer;
    for (vectorPair_t::iterator i = employeesList.begin(); i != employeesList.end(); ++i)
    {
        buffer = i->first + " +" + to_string(i->second) + "\n";
        employeesFile.write(buffer.c_str(), sizeof(char) * buffer.size());
    }
    employeesFile.close();

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
    if (employeesList.begin() == employeesList.end())
        cout << "���������� �� �������" << endl;

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
    char c;
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
            name.pop_back();
            employeesList.push_back({ name, number });

            name = "";
            number = 0;
        }
    }
    employeesFile.close();
    return true;
}

bool addHistory(vectorPair_t& historyList)
{
    int currentParam;
    cout << "��� ����, ����� �������� ������ � �������, ������� ���������� ����� ������� (0 - ��������� �����)" << endl;
    userInputHandler(currentParam);
    if (cin.fail())
    {
        cout << "������ �����! �� ����� �� �����." << endl;
        return false;
    }
    if (!currentParam)
    {
        onExitCommand();
        return true;
    }

    ofstream employeesFile("..\\Debug\\history.dat", ios_base::binary | ios_base::app);
    if (!employeesFile.is_open())
    {
        cout << "���� ������� �� ������" << endl;
        return false;
    }
    cout << "������� ����� ����, ����������, ����� �����" << endl;
    SYSTEMTIME st;

    string buffer;
    string info;
    string info2;
    long long number;
    int separator;
    for (int i = 0; i != currentParam; ++i)
    {
        userInputHandler(buffer);
        GetLocalTime(&st);
        buffer = to_string(st.wDay) + '.' + to_string(st.wMonth) + '.' + to_string(st.wYear) + ' ' + 
            to_string(st.wHour) + ':' + to_string(st.wMinute) + ' ' + buffer;
        separator = buffer.rfind(' ');
        info = buffer.substr(0, separator);
        info2 = buffer.substr(separator + 1, buffer.size() - separator - 1);
        number = stoll(info2);
        historyList.push_back({ info, number });
        buffer = info + " " + info2 + "\n";
        employeesFile.write(buffer.c_str(), sizeof(char) * buffer.size());
    }
    employeesFile.close();

    return true;
}

bool printHistory(vectorPair_t& historyList)
{
    for (vectorPair_t::iterator i = historyList.begin(); i != historyList.end(); ++i)
    {
        cout << i->first << ". ������: " << i->second << endl;
    }

    return true;
}

bool printEarnings(long long& earnings)
{
    if (earnings > 0)
        cout << "��������� ����������: ";
    else
        cout << "������ ����������: ";
    cout << earnings << " ������." << endl;
    return true;
}

bool getHistory(vectorPair_t& historyList, long long& earnings)
{
    string buffer = "";
    string info = "";
    int separator;
    long long number = 0;
    ifstream historyFile("..\\Debug\\history.dat", ios_base::binary);
    if (!historyFile.is_open())
    {
        cout << "���� ������� �� ������" << endl;
        return false;
    }
    char c;

    while (historyFile)
    {
        historyFile.read(&c, 1);
        if (c != '\n')
        {
            buffer = buffer + c;
        }
        else
        {
            if (buffer.rfind(' ') == string::npos)
                break;
            separator = buffer.rfind(' ');
            info = buffer.substr(0, separator);
            number = stoll(buffer.substr(separator + 1, buffer.size() - separator - 1));
            historyList.push_back({ info, number });
            earnings += number;

            buffer = "";
            info = "";
            number = 0;
        }
    }
    historyFile.close();
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
    userInputHandler(currentParam);
    if (!currentParam)
    {
        onExitCommand();
        return true;
    }
    if (currentParam != 1 && currentParam != 2)
    {
        cout << "������ �����! �� ����� �������� ��������." << endl;
        return false;
    }
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
    if constexpr (is_same_v<T, string>) // ???
    { 
        cin.ignore();
        getline(cin, arg);
    }
    else
    {
        cin >> arg; 
    }
}


void onExitCommand()
{
    cout << "����������� �������" << endl;
}

bool startProgram(ProgramInfo & progInfo)
{
    std::system("cls");
    progInfo.clear();
    if (!getSettings(progInfo.settingsMap))
    {
        return false;
    }
    if (!getEmployees(progInfo.employeesList))
    {
        return false;
    }
    if (!getHistory(progInfo.historyList, progInfo.earnings))
    {
        return false;
    }
    if (!drawLogo(progInfo.settingsMap))
    {
        return false;
    }
    cout << "����� ����������! ����� ������� ������ ������ ������� 8" << endl;
    
    return true;
}

/*
* +������� printHelp()
* +������� ����������� ������ ����������� �� employee.dat/bool getEmployees(string & arr[]). ������: ��� �����_��������. 
* +����� ���� ����������� �� �����/void printEmployees(string & arr[]).
* +����������� ��������� �����������/ bool addEmployee(string & arr[]). ��������� - ���, �����.
* +����������� ������� �����������/ bool removeEmployee(string & arr[]). ��������� - ���, �����.
* +����������� ������ ������� ������������ ��������. bool getHistory(string & arr[]). ������: ��.��.�� ��������� ���������_������������ ������.
* ����������� ������ �� �����. void printHistory(string & arr[]).
* ����������� ��������� � ������� ������������. bool addHistory(string & arr[]). ��������� - ���������, ���������, ������.
* ����������� �������� ������� �� ������ int getIncome(int date1, int date2 = -1). if (date2 == -1)
*/

