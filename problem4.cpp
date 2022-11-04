#include <iostream>
#include <armadillo>    //include our armadillo package and armadillo matricy form text file A.txt

using namespace arma;
using namespace std;

double E(double s, int N, double J, arma::vec sk, arma::vec sl){
    return -J*arma::accu(sk*sl)
}

double e(arma::vec s, int N){
    return E(s,N)/N;
}
double M(arma::vec s){
    return arma::accu(s)
}
double m(arma::vec s, int N){
    return M(s,N)/N;
}

double Cv(arma::vec s, int N, double kB, T){
    return (1/N)*(1/(kB*T))*(E(s)**2-arma::abs(E(s)**2));
}

double X(arma::vec s, int N, double kB, T){
    return (1/N)*(1/(kB*T))*(M(s)**2-arma::abs(M(s)**2));
}



                                                                    
int main(){                                                 //testing with matrix A from task 3b yo

    

    return 0;
}
