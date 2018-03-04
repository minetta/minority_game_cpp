#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "strategy.h"

class Agent {
    std::vector<Strategy> strategies;
public:
    Agent(const int, const int);
    int get_action(const std::vector<int>&);
    void update_scores(const std::vector<int>&, const int);
    Strategy* get_best_strategy_ptr();
};

#endif
