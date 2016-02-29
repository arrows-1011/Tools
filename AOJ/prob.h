#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>


class Prob
{
  private:
    std::string id, name;
    std::string TL, sub, AC, WA, TLE, MLE, RE;

  public:
    Prob(){
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

    Prob(std::string id,
         std::string name,
         std::string TL,
         std::string sub,
         std::string AC,
         std::string WA,
         std::string TLE,
         std::string MLE,
         std::string RE){

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

    bool operator < (const Prob p)const{
        if (id != p.id) {
            return id < p.id;
        }

        if (name != p.name) {
            return name < p.name;
        }

        return 0;
    }

    void setID(std::string id){
        this->id = id;
    }

    std::string getID(void){
        return id;
    }

    void setName(std::string name){
        this->name = name;
    }

    std::string getName(void){
        return name;
    }

    void setInfo(std::string TL,
                 std::string sub,
                 std::string AC,
                 std::string WA,
                 std::string TLE,
                 std::string MLE,
                 std::string RE){

        this->TL  = TL;
        this->sub = sub;
        this->AC  = AC;
        this->WA  = WA;
        this->TLE = TLE;
        this->MLE = MLE;
        this->RE  = RE;
    }

    std::string getTL(void){
        return TL;
    }

    std::string getSub(void){
        return sub;
    }

    std::string getAC(void){
        return AC;
    }

    std::string getWA(void){
        return WA;
    }

    std::string getTLE(void){
        return TLE;
    }

    std::string getMLE(void){
        return MLE;
    }

    std::string getRE(void){
        return RE;
    }

    void displayInfo(void){
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
};

extern Prob parse4Problem(std::string);
extern Prob problemSearchAPI(std::string);
extern std::set<std::string> findRecommendProblems(std::string);

extern std::set<std::string> getProbList(std::string);
extern std::string query(std::string);