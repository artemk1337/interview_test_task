import numpy as np
from tqdm import tqdm


shape = (10000, 10000)
arr = np.random.randint(2, size=shape)
print(arr.shape)

with open("test.txt", "w") as f:
    for i in tqdm(range(arr.shape[0])):
        f.write("".join(f"{arr[i][k]}" for k in range(arr.shape[1])) + "\n")
