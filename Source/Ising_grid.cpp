#include "Ising_grid.hpp"

using namespace arma;
using namespace std;



Ising_grid::Ising_grid(int L_, double T_, int seed){
    grid = Mat<short>(L_, L_);
    L = L_;
    T = T_;
    generator = mt19937(seed);
    uniform_int_distribution<short> spin(0,1); 
    for (int i = 0; i < L; i++){
        for (int j = 0; j < L; j++){
            grid(i,j) = spin(generator);
        }
    }
    uniform = uniform_real_distribution<double>(0,1);
    index = uniform_int_distribution<int>(L, 2*L-1);

    // dE = {1,1,1,1,1};
    for (int i = 0; i < 5; i++){
        if (i>1){dE[i] = 1;}
        else{dE[i] = exp(-4*(2-i)/T);}
    }
    // for (int i = 0; i<5; i++){
    //     cout << dE[i] << endl;
    // }
}

void Ising_grid::Align(){
    grid.replace(1, 0);
}

int Ising_grid::Calc_E(){
    int sum = 0;
    for (int i = L; i < 2*L; i++){
        for (int j = L; j < 2*L; j++){
            sum += Get_Energy(i, j);
            // The energy return by Get_Energy is in the range [0, 4]
            // To correct this we shift by -2 at the end
        }
    }
    return sum;
}

double Ising_grid::Calc_eps(){
    int sum = Calc_E();
    return (((double)sum/grid.n_elem)-2);
}

double Ising_grid::Get_m(){
    return 2*((double)accu(grid))/grid.n_elem-1;
}

short Ising_grid::Get_Energy(int i, int j){
    short s = Get_Spin(i, j);
    short E = 0;
    E += s^Get_Spin(i+1, j  );
    E += s^Get_Spin(i-1, j  );
    E += s^Get_Spin(i  , j+1);
    E += s^Get_Spin(i  , j-1);
    return E;
}

short Ising_grid::Get_Spin(int i, int j){
    return grid(i%L, j%L);
}

void Ising_grid::Do_Spin_Flip(){
    int i = index(generator);
    int j = index(generator);
    double chance = dE[Get_Energy(i, j)];
    if (uniform(generator) < chance){
        grid(i%L, j%L) = Get_Spin(i,j) ^ 1;
    }
}

tuple<double, double> Ising_grid::MCMC_Run(int n){
    for (int j = 0; j < n; j++){
            Do_Spin_Flip();
        }
    return make_tuple(Calc_eps(), Get_m());
}

tuple<double, double, double, double> Ising_grid::MCMC_Run(int n, int step){
    double eps_sum=0, eps2_sum=0, m_sum=0, m2_sum=0, eps_, m;
    
    for (int i = 0; i < n; i++){
        tie(eps_, m) = MCMC_Run(step);
        eps_sum += eps_;
        eps2_sum += eps_*eps_;
        m_sum += abs(m);
        m2_sum += m*m;
    }

    return make_tuple(eps_sum, eps2_sum, m_sum, m2_sum);
}

void Ising_grid::Simulate_steps(int burn, int n, int step){
    double eps_sum=0, eps2_sum=0, m_sum=0, m2_sum=0, eps_, m;

    MCMC_Run(burn);
    tie(eps_sum, eps2_sum, m_sum, m2_sum) = MCMC_Run(n, step);

    eps = eps_sum/n;
    abs_m = m_sum/n;
    Cv = (eps2_sum - eps*eps_sum)/(n*T*T);
    chi = (m2_sum - abs_m*m_sum)/(n*T);
}

void Ising_grid::Log_steps(int burn, int n, int step, string filename, int log_freq){
    double eps_sum=0, eps2_sum=0, m_sum=0, m2_sum=0, eps_, m;
    ofstream file;
    file.open(filename);
    file << "eps" << '\t'
        << "abs_m" << '\t'
        << "Cv" << '\t'
        << "chi" << endl;
    
    MCMC_Run(burn);

    for (int i = 1; i < n; i++){
        tie(eps_, m) = MCMC_Run(step);
        
        eps_sum += eps_;
        eps2_sum += eps_*eps_;
        m_sum += abs(m);
        m2_sum += m*m;
        eps = eps_sum/i;
        abs_m = m_sum/i;
        Cv = (eps2_sum - eps*eps_sum)/(i*T*T);
        chi = (m2_sum - abs_m*m_sum)/(i*T);
        if (abs_m < 0.5){abs_m = 1 - 2*abs_m;}
        else{abs_m = 2*abs_m - 1;}

        if (i%log_freq == 0){
            file << eps << '\t'
                << abs_m << '\t'
                << Cv << '\t'
                << chi << endl;
        }
        
    }
    file.close();
}

void Ising_grid::Log_steps_hist(int burn, int n, int step, string filename){
    double E;
    ofstream file;
    file.open(filename);
    file << "eps" << endl;
    MCMC_Run(burn);
    for (int i = 1; i < n; i++){
        MCMC_Run(step);
        E = Calc_E();
        file << E << endl;
    }
    file.close();
}

void Ising_grid::print_grid(){
    for (int i = 0; i < L; i++){
        for (int j = 0; j < L; j++){
            cout << grid(i, j);
        }
        cout << endl;
    }
    cout << endl;
}