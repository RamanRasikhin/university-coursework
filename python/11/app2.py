import matplotlib.pyplot as plt
import numpy as np
from time import time
from threading import Thread

x = np.linspace(-2, 1, 300)
y = np.linspace(-1.5, 1.5, 300)
x, y = np.meshgrid(x, y)
z = x + 1j * y
s = z.shape
res = np.ones(s) * 255

def mandel_part(z_part, res_part, offset):
    p = np.copy(z_part)
    for i in range(255):
        mask = np.abs(z_part) > 2
        res_part[mask] = np.minimum(res_part[mask], i)
        z_part = z_part**2 + p
    res[offset:offset + z_part.shape[0], :] = res_part

threads = []
n_threads = 10
rows_per_thread = s[0] // n_threads

start = time()
for i in range(n_threads):
    start_row = i * rows_per_thread
    end_row = (i + 1) * rows_per_thread if i < n_threads - 1 else s[0]
    z_part = z[start_row:end_row, :]
    res_part = np.ones_like(z_part) * 255
    t = Thread(target=mandel_part, args=(z_part, res_part, start_row))
    threads.append(t)
    t.start()

for t in threads:
    t.join()

print(time() - start)

plt.figure(figsize=(10, 10))
plt.imshow(res)
plt.axis('off')
plt.show()
