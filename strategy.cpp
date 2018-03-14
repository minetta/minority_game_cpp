#include <iostream>
#include <random>
#include "strategy.h"

static std::mt19937 rng(34);

Strategy::Strategy(const int p)
{
    this->score = 0;
    for (unsigned i = 0; i < p; ++i) {
        this->actions.emplace_back(rng() % 2);
    }
}

int Strategy::get_score()
{
    return this->score;
}

int Strategy::choose_action(const int history_n)
{
    return this->actions.at(history_n);
}

void Strategy::update_score(const int history_n, const int new_state)
{
    if (this->actions.at(history_n) == new_state) {
        this->score += 1;
    } else {
        this->score -= 1;
    }
}

std::ostream& operator<<(std::ostream& os, const Strategy& strategy)
{
    // score
    os << "score:" << std::endl;
    os << "\t" << strategy.score << std::endl;

    // actions
    os << "actions:" << std::endl;
    for (unsigned i = 0; i < strategy.actions.size(); ++i) {
        os << "\t" << i << ": " << strategy.actions.at(i) << std::endl;
    }
    return os;
}
