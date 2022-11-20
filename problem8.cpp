#include "Ising_grid.hpp"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

string print(double x, int width, int prec){
    ostringstream out;
    out << setw(width) << setprecision(prec) << scientific << x;
    return out.str();
}

string Run_openMP(int n_sub, double T, int L, int n, int burn = 500, int step = 0){
    double eps_sum=0, eps2_sum=0, m_sum=0, m2_sum=0;
    double eps, abs_m, Cv, chi;

    if (step == 0){
        step = L*L;
    }

    cout << "Running parallel with " << n_sub << " runs" << endl
         << "T = " << T << "; L = " << L << endl;

    #pragma omp parallel for reduction(+:eps_sum) reduction(+:eps2_sum) reduction(+:m_sum) reduction(+:m2_sum)
    for(int i = 0; i<n_sub; i++){
        Ising_grid x = Ising_grid(L, T, i);
        x.MCMC_Run(burn*step);
        
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


              
    ostringstream out;
    out << L << "\t"
        << print(T, 12, 6) << "\t"
        << n << "\t"
        << print(eps, 12, 6) << "\t"
        << print(Cv, 12, 6) << "\t"
        << print(abs_m, 12, 6) << "\t"
        << print(chi, 12, 6);
    return out.str();
}

int main(int argc, char *argv[]){
    int n_sub = 8, n, L, n_T, count = 0;
    double T_min, T_max, T;
    if (argc == 1){
        T_min = 2.1;
        T_max = 2.4;
        n_T = 20;
        n = 100*1000;
    }
    else {
        if (argc == 5){
        T_min = stod(argv[1]);
        T_max = stod(argv[2]);
        n_T = stoi(argv[3]);
        n = stoi(argv[4]);
        }
        else{
            cout << "Pleas supply three arguments (T_min(double) T_max(double) n_T(int) n(int)) or no arguments" << endl;
            return 1;
        }
    }

    ofstream file;
    file.open("Data/Problem8/log.txt", ios::app);
    if (not file.is_open()){
        cout << "Couldn't open file" << endl;
        return 1;
    }
    file << "# L \t T \t n \t eps \t Cv \t abs_m \t chi" << endl;

    for (int L = 20; L < 110; L += 20){
        for (int i = 0; i < n_T; i++){
            count++;
            cout << count << "/" << 5*n_T << "    ";
            T = (T_min*(n_T-i-1) + T_max*(i)) / (n_T - 1);
            file << Run_openMP(n_sub, T, L, n) << endl;
        }
    }
}
