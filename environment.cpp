#include <random>
#include "environment.h"

static std::mt19937 rng(34);

Environment::Environment()
{
}

std::vector<int> Environment::get_recent_history(const int m)
{
    std::vector<int> recent_history;

    if (m > this->history.size()) {
        for (unsigned i = 0; i < m; ++i) {
            recent_history.emplace_back(rng() % 2);
        }
    } else {
        for (auto iter = this->history.end() - m; iter != this->history.end(); ++iter) {
            recent_history.emplace_back(*iter);
        }
    }
    return recent_history;
}

std::vector<int>& Environment::get_attendance_history()
{
    return this->attendance_history;
}

void Environment::update_history(const int new_state)
{
    this->history.emplace_back(new_state);
}

void Environment::update_attendance_history(const int attendance)
{
    this->attendance_history.emplace_back(attendance);
}
