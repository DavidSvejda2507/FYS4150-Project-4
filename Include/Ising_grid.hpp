#ifndef _Ising_grid_
#define _Ising_grid_


#include <armadillo>
#include <iomanip>
#include <string>
#include <random>

class Ising_grid
{
    private:
        arma::Mat<short> grid;
        int L;
        double T;
        double dE [5];
        std::mt19937 generator;
        std::uniform_real_distribution<double> uniform;
        std::uniform_int_distribution<int> index;

        short Get_Energy(int i, int j);
        short Get_Spin(int i, int j);

    public:

        Ising_grid(){}

        Ising_grid(int L, double T, int seed);

        double Get_eps();
        double Get_m();

        void Do_Spin_Flip();




};

#endif