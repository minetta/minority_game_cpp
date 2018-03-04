#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <numeric>
#include "strategy.h"
#include "agent.h"
#include "environment.h"

static const int S = 2;
static const int M = 4;
static const int N_AGENTS = 101;
static const int RANDOM_SEED = 34;
static const int N_ITERS = 100;

int main()
{
    std::clock_t start, end;
    start = std::clock();

    // Initialize agents
    std::vector<Agent> agents;
    for (int i = 0; i < N_AGENTS; ++i) {
        agents.push_back(Agent(S, M));
    }

    // Initialize environment
    Environment environment(M);

    // Iteration
    for (int itr = 0; itr < N_ITERS; ++itr) {
        // M latest history string
        std::vector<int> history_string = environment.get_latest_history_string(M);

        // Get agents' actions
        std::vector<int> actions;
        for (auto& agent : agents) {
            int action = agent.get_action(history_string);
            actions.push_back(action);
        }
        // Determine new state
        int attencance = std::accumulate(actions.begin(), actions.end(), 0);
        int new_state;
        if (attencance > static_cast<int>(N_AGENTS) / 2) {
            new_state = 0;
        } else {
            new_state = 1;
        }

        // Update strategies' score
        for (auto& agent : agents) {
            agent.update_scores(history_string, new_state);
        }

        // Update environment
        environment.update_history(new_state);
        environment.update_attendance_history(attencance);

        std::cout << attencance << std::endl;
    }

    return 0;
}
