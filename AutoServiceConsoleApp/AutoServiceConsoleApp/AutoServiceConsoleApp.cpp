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
    cout << "Добро пожаловать! Введите команду. Чтобы открыть список команд введите 8" << endl;


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
        cout << "Файл Логотипа не найден" << endl;

        return false;
    }
    cout << logoFile.rdbuf() << endl;

    logoFile.close();
    return true;
}

bool changeLogo()
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
    drawLogo(settings::logoNumber);
    cout << "Добро пожаловать! Введите команду. Чтобы открыть список команд введите 8" << endl;
    
    return true;
}

/*
* +Команда printHelp()
* Сделать возможность чтения сотрудников из employee.dat/bool getEmployeeList(string & arr[]). Формат: ФИО номер_телефона. 
* Вывод всех сотрудников на экран/void printEmployeeList(string & arr[]).
* Возможность добавлять сотрудников/ bool addEmployee(string & arr[]). Параметры - ФИО, номер.
* Возможность убирать сотрудников/ bool removeEmployee(string & arr[]). Параметры - ФИО, номер.
* Возможность чтения истории обслуживания клиентов. bool getHistory(string & arr[]). Формат: дд.мм.гг НОМЕРАВТО категория_обслуживания деньги.
* Возможность вывода на экран. void printHistory(string & arr[]).
* Возможность добавлять в историю обслуживания. bool addHistory(string & arr[]). Параметры - номеравто, категория, деньги.
* Возможность смотреть прибыль за период int getIncome(int date1, int date2 = -1). if (date2 == -1)
*/

