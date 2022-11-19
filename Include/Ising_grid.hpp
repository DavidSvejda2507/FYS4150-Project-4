#ifndef _Ising_grid_
#define _Ising_grid_


#include <armadillo>
#include <iomanip>
#include <string>
#include <random>
#include <cmath>
#include <iostream>
#include <fstream>
#include <tuple>

class Ising_grid
{
    private:
        arma::Mat<short> grid;
        int L;
        double T;
        double dE [5];
        double eps;
        double abs_m;
        double Cv;
        double chi;
        std::mt19937 generator;
        std::uniform_real_distribution<double> uniform;
        std::uniform_int_distribution<int> index;

        short Get_Energy(int i, int j);
        short Get_Spin(int i, int j);

    public:

        Ising_grid(){}

        Ising_grid(int L, double T, int seed);

        double Calc_eps();
        int Calc_E();
        double Get_m();

        void Align();
        void Do_Spin_Flip();

        std::tuple<double, double> MCMC_Run(int n);
        std::tuple<double, double, double, double> MCMC_Run(int n, int step);
        void Simulate_steps(int burn, int n, int step);
        void Log_steps(int burn, int n, int step, std::string filename, int log_freq);
        void Log_steps_hist(int burn, int n, int step, std::string filename);

        double Get_eps(){return eps;}
        double Get_abs_m(){return abs_m;}
        double Get_Cv(){return Cv;}
        double Get_chi(){return chi;}
        double Get_T(){return T;}


        void print_grid();

};

#endif