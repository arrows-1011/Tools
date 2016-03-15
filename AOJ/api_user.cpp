#include "user.h"
#include "prob.h"


// Check user id is valid or not.
// id can use characters alphabet, numbers(0 to 9),
// and under bar.
bool valid_user_id(std::string id)
{
    std::regex pattern("[a-zA-Z0-9_]+");
    return std::regex_match(id, pattern);
}

// User Search API in AOJ
// Obtain detailed information of the specific user.
User user_search_API(std::string id)
{
    if (!valid_user_id(id)) {
        std::cerr << "Error: Invalid user id" << std::endl;
        exit(1);
    }

    std::string url
        = "http://judge.u-aizu.ac.jp/onlinejudge/webservice/user?id=";

    url += id;

    std::string xml = query(url);
    User user = parse_4_user(xml);
    return user;
}

User parse_4_user(std::string xml)
{
    std::string id, name, affiliation, solved;
    std::set<std::string> solved_list;

    std::string str;
    std::stringstream ss(xml);

    const std::regex re_id("<id>.*</id>");
    const std::regex re_name("<name>.*</name>");
    const std::regex re_affiliation("<affiliation>.*</affiliation>");
    const std::regex re_solved("<solved>.*</solved>");

    while (std::getline(ss, str, '\n')) {
        if (str == "<solved_list>") {
            break;
        }

        if (std::regex_match(str, re_id)) {
            id = str.substr(4, str.size()-9);
        }

        if (std::regex_match(str, re_name)) {
            name = str.substr(6, str.size()-13);
        }

        if (std::regex_match(str, re_affiliation)) {
            affiliation = str.substr(13, str.size()-27);
        }

        if (std::regex_match(str, re_solved)) {
            solved = str.substr(8, str.size()-17);
        }
    }

    while (std::getline(ss, str, '\n')) {
        if (std::regex_match(str, re_id)) {
            str = str.substr(4, str.size()-9);
            solved_list.insert(str);
        }
    }

    return User(id, name, affiliation, solved, solved_list);
}

#define readLine(N, ss, str)                    \
    for (int i = 0 ; i < N ; i++) {             \
        std::getline(ss, str, '\n');            \
    }                                           \

std::set<User> parse_4_users(std::string xml)
{
    std::set<User> users;

    std::string str;
    std::stringstream ss(xml);

    while (std::getline(ss, str, '\n')) {
        if (str == "<id>") {
            User user;
            readLine(1, ss, str) // str := ID
            user.set_id(str);

            readLine(3, ss, str) // str := Name
            user.set_name(str);

            readLine(3, ss, str) // str := Affiliation
            user.set_affiliation(str);

            readLine(3, ss, str) // str := solved
            user.set_solved(str);

            std::set<std::string> problist
                = get_problist(user.get_id());

            user.set_solvedlist(problist);
            users.insert(user);

            sleep(1);
        }
    }
    return users;
}

// All User List (Rank List) Search API in AOJ.
std::set<User> all_userlist_search_API(std::string affiliation,
                                       std::string criteria,
                                       std::string solved_min,
                                       std::string solved_max)
{
    std::string url
        = "http://judge.u-aizu.ac.jp/onlinejudge/webservice/user_list?";

    bool used_field = 0;

    if (!affiliation.empty()) {
        url += "affiliation=" + affiliation;
        used_field = 1;
    }

    if (!criteria.empty()) {
        url += (used_field ? "&" : "");
        url += "criteria=" + criteria;
        used_field = 1;
    }

    if (!solved_min.empty()) {
        url += (used_field ? "&" : "");
        url += "solved_min=" + solved_min;
        used_field = 1;
    }

    if (!solved_max.empty()) {
        url += (used_field ? "&" : "");
        url += "solved_max=" + solved_max;
    }

    std::string xml = query(url);
    std::set<User> users = parse_4_users(xml);

    auto display = [=](){
        for (auto user : users) {
            user.display_user_info();
            std::cout << std::endl;
        }
    };

    // display();
    return users;
}

#define MAX    1250      // The maximum of solved.
#define MIN       0      // The minimum of solved.
#define OFFSET   50      // The offset of the number of solved.
#define RATE    0.7      // The rate of whether two users are similar or not.

std::set<User> get_similar_users(User user)
{
    auto s2i = [](std::string s){
        std::stringstream ss; ss << s;
        int v; ss >> v;
        return v;
    };

    auto i2s = [](int v){
        std::stringstream ss; ss << v;
        std::string s; ss >> s;
        return s;
    };

    std::string str = user.get_solved();
    int solved = s2i(str);
    int min = std::max(MIN, solved - OFFSET);
    int max = std::min(MAX, solved + OFFSET);

    std::set<User> users = all_userlist_search_API("", "", i2s(min), i2s(max));
    std::set<User> sim_users;

    for (auto u : users) {
        if (u.get_id() == user.get_id()) {
            continue;
        }

        double diff_rate = difference_problems(user, u);
        if (diff_rate >= RATE) {
            sim_users.insert(u);
        }
    }
    return sim_users;
}
