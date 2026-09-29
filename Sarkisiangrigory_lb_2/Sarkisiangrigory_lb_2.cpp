// Sarkisiangrigory_lb_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <fstream>
#include <iostream>
#include <string>
#include <limits>

struct pipe {
    std::string mark;
    double lenght;
    double diam;
    bool sig;
};

struct KS
{
    std::string name;
    int factories;
    int factinwork;
    std::string clas;
};

pipe currentPipe;
KS currentStation;
bool pipeSet = false;
bool stationSet = false;
std::string data = "data.txt";



void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Error: enter a number, please.\n";
        clearInput();
    }
}

double getDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Error: enter a number, please.\n";
        clearInput();
    }
}

std::string getString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        std::cout << "Error: empty input.\n";
        clearInput();
    }
}

bool getBool(const std::string& prompt) {
    while (true) {
        int value = getInt(prompt + " (0 - not repair, 1 - repair): ");
        if (value == 0 || value == 1) return value == 1;
        std::cout << "Error: only 0 or 1 allowed.\n";
    }
}



void adpipe() {
    pipe p;
    p.mark = getString("Enter mark ");
    p.lenght = getDouble("Enter lenght ");
    p.diam = getDouble("Enter diam ");
    p.sig = getBool("Enter sig");

    currentPipe = p;
    pipeSet = true;
}

void viewpipes() {
    if (!pipeSet) {
        std::cout << "pipe not found \n";
    }
    else {
        std::cout << " mark: " << currentPipe.mark
            << " " << currentPipe.lenght << "km "
            << currentPipe.diam << "mm "
            << "repair " << currentPipe.sig << "\n";
    }
}

void redactpipe() {
    if (!pipeSet) {
        std::cout << "pipe not found\n";
        return;
    }

    currentPipe.mark = getString("Enter mark ");
    currentPipe.lenght = getDouble("Enter lenght ");
    currentPipe.diam = getDouble("Enter diam ");
    currentPipe.sig = getBool("Enter sig");
}



void adKS() {
    KS k;
    k.name = getString("Enter name ");
    k.factories = getInt("Enter factories ");
    k.factinwork = getInt("Enter factories in work ");
    k.clas = getString("Enter class ");

    currentStation = k;
    stationSet = true;
}

void viewKS() {
    if (!stationSet) {
        std::cout << "station not found\n";
    }
    else {
        std::cout << " name: " << currentStation.name
            << " " << currentStation.factories << " number of factories "
            << currentStation.factinwork << " number of factories in work "
            << currentStation.clas << " class" << "\n";
    }
}

void redactKS() {
    if (!stationSet) {
        std::cout << "station not found\n";
        return;
    }

    currentStation.name = getString("Enter name ");
    currentStation.factories = getInt("Enter factories ");
    currentStation.factinwork = getInt("Enter factories in work ");
    currentStation.clas = getString("Enter class ");
}



void saveTofile() {
    std::ofstream out(data);
    if (!out.is_open()) {
        std::cout << "can't open the file\n";
        return;
    }

    out << (pipeSet ? 1 : 0) << '\n';
    if (pipeSet) {
        out << currentPipe.mark << '\n'
            << currentPipe.lenght << '\n'
            << currentPipe.diam << '\n'
            << currentPipe.sig << '\n';
    }

    out << (stationSet ? 1 : 0) << '\n';
    if (stationSet) {
        out << currentStation.name << '\n'
            << currentStation.factories << '\n'
            << currentStation.factinwork << '\n'
            << currentStation.clas << '\n';
    }

    std::cout << "saved\n";
}

void loadtofile() {
    std::ifstream in(data);
    if (!in.is_open()) {
        std::cout << "can't open the file\n";
        return;
    }

    pipeSet = false;
    stationSet = false;

    int pFlag;
    if (!(in >> pFlag)) {
        std::cout << "file empty or broken\n";
        return;
    }
    in.ignore();
    pipeSet = (pFlag == 1);

    if (pipeSet) {
        std::getline(in, currentPipe.mark);
        if (!(in >> currentPipe.lenght)) { std::cout << "read error\n"; return; }
        if (!(in >> currentPipe.diam)) { std::cout << "read error\n"; return; }
        if (!(in >> currentPipe.sig)) { std::cout << "read error\n"; return; }
        in.ignore();
    }

    int sFlag;
    if (!(in >> sFlag)) {
        std::cout << "loaded pipe\n";
        return;
    }
    in.ignore();
    stationSet = (sFlag == 1);

    if (stationSet) {
        std::getline(in, currentStation.name);
        if (!(in >> currentStation.factories)) { std::cout << "read error\n"; return; }
        if (!(in >> currentStation.factinwork)) { std::cout << "read error\n"; return; }
        in.ignore();
        std::getline(in, currentStation.clas);
    }

    std::cout << "loaded\n";
}



int main()
{
    int flag = 1;
    while (flag != 0) {
        std::cout << "\n 1. add pipe \n 2. add KS \n 3. View all obj \n 4. redact pipe \n 5. redact KS \n 6. save \n 7. download \n 0. exit\n";
        flag = getInt("> ");

        switch (flag) {
        case 1: {
            std::cout << "\nadd pipe\n";
            adpipe();
            break;
        }
        case 2: {
            std::cout << "add KS\n";
            adKS();
            break;
        }
        case 3: {
            std::cout << "View all obj\n";
            viewpipes();
            viewKS();
            break;
        }
        case 4: {
            std::cout << "redact pipe\n";
            redactpipe();
            break;
        }
        case 5: {
            std::cout << "redact KS\n";
            redactKS();
            break;
        }
        case 6: {
            std::cout << "save\n";
            saveTofile();
            break;
        }
        case 7: {
            std::cout << "download\n";
            loadtofile();
            break;
        }
        case 0: {
            std::cout << "exit\n";
            break;
        }
        default:
            std::cout << "Error: no such menu item. Choose 0-7.\n";
        }
    }
}