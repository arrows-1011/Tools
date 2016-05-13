#include <iostream>
#include <set>
#include <string>


class Prob {
  private:
    std::string id, name;
    std::string TL, sub, AC, WA, TLE, MLE, RE;

  public:
    Prob();

    Prob(std::string, std::string, std::string,
         std::string, std::string, std::string,
         std::string, std::string, std::string);
    
    bool operator < (const Prob p) const;

    void setID(std::string id);
    std::string getID(void);
    
    void setName(std::string name);
    std::string getName(void);

    void setInfo(std::string, std::string,
                 std::string, std::string,
                 std::string, std::string,
                 std::string);

    std::string getTL(void);
    std::string getSub(void);
    std::string getAC(void);
    std::string getWA(void);
    std::string getTLE(void);
    std::string getMLE(void);
    std::string getRE(void);

    void displayInfo(void);
};

extern Prob parse4Problem(std::string);
extern Prob problemSearchAPI(std::string);
extern std::set<std::string> findRecommendProblems(std::string);

extern std::set<std::string> getProbList(std::string);
extern std::string query(std::string);
