#include "user.h"

User::User()
{
    id          = "";
    name        = "";
    affiliation = "";
    solved      = "";
    solved_list = {};
}

User::User(std::string id,
           std::string name,
           std::string affiliation,
           std::string solved,
           std::set<std::string> solved_list)
{
    this->id          = id;
    this->name        = name;
    this->affiliation = affiliation;
    this->solved      = solved;
    this->solved_list = solved_list;
}

bool User::operator < (const User &user) const
{
    if (solved != user.solved) {
        return solved < user.solved;
    }

    if (id != user.id) {
        return id < user.id;
    }

    if (name != user.name) {
        return name < user.name;
    }

    if (affiliation != user.affiliation) {
        return affiliation < user.affiliation;
    }
    return 0;
}

void User::setID(std::string id)
{
    this->id = id;
}

std::string User::getID(void)
{
    return id;
}

void User::setName(std::string name)
{
    this->name = name;
}

std::string User::getName(void)
{
    return name;
}

void User::setAffiliation(std::string affiliation)
{
    this->affiliation = affiliation;
}

std::string User::getAffiliation(void)
{
    return affiliation;
}

void User::setSolved(std::string solved)
{
    this->solved = solved;
}

std::string User::getSolved(void)
{
    return solved;
}

void User::setSolvedList(std::set<std::string> solved_list)
{
    this->solved_list = solved_list;
}

std::set<std::string> User::getSolvedList(void)
{
    return solved_list;
}

void User::displayInfo(void)
{
    std::cout << "           ID : " << id << std::endl;
    std::cout << "         Name : " << name << std::endl;
    std::cout << "  Affiliation : " << affiliation << std::endl;
    std::cout << "       Solved : " << solved << std::endl;
    std::cout << " Problem List : " << std::endl;

    int cnt = 0;
    for (auto problem : solved_list) {
        std::cout << problem << " ";
        ++cnt;
        if (cnt == 20) {
            cnt = 0;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}
