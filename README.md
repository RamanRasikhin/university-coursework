# University Coursework

Selected university projects and exercises in C++, Python and embedded C. The archive includes learning scaffolds and multiple unfinished variants; this index points to the more substantial examples and explains their limits.

## Start here

| Example | What it demonstrates | Verification |
| --- | --- | --- |
| [C++ Library Management](cpp/library-management/) | Classes, books/readers/employees, loans/reservations, CSV persistence and simulated dates | C++17 compile and CLI startup/exit |
| [Sensor Sorting](cpp/sensor-sorting/) | Quicksort with three-level ordering and a weighted checksum | 60 generated cases compared with an independent sorting oracle |
| [Mandelbrot](python/mandelbrot/) | Numerical arrays; serial/thread/process modes | Known complex points and cross-mode equality |
| [Cellular Automata](python/cellular-automata/) | Conway's Life using convolution and periodic boundaries | Still-life and period-two oscillator checks |
| [Numerical Modelling Notebook](python/numerical-modelling/) | Euler integration, Metropolis, percolation, Langton's ant and cellular simulations | Selected existing cells; not executed end to end |
| [8051 Clock](embedded/8051-clock/) | Timer interrupts, display multiplexing and keyboard scanning | Source review only; original hardware unavailable |

## Smaller exercises and lab history

- [Discrete mathematics](cpp/discrete-mathematics/): Ackermann and Sudan recursion, including call-counting variants.
- `python/1`, `2`, `3`, `5`, `6`: early Python and NumPy notebooks.
- `python/8`, `9`: PyQt interfaces and plotting exercises.
- `python/10`, `11`: networking/concurrency and original Mandelbrot variants.
- `python/12`, `14`, `paradygmaty python`, `zadanie domowe`: iterators, generators and programming-paradigm exercises.

Original lab filenames are retained for traceability. These folders are an archive of learning, not separately polished applications. Notebook outputs are cleared; environments, binaries, databases and exam scans are excluded.

## Running the checked examples

See each example's README for its requirements. Python demonstration checks:

```text
python -m pip install numpy scipy matplotlib
python python/test_showcases.py
```

The top-level requirements file also includes optional packages used by older labs. GUI notebooks and scripts require a desktop environment, and some original exercises may need additional packages or data.

## Provenance and cleanup

[SELECTION.md](SELECTION.md) records the source paths, packaging fixes and excluded examples. The larger Python dungeon generator from the local archive was identified as an unchanged copy of Tiendil's tutorial and is not presented here as my own project. Uncertain C++ game derivatives are also excluded pending a reconstruction of the changes.

C++ source packaging adds build instructions, standard headers and a signed empty-range bound. Python showcase packaging extracts reusable functions and fixes known escape-counting/process-startup issues; original lab variants are preserved. These maintenance changes are distinguished from the original coursework.
