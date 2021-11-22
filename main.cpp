#include "config.hpp"
#include <iostream>

int main()
{
    std::string lname;
    std::string name;
    int age;

    Config *cfg = new Config();

    cfg->load("main.cfg");
    cfg->bind(lname, "Last Name"); 
    cfg->bind(name, "Meu Nome"); 
    cfg->bind(age, "Minha Idade");

    std::cout << "Last Name: " << lname << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;

    delete cfg;

    return 0;
}
