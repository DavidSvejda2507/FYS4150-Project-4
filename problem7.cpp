#include "Ising_grid.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>

using namespace std;

string print(double x, int width, int prec){
    ostringstream out;
    out << setw(width) << setprecision(prec) << scientific << x;
    return out.str();
}

void Run_openMP(int n_sub, double T, int L, int burn, int n, int step){
    double eps_sum=0, eps2_sum=0, m_sum=0, m2_sum=0;
    double eps, abs_m, Cv, chi;

    cout << "Running parallel with " << n_sub << " runs" << endl;
    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for reduction(+:eps_sum) reduction(+:eps2_sum) reduction(+:m_sum) reduction(+:m2_sum)
    for(int i = 0; i<n_sub; i++){
        Ising_grid x = Ising_grid(L, T, i);
        x.MCMC_Run(burn);
        
        double eps_sum_=0, eps2_sum_=0, m_sum_=0, m2_sum_=0;
        tie(eps_sum_, eps2_sum_, m_sum_, m2_sum_) = x.MCMC_Run(n/n_sub, step);
        eps_sum += eps_sum_;
        eps2_sum += eps2_sum_;
        m_sum += m_sum_;
        m2_sum += m2_sum_;
    }

    eps = eps_sum/n;
    abs_m = m_sum/n;
    Cv = (eps2_sum - eps*eps_sum)/(n*T*T);
    chi = (m2_sum - abs_m*m_sum)/(n*T);


    cout << "eps " << print(eps, 12, 6) << endl
              << "Cv " << print(Cv, 12, 6) << endl
              << "m " << print(abs_m, 12, 6) << endl
              << "chi " << print(chi, 12, 6) << endl;
              
    
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

}

void Run_sequential(double T, int L, int burn, int n, int step){

    cout << "Running sequential" << endl;
    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    Ising_grid x = Ising_grid(L, T, 42);
    x.Simulate_steps(burn, n, step);


    cout << "eps " << print(x.Get_eps(), 12, 6) << endl
              << "Cv " << print(x.Get_Cv(), 12, 6) << endl
              << "m " << print(x.Get_abs_m(), 12, 6) << endl
              << "chi " << print(x.Get_chi(), 12, 6) << endl;
              
    
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

}

int main(int argc, char *argv[]){
    int n_sub;
    if (argc == 1){n_sub = 10;}
    else {n_sub = stoi(argv[1]);}

    double T = 2.2;
    int L = 100;
    int burn = L*L*500, n = 100000, step = L*L;

    #ifdef _OPENMP
    {
    Run_openMP(n_sub, T, L, burn, n, step);
    }
    #else
    {
    Run_sequential(T, L, burn, n, step);
    }
    #endif
}

