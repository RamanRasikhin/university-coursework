import matplotlib.pyplot as plt
import numpy as np
from time import time
from multiprocess import Pool, Process, Queue

x=np.linspace(-2, 1, 300)
y=np.linspace(-1.5, 1.5, 300)
x, y=np.meshgrid(x, y)
z= x + 1j * y
def mandel(z, q):
    p=np.copy(z)
    s=z.shape
    res = np.ones(s)*255
    for i in range(255):
        res[np.abs(z) > 2] = i
        z=z**2+p
    q.put(res)
    return None

n=6
q=Queue()
parts=np.split(z, n, axis=1)
mandel_res=[ Process(target=mandel, args=(i, q)) for i in parts ]
start=time()
for i in mandel_res:
    i.start()

print(time()-start)
res=np.hstack([q.get() for _ in range(n)])
# res=np.hstack(mandel_res)
plt.figure(figsize=(10, 10))
plt.imshow(res)
plt.show()
for i in mandel_res:
    i.join()