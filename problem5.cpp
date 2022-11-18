#include "Ising_grid.hpp"
#include <iostream>
#include <string>
#include <iomanip>


int main(){
    Ising_grid x;

    for (double T = 1; T < 3; T+= 1.4){
        x = Ising_grid(20, T, 42);
        for (int alligned = 0; alligned < 2; alligned++){
            if (alligned == 1){
                x.Align();
            }

            



        }
    }
}