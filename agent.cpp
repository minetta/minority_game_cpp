#include <cmath>
#include "agent.h"
#include "utils.h"

static const int INF = 1001001001;

Agent::Agent(const int s, const int m)
{
    int p = std::pow(2, m); // number of histories
    for (unsigned i = 0; i < s; ++i) {
        this->strategies.emplace_back(Strategy(p));
    }
}

int Agent::choose_action(const std::vector<int>& history)
{
    Strategy* best_strategy_ptr = this->get_best_strategy_ptr();
    const unsigned history_n = utils::get_history_n(history);
    return best_strategy_ptr->choose_action(history_n);
}

Strategy* Agent::get_best_strategy_ptr()
{
    int best_score = -INF;
    Strategy* best_strategy_ptr = 0;
    for (auto& strategy : this->strategies) {
        if (strategy.get_score() > best_score) {
            best_score = strategy.get_score();
            best_strategy_ptr = &strategy;
        }
    }
    return best_strategy_ptr;
}

std::vector<int>& Agent::get_action_history()
{
    return this->action_history;
}

std::vector<int>& Agent::get_winning_history()
{
    return this->winning_history;
}

void Agent::update_action_history(const int action)
{
    this->action_history.emplace_back(action);
}

void Agent::update_winning_history(const int new_state)
{
    if (this->action_history.back() == new_state) {
        this->winning_history.emplace_back(1); // Win
    } else {
        this->winning_history.emplace_back(0); // Lose
    }
}

void Agent::update_strategy_score(const std::vector<int>& history, const int new_state)
{
    const int history_n = utils::get_history_n(history);
    for (auto& strategy : this->strategies) {
        strategy.update_score(history_n, new_state);
    }
}
