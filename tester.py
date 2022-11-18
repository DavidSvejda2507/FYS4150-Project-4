import numpy as np
import matplotlib.pyplot as plt


data = np.genfromtxt("Data/Test.txt", float, delimiter="\t")

for i in range(4):
    plt.plot(data[:10000,i])
plt.grid(True)
plt.savefig("Data/Test_fig.png")