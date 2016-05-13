#include <iostream>
#include <set>
#include <string>


class User {
  private:
    std::string id;
    std::string name;
    std::string affiliation;
    std::string solved;
    std::set<std::string> solved_list;

  public:
    User();
    User(std::string, std::string,
         std::string, std::string,
         std::set<std::string>);

    bool operator < (const User &) const;

    void setID(std::string);
    std::string getID(void);

    void setName(std::string);
    std::string getName(void);

    void setAffiliation(std::string);
    std::string getAffiliation(void);

    void setSolved(std::string);
    std::string getSolved(void);

    void setSolvedList(std::set<std::string>);
    std::set<std::string> getSolvedList(void);
    
    void displayInfo(void);
};

extern User parse4User(std::string);
extern User userSearchAPI(std::string);
extern std::set<User> parse4Users(std::string);
extern std::set<User> allUserListSearchAPI(std::string, std::string, std::string, std::string);
extern double differenceProblems(User, User);
extern std::set<User> getSimilarUsers(User);

extern std::string query (std::string);
