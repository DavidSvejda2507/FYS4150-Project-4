import numpy as np
import matplotlib.pyplot as plt

#reads file consisting of: epsilon, abs_m, Cv, chi
data = []
for T in ("1","2.4"):
    for A in (0,1):
        data.append((np.genfromtxt(f"Data/Problem5/T_{T}_A_{A}.txt", delimiter='\t', skip_header=1), T, A))
        
    
observables = ["eps","abs m","Cv","chi"]
for i in range(4):
    plt.figure()
    for j in range(4):
        plt.plot(data[j][0][:,i], label = f"T={data[j][1]}  A={data[j][2]}")
    plt.legend()
    
    plt.title(observables[i])
    plt.savefig(f"Data/Problem5/{observables[i]}.png")
        
    