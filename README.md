# toposolve

A fast C++ implementation of the Held-Karp algorithm for solving the Traveling Salesman Problem (TSP) for ring-reduce tours, with Python bindings.
We solve a specific variant of TSP where the `dist(i, j)` is calculated as `min(max(dist(i, k), dist(k, j)) for k in range(n))`.

## Installation

```bash
pip install toposolve
```

## Usage

```python
from toposolve import TSPSolver

# Create distance matrix
distances = [
    [0, 10, 15, 20],
    [10, 0, 35, 25],
    [15, 35, 0, 30],
    [20, 25, 30, 0]
]

# Create solver instance
solver = TSPSolver()

# Solve TSP
min_distance, path = solver.solve_tsp(distances)

print(f"Minimum distance: {min_distance}")
print(f"Optimal path: {path}")
```

## Requirements

- Python 3.6+
- C++ compiler supporting C++17
- CMake 3.18+

## Building from source

```bash
git clone https://github.com/Jackmin801/toposolve
cd toposolve
pip install .
```

## Running tests

```bash
pip install pytest
pytest tests/
```

## License

MIT License