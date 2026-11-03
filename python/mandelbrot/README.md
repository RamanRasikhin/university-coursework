# Mandelbrot: serial, threads and processes

A runnable cleanup of the university exercises archived in `python/11/`. The original variants are preserved there. The public demo adds a shared kernel, a CLI, first-escape counting and an `if __name__ == '__main__'` guard for Windows processes. These are portfolio-maintenance changes, not a claim that the original lab was already a standalone package.

```text
python -m pip install numpy matplotlib
python mandelbrot.py --mode serial --size 500 --output serial.png
python mandelbrot.py --mode threads --workers 4 --output threads.png
python mandelbrot.py --mode processes --workers 4 --output processes.png
```

The modes should produce identical arrays. Execution timings depend on array size, platform and process startup overhead; there is no claim that parallel modes are always faster. Existing archive variants compute escape counts differently, so use this shared-kernel demo when comparing modes.

![Output from the packaged Mandelbrot demo](../../docs/mandelbrot.png)
