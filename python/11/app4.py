import matplotlib.pyplot as plt
import numpy as np
from time import time
from threading import Thread
from multiprocess import Pool

x=np.linspace(-2, 1, 300)
y=np.linspace(-1.5, 1.5, 300)
x, y=np.meshgrid(x, y)
z= x + 1j * y
def mandel(z):
    p=np.copy(z)
    s=z.shape
    res = np.ones(s)*255
    for i in range(255):
        res[np.abs(z) > 2] = i
        z=z**2+p
    return res
start=time()
n=10
p=Pool()
parts=np.split(z, n, axis=1)
mandel_res=p.map(mandel, parts)
print(time()-start)
res=np.hstack(mandel_res)
plt.figure(figsize=(10, 10))
plt.imshow(res)
plt.show()