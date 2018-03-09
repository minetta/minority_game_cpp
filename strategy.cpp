#include <iostream>
#include <random>
#include "strategy.h"

static std::mt19937 rng(34);

Strategy::Strategy(const int n_histories) {
    score = 0;
    for (int i = 0; i < n_histories; ++i) {
        actions.emplace_back(rng() % 2);
    }
}

int& Strategy::get_score() {
    return score;
}

int& Strategy::get_action(const int history_num) {
    return actions.at(history_num);
}

void Strategy::update_score(const int history_num, const int new_state) {
    if (actions.at(history_num) == new_state) {
        score += 1;
    } else {
        score -= 1;
    }
}

std::ostream& operator<<(std::ostream& os, const Strategy& strategy) {
    // score
    os << "score:" << std::endl;
    os << "\t" << strategy.score << std::endl;

    // actions
    os << "actions:" << std::endl;
    for (int i = 0; i < strategy.actions.size(); ++i) {
        os << "\t" << i << ": " << strategy.actions.at(i) << std::endl;
    }

    os << std::endl;

    return os;
}
