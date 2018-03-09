#ifndef MINORITY_GAME_H_
#define MINORITY_GAME_H_

#include <vector>
#include "strategy.h"

class Agent {
    std::vector<int> action_history;
    std::vector<int> winning_history;
    std::vector<Strategy> strategies;
public:
    Agent(const int, const int);
    int& get_action(const std::vector<int>&);
    void update_action_history(const int);
    std::vector<int>& get_action_history();
    std::vector<int>& get_winning_history();
    void update_winning_history(const int);
    void update_scores(const std::vector<int>&, const int);
    Strategy* get_best_strategy_ptr();
};

#endif
