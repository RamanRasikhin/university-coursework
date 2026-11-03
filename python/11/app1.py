import matplotlib.pyplot as plt
import numpy as np
from time import time
from threading import Thread

x = np.linspace(-2, 1, 300)
y = np.linspace(-1.5, 1.5, 300)
x, y = np.meshgrid(x, y)
z = x + 1j * y


def mandel(z):
    s = z.shape
    res = np.ones(s) * 255
    jednadzies = int(len(z) / 10)
    lista = []
    for i in range(10):
        lista.append(z[jednadzies * i:jednadzies * i + 1])
    #    print(lista)
    print(lista[1].shape)
    p = []
    for i in range(10):
        p = np.copy(lista[i])
    for i in range(255):
        for j in range(10):
            res[np.abs(lista[j]) > 2] = i
            lista[j] = lista[j] ** 2 + p
    return res


plt.figure(figsize=(10, 10))
start = time()
plt.imshow(mandel(z))
print(time() - start)
plt.show()