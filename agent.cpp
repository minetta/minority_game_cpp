#include <cmath>
#include <iostream>
#include "agent.h"
#include "utils.h"

Agent::Agent(const int s, const int m) {
    for (int i = 0; i < s; ++i) {
        int n_histories = std::pow(2, m);
        strategies.push_back(Strategy(n_histories));
    }
}

int Agent::get_action(const std::vector<int>& history) {
    Strategy* best_strategy_ptr = get_best_strategy_ptr();
    const int history_num = get_history_num(history);
    const int action = (*best_strategy_ptr).get_action(history_num);
    return action;
}

void Agent::update_scores(const std::vector<int>& history, const int new_state) {
    const int history_num = get_history_num(history);
    for (auto& strategy : strategies) {
        strategy.update_score(history_num, new_state);
    }
}

Strategy* Agent::get_best_strategy_ptr() {
    int best_score = -100000;
    Strategy* best_strategy_ptr = 0;
    for (auto& strategy : strategies) {
        if (strategy.get_score() > best_score) {
            best_score = strategy.get_score();
            best_strategy_ptr = &strategy;
        }
    }

    return best_strategy_ptr;
}
