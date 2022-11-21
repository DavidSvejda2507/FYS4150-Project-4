import numpy as np
import matplotlib.pyplot as plt
import scipy.odr as odr


data = np.genfromtxt(f"Data/Problem8/log.txt", dtype=str, comments="#")
        
observables = ["eps", "Cv", "abs_m", "chi"]

def f_log(beta, x):
    """Function to fit against Cv

    Args:
        beta (np.array): array of length 4 (or more), used as parameters
        x (np.array): Temperatures of the measurements

    Returns:
        y (np.array): Cv of the measurements
    """    
    return beta[2] * (np.log(np.abs(beta[1] * (x-beta[0]))+beta[4]) + beta[3])

def f_74(beta, x):
    """Function to fit against chi

    Args:
        beta (np.array): array of length 4 (or more), used as parameters
        x (np.array): Temperatures of the measurements

    Returns:
        y (np.array): Cv of the measurements
    """    
    return beta[2] * np.power(np.abs(beta[1] * (x-beta[0]))+beta[4], -1.75) + beta[3]

model_Cv = odr.Model(f_log)
model_Chi = odr.Model(f_74)
beta0_Cv = [2.3, 2, -1e-4, 3, 1e-2]
beta0_Chi = [2.3, 1e-2, 2e-9, 5e-2, 1e-2]

Tc_list = []

error_scale = [1e-2, 1e-5, 1e-2, 5e-4]

for L in (20,40,60,80,100):
# for L in (80,):
    L_data = []
    for row in data:        
        if int(row[0]) == L:
            L_data.append(row)
    L_data = np.array(L_data)
    
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2,2)    
    axes = [ax1, ax2, ax3, ax4]
    
    T = L_data[:, 1].astype(float)
    
        
    Cv = L_data[:, 4].astype(float)
    Chi = L_data[:, 6].astype(float)
    weights = 1e-6 * L_data[:, 2].astype(int)
    Data_Cv = odr.Data(T, Cv, weights)
    Data_Chi = odr.Data(T, Chi, weights)
    myodr_Cv = odr.ODR(Data_Cv, model_Cv, beta0_Cv)
    myodr_Chi = odr.ODR(Data_Chi, model_Chi, beta0_Cv)
    output_Cv = myodr_Cv.run()
    output_Chi = myodr_Chi.run()
    
    output_Chi.pprint()
    
    Tc_list.append((output_Cv.beta[0], output_Cv.sd_beta[0], L))
    Tc_list.append((output_Chi.beta[0], output_Chi.sd_beta[0], L))
    
    
    T_ = np.arange(np.min(T), np.max(T), 1e-3, float)
    
    ax2.plot(T_, f_log(output_Cv.beta, T_), "r-")
    # ax4.plot(T_, f_74(beta0_Cv, T_), "b-")
    
    ax4.plot(T_, f_74(output_Chi.beta, T_), "r-")
    
    for i, (obs, ax) in enumerate(zip(observables, axes)):
        ax.errorbar(T, L_data[:, i+3].astype(float), error_scale[i]*np.power(weights, -0.5), fmt = ".")
        
    
    
    plt.title(f"L={L}")
    plt.tight_layout()
    plt.savefig(f"Data/Problem8/L={L}.png")
    
# print(Tc_list)