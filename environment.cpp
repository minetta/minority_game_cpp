#include <random>
#include <vector>
#include "environment.h"

static std::mt19937 rng(34);

Environment::Environment(const int min_m) {
    for (int i = 0; i < min_m; ++i) {
        history.push_back(rng() % 2);
    }
}

std::vector<int> Environment::get_recent_history(const int m) {
    std::vector<int> recent_history;
    std::vector<int>::iterator itr = history.end() - m;
    for (; itr != history.end(); ++itr) {
        recent_history.push_back((*itr));
    }

    return recent_history;
}

void Environment::update_history(const int new_state) {
    history.push_back(new_state);
}

void Environment::update_attendance_history(const int attendance) {
    attendance_history.push_back(attendance);
}

std::ostream& operator<<(std::ostream& os, Environment& environment) {
    os << "History:" << std::endl;
    os << "\t";
    for (auto& state : environment.history) {
        os << state << " ";
    }

    os << std::endl;

    return os;
}
