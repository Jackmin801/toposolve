#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class TSPSolver {
private:
    vector<vector<int>> distances;
    vector<vector<int>> dp;
    vector<vector<int>> parent;
    int n;

    int solve(int mask, int pos) {
        if (mask == ((1 << n) - 1)) {
            return distances[pos][0];
        }

        if (dp[mask][pos] != -1) {
            return dp[mask][pos];
        }

        int ans = numeric_limits<int>::max();
        for (int city = 0; city < n; city++) {
            if ((mask & (1 << city)) == 0) {
                int newAns = max(distances[pos][city], solve(mask | (1 << city), city));
                if (newAns < ans) {
                    ans = newAns;
                    parent[mask][pos] = city;
                }
            }
        }

        return dp[mask][pos] = ans;
    }

public:
    pair<int, vector<int>> solveTSP(const vector<vector<int>>& dist) {
        distances = dist;
        n = distances.size();
        
        dp.assign(1 << n, vector<int>(n, -1));
        parent.assign(1 << n, vector<int>(n, -1));

        int minCost = solve(1, 0);

        // Reconstruct path
        vector<int> path;
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

int main() {
    //vector<vector<int>> distances = {
        //{0, 10, 15, 0},
        //{10, 0, 35, 25},
        //{15, 35, 0, 30},
        //{20, 5, 30, 0}
    //};
    vector<vector<int>> distances = {
        // 24x24 matrix with realistic distances (representing city distances in km)
        {  0,  5, 85, 55, 65, 70, 45, 90, 35, 75, 50, 40, 85, 55, 25, 70, 80, 45, 65, 90, 75, 50, 40, 85},
        { 45,  0, 85, 80, 45, 95, 65, 40, 85, 55, 60, 70, 45, 90, 35, 75, 50, 40, 85, 55, 60, 70,  4, 45},
        { 85, 50,  0,  5, 85, 55, 65, 70, 45, 90, 35, 75, 50, 40, 85, 55, 60, 70, 80, 45, 65, 90, 75, 50},
        { 55, 80, 45,  0,  5, 80, 45, 95, 65, 40, 85, 55, 60, 70, 45, 90, 35, 75, 50, 40, 85, 55, 60, 70},
        { 65, 45, 85, 50,  0,  5, 85, 55, 65, 70, 45, 90, 35, 75, 50, 40, 85, 55, 60, 70, 80, 45, 65, 90},
        { 70, 95, 55, 80, 45,  0,  5, 80, 45, 95, 65, 40, 85, 55, 60, 70, 45, 90, 35, 75, 50, 40, 85, 55},
        { 45, 65, 65, 45, 85, 50,  0,  5, 85, 55, 65, 70, 45, 90, 35, 75, 50, 40, 85, 55, 60, 70, 80, 45},
        { 90, 40, 70, 95, 55, 80, 45,  0,  5, 80, 45, 95, 65, 40, 85, 55, 60, 70, 45, 90, 35, 75, 50, 40},
        { 35, 85, 45, 65, 65, 45, 85, 50,  0,  5, 85, 55, 65, 70, 45, 90, 35, 75, 50, 40, 85, 55, 60, 70},
        { 75, 55, 90, 40, 70, 95, 55, 80, 45,  0,  5, 80, 45, 95, 65, 40, 85, 55, 60, 70, 45, 90, 35, 75},
        { 50, 60, 35, 85, 45, 65, 65, 45, 85, 50,  0,  5, 85, 55, 65, 70, 45, 90, 35, 75, 50, 40, 85, 55},
        { 40, 70, 75, 55, 90, 40, 70, 95, 55, 80, 45,  0,  5, 80, 45, 95, 65, 40, 85, 55, 60, 70, 45, 90},
        { 85, 45, 50, 60, 35, 85, 45, 65, 65, 45, 85, 50,  0,  5, 85, 55, 65, 70, 45, 90, 35, 75, 50, 40},
        { 55, 90, 40, 70, 75, 55, 90, 40, 70, 95, 55, 80, 45,  0,  5, 80, 45, 95, 65, 40, 85, 55, 60, 70},
        { 60, 35, 85, 45, 50, 60, 35, 85, 45, 65, 65, 45, 85, 50,  0,  5, 85, 55, 65, 70, 45, 90, 35, 75},
        { 70, 75, 55, 90, 40, 70, 75, 55, 90, 40, 70, 95, 55, 80, 45,  0,  5, 80, 45, 95, 65, 40, 85, 55},
        { 80, 50, 60, 35, 85, 45, 50, 60, 35, 85, 45, 65, 65, 45, 85, 50,  0,  5, 85, 55, 65, 70, 45, 90},
        { 45, 40, 70, 75, 55, 90, 40, 70, 75, 55, 90, 40, 70, 95, 55, 80, 45,  0,  5, 80, 45, 95, 65, 40},
        { 65, 85, 80, 50, 60, 35, 85, 45, 50, 60, 35, 85, 45, 65, 65, 45, 85, 50,  0,  5, 85, 55, 65, 70},
        { 90, 55, 45, 40, 70, 75, 55, 90, 40, 70, 75, 55, 90, 40, 70, 95, 55, 80, 45,  0,  5, 80, 45, 95},
        { 75, 60, 65, 85, 80, 50, 60, 35, 85, 45, 50, 60, 35, 85, 45, 65, 65, 45, 85, 50,  0,  5, 85, 55},
        { 50, 70, 90, 55, 45, 40, 70, 75, 55, 90, 40, 70, 75, 55, 90, 40, 70, 95, 55, 80, 45,  0,  5,  5},
        { 40, 80,  5, 60, 65, 85, 80, 50, 60, 35, 85, 45, 50, 60, 35, 85, 45, 65, 65, 45, 85, 50,  0, 10},
        {  5, 45, 50, 70, 90, 55, 45, 40, 70, 75, 55, 90, 40, 70, 75, 55, 90, 40, 70, 95, 55, 80, 45,  0}
    };

    TSPSolver solver;
    auto [minDistance, path] = solver.solveTSP(distances);

    cout << "Minimum distance: " << minDistance << endl;
    cout << "Path: ";
    for (int city : path) {
        cout << city << " ";
    }
    cout << endl;

    // Test path
    int currMin = 0;
    for (int i = 1; i < path.size(); i++) {
        cout << "Distance from " << path[i - 1] << " to " << path[i] << ": " << distances[path[i - 1]][path[i]] << endl;
        currMin = max(distances[path[i - 1]][path[i]], currMin);
    }

    return 0;
}