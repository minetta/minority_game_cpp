#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <iostream>
#include <vector>

class Environment {
    std::vector<int> history;
    std::vector<int> attendance_history;
public:
    Environment();
    std::vector<int> get_recent_history(const int m);
    std::vector<int>& get_attendance_history();
    void update_history(const int new_state);
    void update_attendance_history(const int attendance);
};

#endif
