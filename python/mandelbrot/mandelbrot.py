"""Runnable portfolio cleanup of the archived Mandelbrot parallelism exercises.

The archive variants live under ../11. This edition fixes first-escape counting,
shares one numerical kernel across modes and supports Windows process spawning.
"""
import argparse
from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor
from pathlib import Path
from time import perf_counter

import numpy as np


def escape_times(points, iterations=255):
    z = np.zeros_like(points, dtype=np.complex128)
    result = np.full(points.shape, iterations, dtype=np.int32)
    active = np.ones(points.shape, dtype=bool)
    for iteration in range(1, iterations + 1):
        z[active] = z[active] ** 2 + points[active]
        escaped = active & (np.abs(z) > 2)
        result[escaped] = iteration
        active[escaped] = False
        if not active.any():
            break
    return result


def compute(size=300, mode='serial', workers=4, iterations=255):
    if size < 2 or workers < 1 or iterations < 1:
        raise ValueError('size >= 2, workers >= 1 and iterations >= 1 are required')
    x, y = np.meshgrid(np.linspace(-2, 1, size), np.linspace(-1.5, 1.5, size))
    points = x + 1j * y
    if mode == 'serial':
        return escape_times(points, iterations)
    executor = {'threads': ThreadPoolExecutor, 'processes': ProcessPoolExecutor}[mode]
    chunks = np.array_split(points, min(workers, size), axis=0)
    with executor(max_workers=workers) as pool:
        results = list(pool.map(escape_times, chunks, [iterations] * len(chunks)))
    return np.vstack(results)


def main():
    parser = argparse.ArgumentParser(description='Render Mandelbrot with serial, threaded or process execution.')
    parser.add_argument('--mode', choices=['serial', 'threads', 'processes'], default='serial')
    parser.add_argument('--size', type=int, default=500)
    parser.add_argument('--workers', type=int, default=4)
    parser.add_argument('--output', type=Path, default=Path('mandelbrot.png'))
    args = parser.parse_args()
    start = perf_counter()
    result = compute(args.size, args.mode, args.workers)
    elapsed = perf_counter() - start
    import matplotlib
    matplotlib.use('Agg')
    from matplotlib import pyplot as plt
    plt.imsave(args.output, result, cmap='magma', origin='lower')
    print(f'{args.mode}: {elapsed:.3f}s; wrote {args.output}')


if __name__ == '__main__':
    main()
