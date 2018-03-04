#include <random>
#include <vector>
#include "environment.h"

static std::mt19937 rng(34);

Environment::Environment(const int min_m) {
    for (int i = 0; i < min_m; ++i) {
        history.push_back(rng() % 2);
    }
}

std::vector<int> Environment::get_latest_history_string(const int m) {
    std::vector<int> latest_history_string;
    std::vector<int>::iterator itr = history.end() - m;
    for (; itr != history.end(); ++itr) {
        latest_history_string.push_back((*itr));
    }

    return latest_history_string;
}

void Environment::update_history(const int new_state) {
    history.push_back(new_state);
}

void Environment::update_attendance_history(const int attencance) {
    attendance_history.push_back(attencance);
}

std::ostream& operator<<(std::ostream& os, Environment& environment) {
    os << "History:" << std::endl;
    os << "\t";
    std::vector<int>::iterator itr = environment.history.begin();
    for (; itr != environment.history.end(); ++itr) {
        os << *itr << " ";
    }
    os << std::endl;

    return os;
}
