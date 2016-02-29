#include "user.h"
#include "prob.h"


// Check user id is valid or not.
// id can use characters alphabet, numbers(0 to 9),
// and under bar.
bool validUserID(std::string id)
{
    std::regex pattern("[a-zA-Z0-9_]+");
    return std::regex_match(id, pattern);
}

// User Search API in AOJ
// Obtain detailed information of the specific user.
User userSearchAPI(std::string id)
{
    if (!validUserID(id)) {
        std::cerr << "Error: Invalid user id" << std::endl;
        exit(1);
    }

    std::string url
        = "http://judge.u-aizu.ac.jp/onlinejudge/webservice/user?id=";

    url += id;

    std::string xml = query(url);
    User user = parse4User(xml);
    return user;
}

User parse4User(std::string xml)
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

std::set<User> parse4Users(std::string xml)
{
    std::set<User> users;

    std::string str;
    std::stringstream ss(xml);

    while (std::getline(ss, str, '\n')) {
        if (str == "<id>") {
            User user;
            readLine(1, ss, str) // str := ID
            user.setID(str);

            readLine(3, ss, str) // str := Name
            user.setName(str);

            readLine(3, ss, str) // str := Affiliation
            user.setAffiliation(str);

            readLine(3, ss, str) // str := solved
            user.setSolved(str);

            std::set<std::string> probList
                = getProbList(user.getID());

            user.setSolvedList(probList);
            users.insert(user);

            sleep(1);
        }
    }
    return users;
}

// All User List (Rank List) Search API in AOJ.
std::set<User> allUserListSearchAPI(std::string affiliation,
                                    std::string criteria,
                                    std::string solved_min,
                                    std::string solved_max)
{
    std::string url
        = "http://judge.u-aizu.ac.jp/onlinejudge/webservice/user_list?";

    bool usedField = 0;

    if (!affiliation.empty()) {
        url += "affiliation=" + affiliation;
        usedField = 1;
    }

    if (!criteria.empty()) {
        url += (usedField ? "&" : "");
        url += "criteria=" + criteria;
        usedField = 1;
    }

    if (!solved_min.empty()) {
        url += (usedField ? "&" : "");
        url += "solved_min=" + solved_min;
        usedField = 1;
    }

    if (!solved_max.empty()) {
        url += (usedField ? "&" : "");
        url += "solved_max=" + solved_max;
    }

    std::string xml = query(url);
    std::set<User> users = parse4Users(xml);

    auto display = [=](){
        for (auto user : users) {
            user.displayInfo();
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

std::set<User> getSimilarUsers(User user)
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

    std::string str = user.getSolved();
    int solved = s2i(str);
    int min = std::max(MIN, solved - OFFSET);
    int max = std::min(MAX, solved + OFFSET);

    std::set<User> users = allUserListSearchAPI("", "", i2s(min), i2s(max));
    std::set<User> sim_users;

    for (auto u : users) {
        if (u.getID() == user.getID()) {
            continue;
        }

        double diff_rate = differenceProblems(user, u);
        if (diff_rate >= RATE) {
            sim_users.insert(u);
        }
    }
    return sim_users;
}
