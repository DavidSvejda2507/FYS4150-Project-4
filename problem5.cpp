#include "Ising_grid.hpp"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main(){
    Ising_grid x;
    stringstream filename;
    for (double T = 1; T < 3; T+= 1.4){
        x = Ising_grid(20, T, 42);
        for (int alligned = 0; alligned < 2; alligned++){
            if (alligned == 1){
                x.Align();
            }
            filename = stringstream();
            filename << "Data/Problem5/T_" << setprecision(3) << T << "_A_" << alligned << ".txt";
            x.Log_steps(0*400, 10000, 400, filename.str(), 1);



        }
    }
}