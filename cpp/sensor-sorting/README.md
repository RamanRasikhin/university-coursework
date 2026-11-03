# Multi-key sensor sorting

A C++ coursework task implementing quicksort with a compound comparator: location ascending, sensor number ascending, measurement value descending. It prints the sum of `value * zero-based position` after sorting.

Original source: `C++ progs/clion papka/untitled2/main.cpp`. The packaging makes the empty-input quicksort bound explicitly signed. Other logic is preserved.

```text
g++ -std=c++17 main.cpp -o sensor_sort
```

Input begins with a non-negative record count, followed by `location sensor value` records. Example:

```text
4
B 1 5
A 2 7
A 1 3
A 1 9
```

Expected output: `32`. Recursive quicksort retains its quadratic worst case; this is an exercise implementation.
