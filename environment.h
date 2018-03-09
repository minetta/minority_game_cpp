#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <iostream>
#include <vector>

class Environment {
    std::vector<int> history;
    std::vector<int> attendance_history;
public:
    Environment(const int);
    std::vector<int> get_recent_history(const int);
    void update_history(const int);
    void update_attendance_history(const int);
    std::vector<int>& get_attendance_history();
    friend std::ostream& operator<<(std::ostream& os, Environment& environment);
};

#endif
