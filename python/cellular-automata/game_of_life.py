"""Packaged version of the archived convolution-based cellular automaton exercise."""
import argparse
import numpy as np
from scipy.signal import convolve2d


def step(grid):
    kernel = np.ones((3, 3), dtype=np.int8)
    kernel[1, 1] = 0
    neighbors = convolve2d(grid, kernel, mode='same', boundary='wrap')
    return ((neighbors == 3) | ((grid != 0) & (neighbors == 2))).astype(np.int8)


def main():
    parser = argparse.ArgumentParser(description="Conway's Game of Life with periodic boundaries.")
    parser.add_argument('--size', type=int, default=100)
    parser.add_argument('--seed', type=int, default=42)
    args = parser.parse_args()
    if args.size < 3:
        parser.error('size must be at least 3')
    grid = np.random.default_rng(args.seed).integers(0, 2, (args.size, args.size), dtype=np.int8)
    from matplotlib import pyplot as plt
    from matplotlib.animation import FuncAnimation
    fig, ax = plt.subplots()
    image = ax.imshow(grid, cmap='binary', vmin=0, vmax=1)
    ax.set_title("Conway's Game of Life — periodic boundaries")
    def update(_):
        nonlocal grid
        grid = step(grid)
        image.set_data(grid)
        return (image,)
    animation = FuncAnimation(fig, update, frames=200, interval=50, blit=True)
    plt.show()


if __name__ == '__main__':
    main()
