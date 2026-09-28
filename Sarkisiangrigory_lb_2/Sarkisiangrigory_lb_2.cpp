// Sarkisiangrigory_lb_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
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

std::vector<pipe> pipes;
std::vector<KS> stations;
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
    std::string mark;
    double lenght;
    double diam;
    bool sig;
    pipe p;

    mark = getString("Enter mark ");
    p.mark = mark;

    lenght = getDouble("Enter lenght ");
    p.lenght = lenght;

    diam = getDouble("Enter diam ");
    p.diam = diam;

    sig = getBool("Enter sig");
    p.sig = sig;

    pipes.push_back(p);
}

void adKS() {
    std::string name;
    int factories;
    int factinwork;
    std::string clas;
    KS k;

    name = getString("Enter name ");
    k.name = name;

    factories = getInt("Enter factories ");
    k.factories = factories;

    factinwork = getInt("Enter factories in work ");
    k.factinwork = factinwork;

    clas = getString("Enter class ");
    k.clas = clas;

    stations.push_back(k);
}

void viewpipes() {
    if (pipes.empty()) {
        std::cout << "pipes not found \n";
    }
    else {
        int i = 1;
        for (const auto& p : pipes) {
            std::cout << i << "." << " mark: " << p.mark << " " << p.lenght << "km " << p.diam << "mm " << "repair " << p.sig << "\n";
            ++i;
        }
    }
}

void viewKS() {
    if (stations.empty()) {
        std::cout << "stations not found\n";
    }
    else {
        int j = 1;
        for (const auto& k : stations) {
            std::cout << j << "." << " name: " << k.name << " " << k.factories << " number of factories " << k.factinwork << " number of factories in work " << k.clas << " class" << "\n";
            ++j;
        }
    }
}

void redactpipe() {
    if (pipes.empty()) {
        std::cout << "pipes not found\n";
        return;
    }

    int x = getInt("Enter pipe number: ");

    if (x >= 1 && x <= (int)pipes.size()) {
        int i = x - 1;
        std::string mark;
        double lenght;
        double diam;
        bool sig;

        mark = getString("Enter mark ");
        pipes[i].mark = mark;

        lenght = getDouble("Enter lenght ");
        pipes[i].lenght = lenght;

        diam = getDouble("Enter diam ");
        pipes[i].diam = diam;

        sig = getBool("Enter sig");
        pipes[i].sig = sig;
    }
    else {
        std::cout << "number is not found\n";
    }
}

void redactKS() {
    if (stations.empty()) {
        std::cout << "stations not found\n";
        return;
    }

    int x = getInt("Enter KS number: ");

    if (x >= 1 && x <= (int)stations.size()) {
        int i = x - 1;
        std::string name;
        int factories;
        int factinwork;
        std::string clas;

        name = getString("Enter name ");
        stations[i].name = name;

        factories = getInt("Enter factories ");
        stations[i].factories = factories;

        factinwork = getInt("Enter factories in work ");
        stations[i].factinwork = factinwork;

        clas = getString("Enter class ");
        stations[i].clas = clas;
    }
    else {
        std::cout << "number is not found\n";
    }
}

void saveTofile() {
    std::ofstream out(data);
    if (!out.is_open()) {
        std::cout << "can't open the file\n";
        return;
    }
    out << pipes.size() << '\n';
    for (const auto& p : pipes) {
        out << p.mark << '\n'
            << p.lenght << '\n'
            << p.diam << '\n'
            << p.sig << '\n';
    }

    out << stations.size() << '\n';
    for (const auto& k : stations) {
        out << k.name << '\n'
            << k.factories << '\n'
            << k.factinwork << '\n'
            << k.clas << '\n';
    }
}

void loadtofile() {
    std::ifstream in(data);
    if (!in.is_open()) {
        std::cout << "can't open the file\n";
        return;
    }

    pipes.clear();
    stations.clear();

    size_t n;
    if (!(in >> n)) {
        std::cout << "file empty or broken\n";
        return;
    }
    in.ignore();

    for (size_t i = 0; i < n; ++i) {
        pipe p;
        std::getline(in, p.mark);
        if (!(in >> p.lenght)) { std::cout << "read error\n"; return; }
        if (!(in >> p.diam)) { std::cout << "read error\n"; return; }
        if (!(in >> p.sig)) { std::cout << "read error\n"; return; }
        in.ignore();
        pipes.push_back(p);
    }

    size_t ns;
    if (!(in >> ns)) {
        std::cout << "loaded " << pipes.size() << " pipes\n";
        return;
    }
    in.ignore();

    for (size_t i = 0; i < ns; ++i) {
        KS k;
        std::getline(in, k.name);
        if (!(in >> k.factories)) { std::cout << "read error\n"; return; }
        if (!(in >> k.factinwork)) { std::cout << "read error\n"; return; }
        in.ignore();
        std::getline(in, k.clas);
        stations.push_back(k);
    }

    std::cout << "loaded " << pipes.size() << " pipes, "
        << stations.size() << " stations\n";
}

int main()
{
    int flag = 1;
    while (flag != 0) {
        std::cout << "\n 1. add pipe \n 2. add KS \n 3. View all obj \n 4. redact pipe \n 5. redact KS \n 6. save \n 7. downloaud \n 0. exit\n";
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
            std::cout << "choose pipe\n";
            viewpipes();
            redactpipe();
            break;
        }
        case 5: {
            std::cout << "redact KS\n";
            std::cout << "choose KS\n";
            redactKS();
            viewKS();
            break;
        }
        case 6: {
            std::cout << "save\n";
            saveTofile();
            break;
        }
        case 7: {
            std::cout << "downloaud\n";
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