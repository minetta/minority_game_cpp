#ifndef UTILS_H_
#define UTILS_H_

#include <fstream>
#include <vector>
#include <cmath>

namespace utils {

int get_history_num(const std::vector<int>& history) {
    int history_num = 0;
    const int history_size = history.size();
    for (unsigned i = 0; i < history_size; ++i) {
        int power = std::pow(2, history_size - i - 1);
        history_num += power * history.at(i);
    }
    return history_num;
}


// void save_vector(const std::vector<int>& vec, const char* path)
// {
//     std::ofstream f;
//     f.open(path);
//     for (auto& x : vec) {
//         f << x << "\n";
//     }
//     f.close();
// }

} // namespace utils

#endif
