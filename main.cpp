#include <ctime>
#include <numeric>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include "agent.h"
#include "environment.h"

static const int S = 2;
static const int M = 16;
static const int N_AGENTS = 1001;
static const int N_ITERS = 10000;
static const int N_RUNS = 32;

void save_vector(const std::vector<int>& vec, const char* path)
{
    std::ofstream f;
    f.open(path);
    for (auto& value : vec) {
        f << value << ",";
    }
    f << "\n";
    f.close();
}

void game(std::vector<Agent>& agents, Environment& environment)
{
    // Get M recent history
    std::vector<int> history = environment.get_recent_history(M);

    // Get agents' action
    std::vector<int> actions;
    for (auto& agent : agents) {
        int action = agent.choose_action(history);
        agent.update_action_history(action);
        actions.emplace_back(action);
    }

    // Determine the new state
    int attendance = std::accumulate(actions.begin(), actions.end(), 0);
    int new_state;
    if (attendance > static_cast<float>(N_AGENTS) / 2.0) {
        new_state = 0;
    } else {
        new_state = 1;
    }

    // Update agents' winning history
    for (auto& agent : agents) {
        agent.update_strategy_score(history, new_state);
    }

    // Update the environemt
    environment.update_history(new_state);
    environment.update_attendance_history(attendance);
}

void run(const int r)
{
    // Initialize agents
    std::vector<Agent> agents;
    for (unsigned i = 0; i < N_AGENTS; ++i) {
        agents.emplace_back(Agent(S, M));
    }

    // Initialize environment
    Environment environment;

    // Iterate games
    for (unsigned i = 0; i < N_ITERS; ++i) {
        game(agents, environment);
    }

    // Save attendance history
    std::vector<int> attendance_history = environment.get_attendance_history();
    char attendance_path[100];
    sprintf(attendance_path, "results/m%d_s%d_nagents%d_niters%d_nruns%d/attendance_%d.csv", M, S, N_AGENTS, N_ITERS, N_RUNS, r + 1);
    save_vector(attendance_history, attendance_path);
}

int main()
{
    std::clock_t start, end;
    start = std::clock();

    // Create a directory
    char result_dir[100];
    sprintf(result_dir, "results/m%d_s%d_nagents%d_niters%d_nruns%d", M, S, N_AGENTS, N_ITERS, N_RUNS);
    mkdir(result_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    for (unsigned r = 0; r < N_RUNS; ++r) {
        run(r);
        end = std::clock();
        std::cout << "RUN: " << r + 1 << ", Time: " << (end - start) / 1000000 << "[s]" << std::endl;
    }

    return 0;
}
