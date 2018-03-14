#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <iostream>
#include <vector>

class Strategy {
    int score;
    std::vector<int> actions;
public:
    Strategy(const int p);
    int get_score();
    int choose_action(const int history_n);
    void update_score(const int history_n, const int new_state);
    friend std::ostream& operator<<(std::ostream& os, const Strategy& strategy);
};

#endif
