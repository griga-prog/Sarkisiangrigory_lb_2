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

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
T getNumber(const std::string& prompt) {
    T value;
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
        int value = getNumber<int>(prompt + " (0 - not repair, 1 - repair): ");
        if (value == 0 || value == 1) return value == 1;
        std::cout << "Error: only 0 or 1 allowed.\n";
    }
}



void adpipe(pipe& currentPipe, bool& pipeSet) {
    currentPipe.mark = getString("Enter mark ");
    currentPipe.lenght = getNumber<double>("Enter lenght ");
    currentPipe.diam = getNumber<double>("Enter diam ");
    currentPipe.sig = getBool("Enter sig");
    pipeSet = true;
}

void viewpipes(bool pipeSet, const pipe& currentPipe) {
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

void redactpipe(bool pipeSet, pipe& currentPipe) {
    if (!pipeSet) {
        std::cout << "pipe not found\n";
        return;
    }

    currentPipe.mark = getString("Enter mark ");
    currentPipe.lenght = getNumber<double>("Enter lenght ");
    currentPipe.diam = getNumber<double>("Enter diam ");
    currentPipe.sig = getBool("Enter sig");
}


void adKS(KS& currentStation, bool& stationSet) {
    currentStation.name = getString("Enter name ");
    currentStation.factories = getNumber<int>("Enter factories ");
    currentStation.factinwork = getNumber<int>("Enter factories in work ");
    currentStation.clas = getString("Enter class ");
    stationSet = true;
}

void viewKS(bool stationSet, const KS& currentStation) {
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

void redactKS(bool stationSet, KS& currentStation) {
    if (!stationSet) {
        std::cout << "station not found\n";
        return;
    }

    currentStation.name = getString("Enter name ");
    currentStation.factories = getNumber<int>("Enter factories ");
    currentStation.factinwork = getNumber<int>("Enter factories in work ");
    currentStation.clas = getString("Enter class ");
}



void savePipe(std::ofstream& out, bool pipeSet, const pipe& p) {
    out << (pipeSet ? 1 : 0) << '\n';
    if (pipeSet) {
        out << p.mark << '\n'
            << p.lenght << '\n'
            << p.diam << '\n'
            << p.sig << '\n';
    }
}

void loadPipe(std::ifstream& in, bool& pipeSet, pipe& p) {
    int flag;
    if (!(in >> flag)) {
        std::cout << "file empty or broken\n";
        pipeSet = false;
        return;
    }
    in.ignore();
    pipeSet = (flag == 1);

    if (pipeSet) {
        std::getline(in, p.mark);
        if (!(in >> p.lenght)) { std::cout << "read error\n"; pipeSet = false; return; }
        if (!(in >> p.diam)) { std::cout << "read error\n"; pipeSet = false; return; }
        if (!(in >> p.sig)) { std::cout << "read error\n"; pipeSet = false; return; }
        in.ignore();
    }
}



void saveStation(std::ofstream& out, bool stationSet, const KS& k) {
    out << (stationSet ? 1 : 0) << '\n';
    if (stationSet) {
        out << k.name << '\n'
            << k.factories << '\n'
            << k.factinwork << '\n'
            << k.clas << '\n';
    }
}

void loadStation(std::ifstream& in, bool& stationSet, KS& k) {
    int flag;
    if (!(in >> flag)) {
        std::cout << "loaded pipe\n";
        stationSet = false;
        return;
    }
    in.ignore();
    stationSet = (flag == 1);

    if (stationSet) {
        std::getline(in, k.name);
        if (!(in >> k.factories)) { std::cout << "read error\n"; stationSet = false; return; }
        if (!(in >> k.factinwork)) { std::cout << "read error\n"; stationSet = false; return; }
        in.ignore();
        std::getline(in, k.clas);
    }
}



void saveTofile(const std::string& filename,bool pipeSet, const pipe& p,bool stationSet, const KS& k) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cout << "can't open the file\n";
        return;
    }
    savePipe(out, pipeSet, p);
    saveStation(out, stationSet, k);
    std::cout << "saved\n";
}

void loadtofile(const std::string& filename,
    bool& pipeSet, pipe& p,
    bool& stationSet, KS& k) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "can't open the file\n";
        return;
    }

    pipeSet = false;
    stationSet = false;

    loadPipe(in, pipeSet, p);
    loadStation(in, stationSet, k);

    std::cout << "loaded\n";
}



int main()
{
    pipe currentPipe;
    KS currentStation;
    bool pipeSet = false;
    bool stationSet = false;
    std::string data = "data.txt";

    int flag = 1;
    while (flag != 0) {
        std::cout << "\n 1. add pipe \n 2. add KS \n 3. View all obj \n 4. redact pipe \n 5. redact KS \n 6. save \n 7. download \n 0. exit\n";
        flag = getNumber<int>("> ");

        switch (flag) {
        case 1: {
            std::cout << "\nadd pipe\n";
            adpipe(currentPipe, pipeSet);
            break;
        }
        case 2: {
            std::cout << "add KS\n";
            adKS(currentStation, stationSet);
            break;
        }
        case 3: {
            std::cout << "View all obj\n";
            viewpipes(pipeSet, currentPipe);
            viewKS(stationSet, currentStation);
            break;
        }
        case 4: {
            std::cout << "redact pipe\n";
            redactpipe(pipeSet, currentPipe);
            break;
        }
        case 5: {
            std::cout << "redact KS\n";
            redactKS(stationSet, currentStation);
            break;
        }
        case 6: {
            std::cout << "save\n";
            saveTofile(data, pipeSet, currentPipe, stationSet, currentStation);
            break;
        }
        case 7: {
            std::cout << "download\n";
            loadtofile(data, pipeSet, currentPipe, stationSet, currentStation);
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