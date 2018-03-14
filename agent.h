#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "strategy.h"

class Agent {
    std::vector<int> action_history;
    std::vector<int> winning_history;
    std::vector<Strategy> strategies;
public:
    Agent(const int s, const int m);
    int choose_action(const std::vector<int>& history);
    Strategy* get_best_strategy_ptr();
    std::vector<int>& get_action_history();
    std::vector<int>& get_winning_history();
    void update_action_history(const int action);
    void update_winning_history(const int new_state);
    void update_strategy_score(const std::vector<int>& history, const int new_state);
};

#endif
