#include "prob.h"
#include "user.h"


// Problem Search API in AOJ
// Obtain detailed information of the specific problem.
Prob problemSearchAPI(std::string id)
{
    std::string url
        = "http://judge.u-aizu.ac.jp/onlinejudge/webservice/problem?";

    if (!id.empty()) {
        url += "id=" + id;
        url += "&status=false";
    } else {
        std::cerr << "Error: id is empty" << std::endl;
        exit(1);
    }

    std::string xml = query(url);
    Prob prob = parse4Problem(xml);

    return prob;
}

Prob parse4Problem(std::string xml)
{
    std::string id, name;
    std::string TL, sub, AC, WA, TLE, MLE, RE;

    std::string str;
    std::stringstream ss(xml);

    auto setElement = [](std::string &target, std::string str){
        target = str;
    };

    while (std::getline(ss, str, '\n')) {
        if (str == "<id>") {
            std::getline(ss, str, '\n');
            setElement(id, str);
        }

        if (str == "<name>") {
            std::getline(ss, str, '\n');
            setElement(name, str);
        }

        if (str == "<problemtimelimit>") {
            std::getline(ss, str, '\n');
            setElement(TL, str);
        }

        if (str == "<submission>") {
            std::getline(ss, str, '\n');
            setElement(sub, str);
        }

        if (str == "<accepted>") {
            std::getline(ss, str, '\n');
            setElement(AC, str);
        }

        if (str == "<wronganswer>") {
            std::getline(ss, str, '\n');
            setElement(WA, str);
        }

        if (str == "<timelimit>") {
            std::getline(ss, str, '\n');
            setElement(TLE, str);
        }

        if (str == "<memorylimit>") {
            std::getline(ss, str, '\n');
            setElement(MLE, str);
        }

        if (str == "<runtimeerror>") {
            std::getline(ss, str, '\n');
            setElement(RE, str);
        }
    }
    return Prob(id, name, TL, sub, AC, WA, TLE, MLE, RE);
}

std::set<std::string> getProbList(std::string id)
{
    std::string url =
        "http://judge.u-aizu.ac.jp/onlinejudge/webservice/solved_record?user_id=" + id;

    std::string str;
    std::string xml = query(url);
    std::stringstream ss(xml);

    std::set<std::string> probList;

    while (std::getline(ss, str, '\n')) {
        if (str == "<problem_id>") {
            std::getline(ss, str, '\n');
            probList.insert(str);
        }
    }

    return probList;
}

double differenceProblems(User u1, User u2)
{
    std::set<std::string> both_probs;
    std::set<std::string> onlyU1_probs;
    std::set<std::string> onlyU2_probs;

    std::set<std::string> u1_probs = u1.getSolvedList();
    std::set<std::string> u2_probs = u2.getSolvedList();

    for (auto p : u1_probs) {
        if (u2_probs.count(p) > 0) {
            both_probs.insert(p);
        } else {
            onlyU1_probs.insert(p);
        }
    }

    for (auto p : u2_probs) {
        if (u1_probs.count(p) == 0) {
            onlyU2_probs.insert(p);
        }
    }

    auto display = [=](User u1, User u2){
        std::cout << "Solved both " + u1.getID() + " and " + u2.getID() + " is ";
        std::cout << both_probs.size();
        std::cout << "problems" << std::endl;

        for (auto p : both_probs) {
            std::cout << p << " ";
        }

        std::cout << "\n\n";

        std::cout << "Solved only " + u1.getID() + " is ";
        std::cout << onlyU1_probs.size();
        std::cout << " problems" << std::endl;

        for (auto p : onlyU1_probs) {
            std::cout << p << " ";
        }

        std::cout << "\n\n";

        std::cout << "Solved only " + u2.getID() + " is ";
        std::cout << onlyU2_probs.size();
        std::cout << " problems" << std::endl;

        for (auto p : onlyU2_probs) {
            std::cout << p << " ";
        }
        std::cout << "\n\n";
    };

    // display(u1, u2);

    double both_solved = both_probs.size();
    double diff_rate = both_solved / std::max(u1_probs.size(), u2_probs.size());
    return diff_rate;
}

std::set<std::string> findRecommendProblems(std::string user_id)
{
    User user = userSearchAPI(user_id);
    std::set<User> sim_users = getSimilarUsers(user);

    std::map<std::string, int> probs_counter;

    auto getOnlyProb = [&user](std::set<std::string> probs){
        std::set<std::string> user_probs = user.getSolvedList();
        std::set<std::string> only_probs;
        for (auto p : probs) {
            if (user_probs.count(p) == 0) {
                only_probs.insert(p);
            }
        }
        return only_probs;
    };

    // Count problems that solved only similar users.
    for (auto u : sim_users) {
        std::set<std::string> probs =
            getOnlyProb(u.getSolvedList());

        for (auto p : probs) {
            probs_counter[p]++;
        }
    }

    // Find problems that other users are solving a lot.
    std::priority_queue<std::pair<int,std::string>> que;
    for (auto pr : probs_counter) {
        que.push(std::make_pair(pr.second, pr.first));
    }

    std::set<std::string> rec_probs;
    while (!que.empty()) {
        if (rec_probs.size() == 15) {
            break;
        }

        std::pair<int, std::string> prob_info = que.top();
        que.pop();
        rec_probs.insert(prob_info.second);
    }
    return rec_probs;
}
