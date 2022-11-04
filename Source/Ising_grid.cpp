#include "Ising_grid.hpp"
#include <iostream>

using namespace arma;
using namespace std;


Ising_grid::Ising_grid(int L_, double T, int seed){
    grid = Mat<short>(L_, L_);
    L = L_;
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
        else{dE[i] = exp(-2*(2-i)/T);}
    }
    for (int i = 0; i<5; i++){
        cout << dE[i] << endl;
    }
}

double Ising_grid::Get_eps(){
    int sum = 0;
    for (int i = L; i < 2L; i++){
        for (int j = L; j < 2L; j++){
            sum += Get_Energy(i, j);
            // The energy return by Get_Energy is in the range [0, 4]
            // To correct this we shift by -2 at the end
        }
    }
    return (((double)sum/grid.n_elem)-2);
}

double Ising_grid::Get_m(){
    return accu(grid)/grid.n_elem;
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