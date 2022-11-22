import numpy as np
import matplotlib.pyplot as plt

#reads file consisting of: epsilon, abs_m, Cv, chi
data = []
for T in ("1","2.4"):
    for A in (0,1):
        data.append((np.genfromtxt(f"Data/Problem5/T_{T}_A_{A}.txt", delimiter='\t', skip_header=1), T, A))
        
    
observables = ["Energy per spin (\u03B5) for T = 1 [J/K]","Absolute magnetisation per spin (|m|)","Specific heat capacity (Cv)","Susceptibility (\u03A7)"]
imgnm = ["epsilon", "abs_m", "Cv", "chi"]
xl = ["\u03B5", "|m|", "Cv", "\u03A7"]
#yl = [" ", " ", " ", " "]
for i in range(4):
    plt.figure()
    for j in range(4):
        plt.plot(data[j][0][:5000,i], label = f"T={data[j][1]}  A={data[j][2]}")  #plotting epsilon 
    plt.legend()
    
    plt.title(observables[i])
    plt.ylabel(xl[i])
    plt.xlabel("Number of montecarlo cycles")
    plt.show()
    plt.savefig(f"Data/Problem5/{imgnm[i]}.pdf")
        
    
