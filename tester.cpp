#include "Ising_grid.hpp"
#include <iostream>
#include <string>
#include <iomanip>


std::string print(double x, int width, int prec){
    std::ostringstream out;
    out << std::setw(width) << std::setprecision(prec) << std::scientific << x;
    return out.str();
}


int main(int argc, char *argv[]){
    Ising_grid x;
    if(argc == 2){
        x = Ising_grid(2, 1., std::stoi(argv[1]));
    }
    else{
        x = Ising_grid(2, 1., 42);
    }
    // for (int i = 0; i<10; i++){
    //     x.print_grid();
    //     x.Do_Spin_Flip();
    // }
    x.print_grid();



    // std::cout << print(x.Calc_eps(), 12,6) << std::endl;

    x.Simulate_steps(10, 1000000, 10);
    std::cout << "eps " << print(x.Get_eps(), 12, 6) << std::endl
              << "Cv " << print(x.Get_Cv(), 12, 6) << std::endl
              << "m " << print(x.Get_abs_m(), 12, 6) << std::endl
              << "chi " << print(x.Get_chi(), 12, 6) << std::endl;
}

// int main(){
//     for (short i = 0; i <2; i++){
//         for (short j = 0; j < 2; j++){
//             std::cout << i << " ^ " << j << " = " << (i^j) << std::endl;
//         }
//     }
// }