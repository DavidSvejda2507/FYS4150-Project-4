import numpy as np
import matplotlib.pyplot as plt


data = []
for T in ("1","2.4"):
    for A in (0,1):
        data.append((np.genfromtxt(f"Data/Problem6/T_{T}_A_{A}.txt", dtype=int, delimiter='\t', skip_header=1)/200-2, T, A))
        
    
observables = ["eps"]
for i in range(len(observables)):
    for j in range(0, 4, 2):
        plt.figure()
        
        
        bins = np.arange(np.min(data[j][0]), np.max(data[j][0]), 0.02)
        data_ = np.zeros((len(data[0][0]),2))
        data_[:,0] = data[j][0]
        data_[:,1] = data[j+1][0]
        plt.hist(data_, bins, label= f"A = {data[j][1]}")
        # plt.hist(data[j+1][0], bins, label= f"A = {data[j+1][1]}")
        # plt.legend()
        
        plt.title(f"eps for T={data[j][1]}")
        plt.savefig(f"Data/Problem6/T={data[j][1]}.pdf")
        
    
