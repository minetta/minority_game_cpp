#include <cmath>
#include <iostream>
#include "minority_game.h"
#include "utils.h"

Agent::Agent(const int s, const int m) {
    for (unsigned i = 0; i < s; ++i) {
        int n_histories = std::pow(2, m);
        strategies.emplace_back(Strategy(n_histories));
    }
}

void Agent::update_action_history(const int action) {
    action_history.emplace_back(action);
}

std::vector<int>& Agent::get_action_history() {
    return action_history;
}

std::vector<int>& Agent::get_winning_history() {
    return winning_history;
}

void Agent::update_winning_history(const int state) {
    if (action_history.back() == state) {
        winning_history.emplace_back(1); // Win
    } else {
        winning_history.emplace_back(0); // Lose
    }
}

int& Agent::get_action(const std::vector<int>& history) {
    Strategy* best_strategy_ptr = get_best_strategy_ptr();
    const int history_num = utils::get_history_num(history);
    return (*best_strategy_ptr).get_action(history_num);
}

void Agent::update_scores(const std::vector<int>& history, const int new_state) {
    const int history_num = utils::get_history_num(history);
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
