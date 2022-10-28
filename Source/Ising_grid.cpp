#include "Ising_grid.hpp"


using namespace arma;
using namespace std;


Ising_grid::Ising_grid(int L, double T){
    grid = Mat<short>(L, L);
    // dE = {1,1,1,1,1};
    for (int i = 0; i < 5; i++){
        if (i<3){dE[i] = 1;}
        else{dE[i] = exp(-2/T);}
    }
}
