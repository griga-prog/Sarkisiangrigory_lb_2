// Sarkisiangrigory_lb_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

int main()
{
    int flag = 1;
    while (flag != 0) {
        std::cout << "\n 1. add pipe \n 2. add KS \n 3. View all obj \n 4. redact pipe \n 5. redact KS \n 6. save \n 7. downloaud \n 0. exit";
        std::cin >> flag;
        switch (flag) {
        case 1: {
            std::cout << "\nadd pipe\n";
            break;
        }
        case 2: {
            std::cout << "add KS\n";
            break;
        }
        case 3: {
            std::cout << "View all obj\n";
            break;
        }
        case 4: {
            std::cout << "redact pipe\n";
            break;
        }
        case 5: {
            std::cout << "redact KS\n";
            break;
        }
        case 6: {
            std::cout << "save\n";
            break;
        }
        case 7: {
            std::cout << "downloaud\n";
            break;
        }
        case 0: {
            std::cout << "\n 1. add pipe \n 2. add KS \n 3. View all obj \n 4. redact pipe \n 5. redact KS \n 6. save \n 7. downloaud \n 0. exit";
            break;
        }
        }
    }
}

struct pipe {
    std::string mark;
    double lenght;
    double diam;
    std::string sig;
};

struct KS
{
    std::string name;
    int factories;
    int factinwork;
    std::string clas;
};
