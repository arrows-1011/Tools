#include <iostream>

#include "prob.h"
#include "user.h"


int main(void)
{
    std::string user_id = "s1210207";
    
    auto probs = findRecommendProblems(user_id);
    int rank = 0;

    for (auto p : probs) {
        ++rank;
        printf("Rank %02d: ", rank);
        std::cout << p << std::endl;
    }

    return 0;
}
