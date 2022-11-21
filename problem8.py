import numpy as np
import matplotlib.pyplot as plt
import scipy.odr as odr


data = np.genfromtxt(f"Data/Problem8/log.txt", dtype=str, comments="#")
        
observables = ["eps", "Cv", "abs_m", "chi"]

def f(beta, x):
    """Function to fit against Cv

    Args:
        beta (np.array): array of length 3 (or more), used as parameters
        x (np.array): Temperatures of the measurements

    Returns:
        y (np.array): Cv of the measurements
    """    
    return beta[2] * (np.log(np.abs(beta[1] * (x-beta[0]))+1e-8) + beta[3])
model = odr.Model(f)
beta0 = [2.3, 2, -1e-4, 3]

for L in (20,40,60,80,100):
    L_data = []
    for row in data:        
        if int(row[0]) == L:
            L_data.append(row)
    L_data = np.array(L_data)
    
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2,2)    
    axes = [ax1, ax2, ax3, ax4]
    
    T = L_data[:, 1].astype(float)
    
        
    Cv = L_data[:, 4].astype(float)
    weights = 1e-6 * L_data[:, 2].astype(int)
    Data = odr.Data(T, Cv, weights)
    myodr = odr.ODR(Data, model, beta0)
    output = myodr.run()
    # output.pprint()
    
    T_ = np.arange(np.min(T), np.max(T), 1e-3, float)
    ax2.plot(T_, f(output.beta, T_), "r-")
    
    for i, (obs, ax) in enumerate(zip(observables, axes)):
        ax.plot(T, L_data[:, i+3].astype(float), ".")
    
    plt.title(f"L={L}")
    plt.tight_layout()
    plt.savefig(f"Data/Problem8/L={L}.png")