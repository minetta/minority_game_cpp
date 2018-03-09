#include <cmath>
#include <ctime>
#include <cstdio>
#include <random>
#include <vector>
#include <numeric>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include "environment.h"
#include "minority_game.h"

static const int S = 2;
static const int M = 2;
static const int N_AGENTS = 11;
static const int RANDOM_SEED = 34;
static const int N_ITERS = 10000;
static const int N_RUNS = 32;

void save_vector(const std::vector<int>& vec, const char* path)
{
    std::ofstream f;
    f.open(path);
    for (auto& x : vec) {
        f << x << ",";
    }
    f << "\n";
    f.close();
}

void save_2dvector(const std::vector<std::vector<int> > vecvec, const char* path)
{
    std::ofstream f;
    f.open(path);
    for (auto& vec : vecvec) {
        for (auto& v : vec) {
            f << v << ",";
        }
        f << "\n";
    }
    f.close();
}

// 1回のiterationをまわす関数
void iteration(std::vector<Agent>& agents, Environment& environment)
{
    // Get M recent history
    std::vector<int> history = environment.get_recent_history(M);

    // Get agents' actions
    std::vector<int> actions;
    for (auto& agent : agents) {
        int action = agent.get_action(history);
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
        agent.update_winning_history(new_state);
    }

    // Update strategies' score
    for (auto& agent : agents) {
        agent.update_scores(history, new_state);
    }

    // Update the environment
    environment.update_history(new_state);
    environment.update_attendance_history(attendance);

    // std::cout << attendance << std::endl;
}

void run(const int r)
{
    // Initialize agents
    std::vector<Agent> agents;
    for (unsigned i = 0; i < N_AGENTS; ++i) {
        agents.emplace_back(Agent(S, M));
    }

    // Initialize environment
    Environment environment(M);

    // Iterate agmes
    for (unsigned itr = 0; itr < N_ITERS; ++itr) {
        iteration(agents, environment);
    }

    // Get attendance history
    std::vector<int> attendance_history = environment.get_attendance_history();
    char attendance_path[100];
    sprintf(attendance_path, "results/m%d_s%d_nagents%d_niters%d_nruns%d/attendance_%d.csv", M, S, N_AGENTS, N_ITERS, N_RUNS, r);
    save_vector(attendance_history, attendance_path);

    // Save action histories
    std::vector<std::vector<int> > action_histories;
    for (auto& agent : agents) {
        action_histories.emplace_back(agent.get_action_history());
    }
    char action_path[100];
    sprintf(action_path, "results/m%d_s%d_nagents%d_niters%d_nruns%d/action_histories_%d.csv", M, S, N_AGENTS, N_ITERS, N_RUNS, r);
    save_2dvector(action_histories, action_path);

    // Save winning histories
    std::vector<std::vector<int> > winning_histories;
    for (auto& agent : agents) {
        winning_histories.emplace_back(agent.get_winning_history());
    }
    char winning_path[100];
    sprintf(winning_path, "results/m%d_s%d_nagents%d_niters%d_nruns%d/winning_histories_%d.csv", M, S, N_AGENTS, N_ITERS, N_RUNS, r);
    save_2dvector(winning_histories, winning_path);
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
