#ifndef _Ising_grid_
#define _Ising_grid_


#include <armadillo>
#include <iostream>
#include <iomanip>
#include <string>

class Ising_grid
{
    private:
        arma::Mat<short> grid;
        double T;
        double dE [5];


    public:

        Ising_grid(){}

        Ising_grid(int L, double T);








};

#endif