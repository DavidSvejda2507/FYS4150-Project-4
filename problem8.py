import numpy as np
import matplotlib.pyplot as plt


data = np.genfromtxt(f"Data/Problem8/log.txt", dtype=str, comments="#")
        
observables = ["eps", "Cv", "abs_m", "chi"]

for L in (20,40,60,80,100):
    L_data = []
    for row in data:        
        if int(row[0]) == L:
            L_data.append(row)
    L_data = np.array(L_data)
    
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2,2)    
    axes = [ax1, ax2, ax3, ax4]
    
    T = L_data[:, 1].astype(float)
    
    for i, (obs, ax) in enumerate(zip(observables, axes)):
        ax.plot(T, L_data[:, i+3].astype(float), ".")
    
    
    plt.title(f"L={L}")
    plt.savefig(f"Data/Problem8/L={L}.png")