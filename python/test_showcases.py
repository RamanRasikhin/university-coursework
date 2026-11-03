"""Behavioral checks for the packaged numerical demonstrations."""
from pathlib import Path
import importlib.util
import sys
import unittest
import numpy as np


def load(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


ROOT = Path(__file__).parent
# An importable module name is needed for Windows multiprocessing.
sys.path.insert(0, str(ROOT / 'mandelbrot'))
import mandelbrot
life = load('game_of_life', ROOT / 'cellular-automata/game_of_life.py')


class ShowcaseTests(unittest.TestCase):
    def test_known_complex_points(self):
        actual = mandelbrot.escape_times(np.array([0j, -1+0j, 2+0j]), iterations=20)
        np.testing.assert_array_equal(actual, [20, 20, 2])

    def test_modes_produce_identical_results(self):
        serial = mandelbrot.compute(24, 'serial', 2, 30)
        for mode in ['threads', 'processes']:
            np.testing.assert_array_equal(serial, mandelbrot.compute(24, mode, 2, 30))

    def test_life_blinker_period_two(self):
        grid = np.zeros((7, 7), dtype=np.int8)
        grid[3, 2:5] = 1
        vertical = np.zeros_like(grid)
        vertical[2:5, 3] = 1
        np.testing.assert_array_equal(life.step(grid), vertical)
        np.testing.assert_array_equal(life.step(life.step(grid)), grid)

    def test_life_still_block(self):
        grid = np.zeros((6, 6), dtype=np.int8)
        grid[2:4, 2:4] = 1
        np.testing.assert_array_equal(life.step(grid), grid)


if __name__ == '__main__':
    unittest.main()
