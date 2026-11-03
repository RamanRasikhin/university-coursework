# Conway's Game of Life

A packaged version of the convolution-based exercise in `py/python/7(kartkowka)/kartkowka_2_b.py`. The periodic-boundary convolution and B3/S23 rule are preserved. Packaging extracts a testable step function, defers GUI startup to main and adds size/seed options. The original exercise included animation scaffolding.

```text
python -m pip install numpy scipy matplotlib
python game_of_life.py --size 100 --seed 42
```

Behavior checks cover a stable 2x2 block and a period-two blinker. The earlier loop-based archive variant is not used here because its edge slicing does not implement the same periodic boundaries.
