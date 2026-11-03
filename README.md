# University Coursework

A curated selection of C++ and Python exercises from university classes. This is a coursework archive: implementations vary in maturity and are preserved as learning examples.

## Contents

| Directory | Topics |
| --- | --- |
| `cpp/discrete-mathematics/` | Recursive Ackermann and Sudan functions, alternative implementations |
| `python/1/`, `2/`, `3/`, `5/`, `6/` | Python lab notebooks and exercises |
| `python/8/`, `9/` | PyQt interfaces and plotting examples |
| `python/10/`, `11/` | Notebooks and numerical/threading/process examples |
| `python/12/`, `14/`, `paradygmaty python/`, `zadanie domowe/` | Additional notebooks and programming-paradigm exercises |

Original exercise filenames are retained. Notebook outputs have been cleared. Virtual environments, binaries, exam scans, copied example games and duplicate notebook checkpoints are excluded.

## Python

Use a virtual environment and install only the packages required by the chosen exercise. Common dependencies found in this selection are listed in `requirements.txt`; they have not been version-pinned or validated as a single environment.

```powershell
python -m venv .venv
.\.venv\Scripts\python.exe -m pip install -r requirements.txt
.\.venv\Scripts\python.exe -m jupyter notebook
```

Run GUI scripts individually from a desktop Python environment. Some notebooks may require their original input data or additional packages.

## C++

Compile each source separately. For example, with a C++ compiler available:

```text
g++ -std=c++17 cpp/discrete-mathematics/ackerman/Program_1_A_Rasikhin_Raman.cpp -o ackermann
```

Keep recursive-function inputs small: time and memory grow quickly. The examples retain their original input handling and integer limits.
