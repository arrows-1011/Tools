#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <vector>


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

    void set_id(std::string id)
    {
        this->id = id;
    }

    std::string get_id(void)
    {
        return id;
    }

    void set_name(std::string name)
    {
        this->name = name;
    }

    std::string get_name(void)
    {
        return name;
    }

    void set_affiliation(std::string affiliation)
    {
        this->affiliation = affiliation;
    }

    std::string get_affiliation(void)
    {
        return affiliation;
    }

    void set_solved(std::string solved)
    {
        this->solved = solved;
    }

    std::string get_solved(void)
    {
        return solved;
    }

    void set_solvedlist(std::set<std::string> solved_list)
    {
        this->solved_list = solved_list;
    }

    std::set<std::string> get_solvedlist(void)
    {
        return solved_list;
    }

    void display_user_info(void)
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

extern User parse_4_user(std::string);
extern User user_search_API(std::string);
extern std::set<User> parse_4_users(std::string);
extern std::set<User> all_userlist_search_API(std::string, std::string, std::string, std::string);
extern void common_solved_problems(std::vector<User>);
extern double difference_problems(std::string, std::string);
extern double difference_problems(User, User);
extern std::set<User> get_similar_users(User);

extern std::string query(std::string);
