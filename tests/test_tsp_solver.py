import pytest
from toposolve import TSPSolver

def test_small_tsp():
    distances = [
        [0, 10, 15, 20],
        [10, 0, 35, 25],
        [15, 35, 0, 30],
        [20, 25, 30, 0]
    ]
    
    solver = TSPSolver()
    min_dist, path = solver.solve_tsp(distances)
    
    assert isinstance(min_dist, int)
    assert isinstance(path, list)
    assert len(path) == len(distances) + 1
    assert path[0] == path[-1] == 0

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