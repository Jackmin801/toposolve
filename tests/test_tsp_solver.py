from typing import List
import pytest
from toposolve import TSPSolver
import random
from itertools import permutations

def make_random_problem(n: int):
    distances = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(i + 1, n):
            distance = random.randint(1, 100)
            distances[i][j] = distances[j][i] = distance
    return distances


def solve_tsp_brute_force(distances: List[List[int]]):
    min_distance = float("inf")
    optimal_path = None
    for path in permutations(range(len(distances))):
        distance = max(distances[i][j] for i, j in zip(path, path[1:]))
        distance = max(distance, distances[path[-1]][path[0]])
        if distance < min_distance:
            min_distance = distance
            optimal_path = path
    return min_distance, list(optimal_path) + [0]

@pytest.mark.parametrize("problem_size", [5, 10])
def test_tsp(problem_size: int):
    distances = make_random_problem(problem_size)
    solver = TSPSolver()
    min_dist, path = solver.solve_tsp(distances)

    assert isinstance(min_dist, int)
    assert isinstance(path, list)
    assert len(path) == len(distances) + 1
    assert path[0] == path[-1] == 0

    min_dist_brute, path_brute = solve_tsp_brute_force(distances)
    
    print(min_dist, min_dist_brute)
    print(f"{path=} {path_brute=}")
    assert min_dist == min_dist_brute

def test_invalid_input():
    solver = TSPSolver()
    
    # Empty matrix
    with pytest.raises(ValueError):
        solver.solve_tsp([])
    
    # Non-square matrix
    with pytest.raises(ValueError):
        solver.solve_tsp([[0, 1], [1, 0, 2]])
    
    # Too many cities
    big_matrix = [[0] * 31 for _ in range(31)]
    with pytest.raises(ValueError):
        solver.solve_tsp(big_matrix)