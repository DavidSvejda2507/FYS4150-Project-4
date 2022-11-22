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
beta0_Cv = {20: [2.3, 0.2, -1e-3, 3, 1e-2],
            40: [2.3, 0.2, -1e-3, 3, 1e-2],
            60: [2.3, 0.2, -1e-4, 3, 1e-2],
            80: [2.3, 0.2, -1e-4, 3, 1e-2],
           100: [2.3, 0.2, -1e-4, 3, 1e-2]}
beta0_Chi = {20: [2.4, 2e-1, 2.2e-5, 1e-3, 2e-2],
             40: [2.3, 2e-1, 2e-5, 1e-3, 2e-2],
             60: [2.3, 2e-1, 2e-5, 1e-3, 2e-2],
             80: [2.3, 2e-1, 2e-5, 1e-3, 2e-2],
            100: [2.3, 2e-1, 2e-5, 1e-3, 2e-2]}

Tc_list = []


error_scale =  {20: [1e-2, 1e-4, 1e-2, 5e-4],
                40: [1e-2, 3e-5, 2e-2, 7e-4],
                60: [1e-2, 1e-5, 1e-2, 5e-4],
                80: [1e-2, 1e-5, 2e-2, 7e-4],
               100: [1e-2, 1e-5, 3e-2, 1e-3]}

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
    myodr_Cv = odr.ODR(Data_Cv, model_Cv, beta0_Cv[L])
    myodr_Chi = odr.ODR(Data_Chi, model_Chi, beta0_Chi[L])
    output_Cv = myodr_Cv.run()
    output_Chi = myodr_Chi.run()
    
    # output_Chi.pprint()
    
    Tc_list.append((output_Cv.beta[0], output_Cv.sd_beta[0], L))
    Tc_list.append((output_Chi.beta[0], output_Chi.sd_beta[0], L))
    
    
    T_ = np.arange(np.min(T), np.max(T), 1e-3, float)
    
    for i, (obs, ax) in enumerate(zip(observables, axes)):
        ax.errorbar(T, L_data[:, i+3].astype(float), error_scale[L][i]*np.power(weights, -0.5), fmt = "_")
    
    ax2.plot(T_, f_log(output_Cv.beta, T_), "r-")
    # ax2.plot(T_, f_log(beta0_Cv[L], T_), "b-")
    
    ax4.plot(T_, f_74(output_Chi.beta, T_), "r-")
    # ax4.plot(T_, f_74(beta0_Chi[L], T_), "b-")
        
    
    
    plt.title(f"L={L}")
    plt.tight_layout()
    plt.savefig(f"Data/Problem8/L={L}.png")
    
# print(Tc_list)

def f_lin(beta, x):
    """Linear model for fitting Tc(L = inf)

    Args:
        beta (np.array): length of at least 2
        x (np.array): input data

    Returns:
        y (np.array): Output data
    """    
    return beta[0]*x + beta[1]


# Tc_list = np.array(list(filter(lambda x: 0 < x[1] < 1 and x[0] < 2.34, Tc_list)))
Tc_list = np.array(Tc_list)
# print(Tc_list)

model_lin = odr.Model(f_lin)
y = Tc_list[:,0]
weights_lin = np.power(Tc_list[:,1], -2)
x = np.power(Tc_list[:,2], -1)
Data = odr.Data(x, y, weights_lin)
odr_lin = odr.ODR(Data, model_lin, (1, 2.2))
output = odr_lin.run()
output.pprint()

L_range = np.arange(0, 0.051, 0.01)

plt.figure()
plt.errorbar(x, y, Tc_list[:,1], fmt = "_")
plt.plot(L_range, f_lin(output.beta, L_range), "r-")
plt.xlabel("$L^{-1}$")
plt.ylabel("Tc")
plt.tight_layout()
plt.savefig("Data/Problem8/Tc_plot.png")

print("\n")
print(f"Tc = {output.beta[1]} +/- {output.sd_beta[1]}")