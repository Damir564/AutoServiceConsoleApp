#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <vector>
#include <map>

using namespace std;

using vectorPair_t = vector<pair<string, long long>>;
using map_t = map<string, int>;

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
    cout << "Добро пожаловать! Чтобы увидеть список команд введите 8" << endl;


    int currentCommand = 0;
    bool commandState = true;
    do
    {
        if (!commandState)
        {
            system("pause");
            return -1;
        }
        cout << "Введите Команду:" << endl;
        userInputHandler<>(currentCommand);
        switch (currentCommand)
        {
        case EMPLOYEES:
            commandState = printEmployees(progInfo.employeesList);
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

bool printHelp()
{
    cout << "Список возможных команд:" << endl;
    cout << "1.\tВывести список сотрудников" << endl;
    cout << "2.\tДобавить в список сотрудников" << endl;
    cout << "3.\tУбрать из списка сотрудников" << endl;
    cout << "7.\tИзменить логотип программы" << endl;
    cout << "8.\tВывести список команд" << endl;
    cout << "9.\tПерезагрузить программу" << endl;
    cout << "10.\tВыйти из программы" << endl;
    return true;
}

bool getSettings(map_t& settingsMap)
{
    string param;
    int value;
    ifstream settingsFile("..\\Debug\\settings.txt");
    if (!settingsFile.is_open())
    {
        cout << "Файл Настроек не найден" << endl;
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
        cout << i->first << ". Контакты: +" << i->second << endl;
    }

    return true;
}

bool getEmployees(vectorPair_t& employeesList)
{
    string name = "";
    long long number = 0;
    ifstream employeeFile("..\\Debug\\employees.dat", ios_base::binary);
    if (!employeeFile.is_open())
    {
        cout << "Файл Сотрудников не найден" << endl;
        return false;
    }
    char c = '>';
    bool readNumber = false;

    while (employeeFile)
    {
        employeeFile.read(&c, 1);
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
    employeeFile.close();
    return true;
}

bool drawLogo(map_t& settingsMap)
{
    const string PATHS[2] = { "..\\Debug\\logo.txt" , "..\\Debug\\logo2.txt" };
    ifstream logoFile(PATHS[settingsMap["logoNumber"]]);
    if (!logoFile.is_open())
    {
        cout << "Файл Логотипа не найден" << endl;

        return false;
    }
    cout << logoFile.rdbuf() << endl;

    logoFile.close();
    return true;
}

bool changeLogo(map_t& settingsMap)
{
    int currentParam;
    cout  << "Выберите логотип:\n\t1 - Гайка\n\t2 - Машина\n0 - Вернуться назад" << endl;
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
    cout << "Ввод >> ";
    cin >> arg;
}

void onExitCommand()
{
    cout << "<Завершнение команды>" << endl;
}

bool clearScreen()
{
    system("cls");
    drawLogo(progInfo.settingsMap);
    cout << "Добро пожаловать! Введите команду. Чтобы открыть список команд введите 8" << endl;
    
    return true;
}

/*
* +Команда printHelp()
* +Сделать возможность чтения сотрудников из employee.dat/bool getEmployees(string & arr[]). Формат: ФИО номер_телефона. 
* +Вывод всех сотрудников на экран/void printEmployees(string & arr[]).
* Возможность добавлять сотрудников/ bool addEmployee(string & arr[]). Параметры - ФИО, номер.
* Возможность убирать сотрудников/ bool removeEmployee(string & arr[]). Параметры - ФИО, номер.
* Возможность чтения истории обслуживания клиентов. bool getHistory(string & arr[]). Формат: дд.мм.гг НОМЕРАВТО категория_обслуживания деньги.
* Возможность вывода на экран. void printHistory(string & arr[]).
* Возможность добавлять в историю обслуживания. bool addHistory(string & arr[]). Параметры - номеравто, категория, деньги.
* Возможность смотреть прибыль за период int getIncome(int date1, int date2 = -1). if (date2 == -1)
*/

