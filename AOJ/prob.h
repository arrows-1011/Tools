#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>


class Prob {
  private:
    std::string id, name;
    std::string TL, sub, AC, WA, TLE, MLE, RE;

  public:
    Prob() {
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
         std::string RE) {

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

    bool operator < (const Prob p)const {
        if (id != p.id) {
            return id < p.id;
        }

        if (name != p.name) {
            return name < p.name;
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

    void set_info(std::string TL,
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

    std::string get_TL(void)
    {
        return TL;
    }

    std::string get_sub(void)
    {
        return sub;
    }

    std::string get_AC(void)
    {
        return AC;
    }

    std::string get_WA(void)
    {
        return WA;
    }

    std::string get_TLE(void)
    {
        return TLE;
    }

    std::string get_MLE(void)
    {
        return MLE;
    }

    std::string get_RE(void)
    {
        return RE;
    }

    void display_problem_info(void)
    {
        std::cout << "   ID : " + id   << std::endl;
        std::cout << " Name : " + name << std::endl;
        std::cout << "   TL : " + TL   << std::endl;
        std::cout << "  sub : " + sub  << std::endl;
        std::cout << "   AC : " + AC   << std::endl;
        std::cout << "   WA : " + WA   << std::endl;
        std::cout << "  TLE : " + TLE  << std::endl;
        std::cout << "  MLE : " + MLE  << std::endl;
        std::cout << "   RE : " + RE   << std::endl;
    }
};

extern Prob parse_4_problem(std::string);
extern Prob problem_search_API(std::string);
extern std::set<std::string> find_recommend_problems(std::string);

extern std::set<std::string> get_problist(std::string);
extern std::string query(std::string);
