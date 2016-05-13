#include "prob.h"

Prob::Prob()
{
    id   = "";
    name = "";
    TL   = "";
    sub  = "";
    AC   = "";
    WA   = "";
    TLE  = "";
    MLE  = "";
    RE   = "";
}

Prob::Prob(std::string id,
           std::string name,
           std::string TL,
           std::string sub,
           std::string AC,
           std::string WA,
           std::string TLE,
           std::string MLE,
           std::string RE)
{

    this->id   = id;
    this->name = name;
    this->TL   = TL;
    this->sub  = sub;
    this->AC   = AC;
    this->WA   = WA;
    this->TLE  = TLE;
    this->MLE  = MLE;
    this->RE   = RE;
}

bool Prob::operator < (const Prob p) const
{
    if (id != p.id) {
        return id < p.id;
    }

    if (name != p.name) {
        return name < p.name;
    }
    return 0;
}

void Prob::setID(std::string id)
{
    this->id = id;
}

std::string Prob::getID(void)
{
    return id;
}

void Prob::setName(std::string name)
{
    this->name = name;
}

std::string Prob::getName(void)
{
    return name;
}

void Prob::setInfo(std::string TL,
                   std::string sub,
                   std::string AC,
                   std::string WA,
                   std::string TLE,
                   std::string MLE,
                   std::string RE)
{
    this->TL  = TL;
    this->sub = sub;
    this->AC  = AC;
    this->WA  = WA;
    this->TLE = TLE;
    this->MLE = MLE;
    this->RE  = RE;
}

std::string Prob::getTL(void)
{
    return TL;
}

std::string Prob::getSub(void)
{
    return sub;
}

std::string Prob::getAC(void)
{
    return AC;
}

std::string Prob::getTLE(void)
{
    return TLE;
}

std::string Prob::getMLE(void)
{
    return MLE;
}

void Prob::displayInfo(void)
{
    std::cout << "   ID : " + id << std::endl;
    std::cout << " Name : " + name << std::endl;
    std::cout << "   TL : " + TL << std::endl;
    std::cout << "  sub : " + sub << std::endl;
    std::cout << "   AC : " + AC << std::endl;
    std::cout << "   WA : " + WA << std::endl;
    std::cout << "  TLE : " + TLE << std::endl;
    std::cout << "  MLE : " + MLE << std::endl;
    std::cout << "   RE : " + RE << std::endl;
}
