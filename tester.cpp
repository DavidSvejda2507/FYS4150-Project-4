#include "Ising_grid.hpp"
#include <iostream>


int main(){
    Ising_grid x = Ising_grid(20, 2., 42);
    for (int i = 0; i < 10000; i++){
        x.Do_Spin_Flip();
    }
}