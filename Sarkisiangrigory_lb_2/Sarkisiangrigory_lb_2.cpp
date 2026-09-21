// Sarkisiangrigory_lb_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

void adpipe() {
    std::string mark;
    double lenght;
    double diam;
    bool sig;
    pipe p;
    std::cout << "Enter mark ";
    std::cin >> mark;
    p.mark = mark;

    std::cout << "Enter lenght";
    std::cin >> lenght;
    p.lenght = lenght;

    std::cout << "Enter diam";
    std::cin >> diam;
    p.diam = diam;

    std::cout << "Enter sig";
    std::cin >> sig;
    p.sig = sig;

    std::cout << p.mark;
    std::cout << p.lenght;
    std::cout << p.diam;
    std::cout << p.sig;
   /* pipes.push_back(pipe{ mark,lenght,diam,sig });*/
    pipes.push_back(p);
    //for (const auto& s : pipes) {
    //        std::cout << s.mark << " mark " << s.lenght << " km " << s.diam << " mm " << s.sig << "\n";
    //    }




}
void adKS() {
    std::string name;
    int factories;
    int factinwork;
    std::string clas;
    KS k;
    std::cout << "Enter name ";
    std::cin >> name;
    k.name = name;

    std::cout << "Enter factories";
    std::cin >> factories;
    k.factories = factories;

    std::cout << "Enter factories in work";
    std::cin >> factinwork;
    k.factinwork = factinwork;

    std::cout << "Enter class";
    std::cin >> clas;
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
    int x;
    std::cin >> x;
    if (x - 1 < pipes.size()) {
        int i = x - 1;
        std::string mark;
        double lenght;
        double diam;
        bool sig;

        std::cout << "Enter mark ";
        std::cin >> mark;
        pipes[i].mark = mark;

        std::cout << "Enter lenght";
        std::cin >> lenght;
        pipes[i].lenght = lenght;

        std::cout << "Enter diam";
        std::cin >> diam;
        pipes[i].diam = diam;

        std::cout << "Enter sig";
        std::cin >> sig;
        pipes[i].sig = sig;
    }
    else {
        std::cout << "number is not found";
    }


}
void redactKS() {
    int x;
    std::cin >> x;
    if (x - 1 < stations.size()) {
        int i = x - 1;
        std::string name;
        int factories;
        int factinwork;
        std::string clas;
        std::cout << "Enter name ";
        std::cin >> name;
        stations[i].name = name;

        std::cout << "Enter factories";
        std::cin >> factories;
        stations[i].factories = factories;

        std::cout << "Enter factories in work";
        std::cin >> factinwork;
        stations[i].factinwork = factinwork;

        std::cout << "Enter class";
        std::cin >> clas;
        stations[i].clas = clas;
    }
    else {
        std::cout << "number is not found";
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
        std::cout << "file empty or broken";
        return;
    }

    in.ignore();

    for (size_t i = 0; i < n; ++i) {
        pipe p;
        std::getline(in, p.mark);
        in >> p.lenght;
        in >> p.diam;
        in >> p.sig;
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
        in >> k.factories;
        in >> k.factinwork;
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
        std::cout << "\n 1. add pipe \n 2. add KS \n 3. View all obj \n 4. redact pipe \n 5. redact KS \n 6. save \n 7. downloaud \n 0. exit";
        std::cin >> flag;
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
            std::cout << "\n 1. add pipe \n 2. add KS \n 3. View all obj \n 4. redact pipe \n 5. redact KS \n 6. save \n 7. downloaud \n 0. exit";
            break;
        }
        }
    }
}  



