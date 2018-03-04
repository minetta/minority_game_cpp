#include <cmath>
#include <iostream>
#include "agent.h"
#include "utils.h"

Agent::Agent(const int s, const int m) {
    for (int i = 0; i < s; ++i) {
        int n_actions = std::pow(2, m);
        strategies.push_back(Strategy(n_actions));
    }
}

int Agent::get_action(const std::vector<int>& history_string) {
    Strategy* best_strategy_ptr = get_best_strategy_ptr();
    const int history_string_num = get_history_string_num(history_string);
    const int action = (*best_strategy_ptr).get_action(history_string_num);
    return action;
}

void Agent::update_scores(const std::vector<int>& history_string, const int new_state) {
    const int history_string_num = get_history_string_num(history_string);
    for (auto& strategy : strategies) {
        strategy.update_score(history_string_num, new_state);
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
