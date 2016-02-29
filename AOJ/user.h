#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <time.h>


class User {
  private:
    std::string id;
    std::string name;
    std::string affiliation;
    std::string solved;
    std::set<std::string> solved_list;

  public:
    User() {
        id          = "";
        name        = "";
        affiliation = "";
        solved      = "";
        solved_list = {};
    }

    User(std::string id,
           std::string name,
           std::string affiliation,
           std::string solved,
           std::set<std::string> solved_list) {

        this->id          = id;
        this->name        = name;
        this->affiliation = affiliation;
        this->solved      = solved;
        this->solved_list = solved_list;
    }

    bool operator < (const User &user)const {
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

    void setID(std::string id)
    {
        this->id = id;
    }

    std::string getID(void)
    {
        return id;
    }

    void setName(std::string name)
    {
        this->name = name;
    }

    std::string getName(void)
    {
        return name;
    }

    void setAffiliation(std::string affiliation)
    {
        this->affiliation = affiliation;
    }

    std::string getAffiliation(void)
    {
        return affiliation;
    }

    void setSolved(std::string solved)
    {
        this->solved = solved;
    }

    std::string getSolved(void)
    {
        return solved;
    }

    void setSolvedList(std::set<std::string> solved_list)
    {
        this->solved_list = solved_list;
    }

    std::set<std::string> getSolvedList(void)
    {
        return solved_list;
    }

    void displayInfo(void)
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
};

extern User parse4User(std::string);
extern User userSearchAPI(std::string);
extern std::set<User> parse4Users(std::string);
extern std::set<User> allUserListSearchAPI(std::string, std::string, std::string, std::string);
extern double differenceProblems(User, User);
extern std::set<User> getSimilarUsers(User);

extern std::string query (std::string);
