#include <vector>
#include <cmath>
#include <iostream>

int get_history_string_num(const std::vector<int>& history_string) {
    int history_string_num = 0;
    const int history_string_size = history_string.size();
    for (int i = 0; i < history_string_size; ++i) {
        int power = std::pow(2, history_string_size - i - 1);
        history_string_num += power * history_string.at(i);
    }
    return history_string_num;
}
