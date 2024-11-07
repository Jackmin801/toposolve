#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <limits>
#include <stdexcept>

namespace py = pybind11;

class TSPSolver {
private:
    std::vector<std::vector<int>> distances;
    std::vector<std::vector<int>> dp;
    std::vector<std::vector<int>> parent;
    int n;

    int solve(int mask, int pos) {
        if (mask == ((1 << n) - 1)) {
            return distances[pos][0];
        }

        if (dp[mask][pos] != -1) {
            return dp[mask][pos];
        }

        int ans = std::numeric_limits<int>::max();
        for (int city = 0; city < n; city++) {
            if ((mask & (1 << city)) == 0) {
                int newAns = std::max(distances[pos][city], solve(mask | (1 << city), city));
                if (newAns < ans) {
                    ans = newAns;
                    parent[mask][pos] = city;
                }
            }
        }

        return dp[mask][pos] = ans;
    }

public:
    std::pair<int, std::vector<int>> solveTSP(const std::vector<std::vector<int>>& dist) {
        // Input validation
        if (dist.empty()) {
            throw std::invalid_argument("Distance matrix cannot be empty");
        }
        
        n = dist.size();
        for (const auto& row : dist) {
            if (row.size() != n) {
                throw std::invalid_argument("Distance matrix must be square");
            }
        }
        
        if (n > 30) {  // Practical limit
            throw std::invalid_argument("Number of cities cannot exceed 30 due to computational limits");
        }

        distances = dist;
        dp.assign(1 << n, std::vector<int>(n, -1));
        parent.assign(1 << n, std::vector<int>(n, -1));

        int minCost = solve(1, 0);

        std::vector<int> path;
        path.push_back(0);
        
        int mask = 1;
        int pos = 0;
        
        while (mask != ((1 << n) - 1)) {
            int nextCity = parent[mask][pos];
            path.push_back(nextCity);
            mask |= (1 << nextCity);
            pos = nextCity;
        }
        path.push_back(0);

        return {minCost, path};
    }
};

PYBIND11_MODULE(_toposolve, m) {
    m.doc() = "Fast C++ implementation of the Held-Karp algorithm for solving TSP";

    py::class_<TSPSolver>(m, "TSPSolver")
        .def(py::init<>())
        .def("solve_tsp", &TSPSolver::solveTSP, 
             py::arg("distances"),
             "Solve the Traveling Salesman Problem using the Held-Karp algorithm.\n\n"
             "Args:\n"
             "    distances: List of lists containing integer distances between cities.\n\n"
             "Returns:\n"
             "    Tuple of (minimum distance, optimal path).\n\n"
             "Raises:\n"
             "    ValueError: If the input matrix is invalid or too large.");
}