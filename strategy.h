#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <iostream>
#include <vector>

class Strategy {
    int score;
    std::vector<int> actions;
public:
    Strategy(const int);
    int& get_score();
    int& get_action(const int);
    void update_score(const int, const int);
    friend std::ostream& operator<<(std::ostream& os, const Strategy& strategy);
};

#endif
