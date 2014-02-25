#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "config.h"
#include "PartArray.h"
#include <ctime>

using namespace std;

int main(){
    config::Instance()->srand(time(NULL));
    config::Instance()->partR = 0.5; //радиус частицы 0.5
    config::Instance()->m = 1.; //вектор = 2R;
    config::Instance()->set2D();
    double calcError = 0.01; //погрешность рассчета 1 процент
    int experiments = 100; //количество экспериментов
    clock_t time; //время рассчета

    ofstream f("squareLatticePT.txt");
    f<<"x\ty\tparts\taccuracy\tspeed"<<endl;

    for (int j=3;j<=10;j++){
        cout<<"start with "<<j<<"x"<<j<<" lattice with "<<j*j<<" particles"<<endl;

        time = clock();
        int validExp = 0; //точность рассчета, %
        for (int i=0;i<experiments;i++){
            PartArray* sys = new PartArray(j,j,1);
            sys->dropChain();
            sys->save("sys.dat");
            double eMin = sys->calcEnergy1(); //замерили минимум
            double delta = fabs(eMin*calcError); //замерили погрешность расчета
            sys->shuffleM();//перемешали состояния
            sys->setToPTGroundState(5,1000,0,3);
            double E = sys->calcEnergy1();

            if (fabs(eMin-E)<delta)
                validExp++;

            delete sys;
        }
        time = clock() - time;

        f
                <<j<<"\t"
               <<j<<"\t"
              <<j*j<<"\t"
             <<(double)validExp/(double)experiments<<"\t"
            <<(double)time/CLOCKS_PER_SEC
           <<endl;
    }



    cout<<"finish";
    return 0;
}
