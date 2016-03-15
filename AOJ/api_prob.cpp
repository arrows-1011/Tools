#include "prob.h"
#include "user.h"


// Problem Search API in AOJ
// Obtain detailed information of the specific problem.
Prob problem_search_API(std::string id)
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
    Prob prob = parse_4_problem(xml);

    return prob;
}

Prob parse_4_problem(std::string xml)
{
    std::string id, name;
    std::string TL, sub, AC, WA, TLE, MLE, RE;

    std::string str;
    std::stringstream ss(xml);

    auto set_element = [](std::string &target, std::string str){
        target = str;
    };

    while (std::getline(ss, str, '\n')) {
        if (str == "<id>") {
            std::getline(ss, str, '\n');
            set_element(id, str);
        }

        if (str == "<name>") {
            std::getline(ss, str, '\n');
            set_element(name, str);
        }

        if (str == "<problemtimelimit>") {
            std::getline(ss, str, '\n');
            set_element(TL, str);
        }

        if (str == "<submission>") {
            std::getline(ss, str, '\n');
            set_element(sub, str);
        }

        if (str == "<accepted>") {
            std::getline(ss, str, '\n');
            set_element(AC, str);
        }

        if (str == "<wronganswer>") {
            std::getline(ss, str, '\n');
            set_element(WA, str);
        }

        if (str == "<timelimit>") {
            std::getline(ss, str, '\n');
            set_element(TLE, str);
        }

        if (str == "<memorylimit>") {
            std::getline(ss, str, '\n');
            set_element(MLE, str);
        }

        if (str == "<runtimeerror>") {
            std::getline(ss, str, '\n');
            set_element(RE, str);
        }
    }
    return Prob(id, name, TL, sub, AC, WA, TLE, MLE, RE);
}

std::set<std::string> get_problist(std::string id)
{
    std::string url =
        "http://judge.u-aizu.ac.jp/onlinejudge/webservice/solved_record?user_id=" + id;

    std::string str;
    std::string xml = query(url);
    std::stringstream ss(xml);

    std::set<std::string> problist;

    while (std::getline(ss, str, '\n')) {
        if (str == "<problem_id>") {
            std::getline(ss, str, '\n');
            problist.insert(str);
        }
    }

    return problist;
}

void common_solved_problems(std::vector<User> users)
{
    std::set<std::string> common_probs;

    std::vector<std::set<std::string>> ui_probs(users.size());
    for (size_t i = 0; i < users.size(); i++) {
        ui_probs[i] = users[i].get_solvedlist();
    }

    for (auto p : ui_probs[0]) {
        bool is_common = 1;
        for (size_t i = 1; i < users.size(); i++) {
            if (ui_probs[i].count(p) == 0) {
                is_common = 0;
                break;
            }
        }
        if (is_common) {
            common_probs.insert(p);
        }
    }
    
    std::cout << "Common solved problems" << std::endl;
    int cnt = 0;
    for (auto p : common_probs) {
        std::cout << p;
        if (++cnt == 20) {
            std::cout << std::endl;
        }
    }

}

double difference_problems(std::string u1, std::string u2)
{
    User user1 = user_search_API(u1);
    User user2 = user_search_API(u2);
    return difference_problems(user1, user2);
}

double difference_problems(User u1, User u2)
{
    std::set<std::string> both_probs;
    std::set<std::string> only_u1_probs;
    std::set<std::string> only_u2_probs;

    std::set<std::string> u1_probs = u1.get_solvedlist();
    std::set<std::string> u2_probs = u2.get_solvedlist();

    for (auto p : u1_probs) {
        if (u2_probs.count(p) > 0) {
            both_probs.insert(p);
        } else {
            only_u1_probs.insert(p);
        }
    }

    for (auto p : u2_probs) {
        if (u1_probs.count(p) == 0) {
            only_u2_probs.insert(p);
        }
    }

    auto display = [=](User u1, User u2){
        std::cout << "Solved both " + u1.get_id() + " and " + u2.get_id() + " is ";
        std::cout << both_probs.size();
        std::cout << "problems" << std::endl;

        for (auto p : both_probs) {
            std::cout << p << " ";
        }

        std::cout << "\n\n";

        std::cout << "Solved only " + u1.get_id() + " is ";
        std::cout << only_u1_probs.size();
        std::cout << " problems" << std::endl;

        for (auto p : only_u1_probs) {
            std::cout << p << " ";
        }

        std::cout << "\n\n";

        std::cout << "Solved only " + u2.get_id() + " is ";
        std::cout << only_u2_probs.size();
        std::cout << " problems" << std::endl;

        for (auto p : only_u2_probs) {
            std::cout << p << " ";
        }
        std::cout << "\n\n";
    };

    display(u1, u2);

    double both_solved = both_probs.size();
    double diff_rate = both_solved / std::max(u1_probs.size(), u2_probs.size());
    return diff_rate;
}

std::set<std::string> find_recommend_problems(std::string user_id)
{
    User user = user_search_API(user_id);
    std::set<User> sim_users = get_similar_users(user);

    std::map<std::string, int> probs_counter;

    auto get_only_prob = [&user](std::set<std::string> probs){
        std::set<std::string> user_probs = user.get_solvedlist();
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
            get_only_prob(u.get_solvedlist());

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
