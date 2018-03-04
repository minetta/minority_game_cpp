#include <vector>
#include <cmath>
#include <iostream>

int get_history_num(const std::vector<int>& history) {
    int history_num = 0;
    const int history_size = history.size();
    for (int i = 0; i < history_size; ++i) {
        int power = std::pow(2, history_size - i - 1);
        history_num += power * history.at(i);
    }
    return history_num;
}
