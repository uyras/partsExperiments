#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "config.h"
#include "PartArray.h"
#include <ctime>

using namespace std;

ofstream f;
void experiment(int lattice,int replicas, int steps, int tMin, int tMax){

    PartArray* sys = new PartArray(lattice,lattice,1);
    sys->dropChain();
    double eMin = sys->calcEnergy1(); //замерили минимум
    sys->shuffleM();//перемешали состояния
    sys->setToPTGroundState(replicas,steps,tMin,tMax);
    double E = sys->calcEnergy1();

    f<<
        lattice<<"\t"<<
        lattice<<"\t"<<
        lattice*lattice<<"\t"<<
        replicas<<"\t"<<
        steps<<"\t"<<
        tMin<<"\t"<<
        tMax<<"\t"<<
        eMin<<"\t"<<
        E<<"\t";

    delete sys;
}

/**
 * Параметры:
 * 1. Файл для сохранения
 * 2. количество реплик
 * 3. количество шагов
 * 4. температура минимума
 * 5. температура максимума
 */
int main(int argc, char *argv[]){
    config::Instance()->srand(time(NULL));
    config::Instance()->partR = 0.5; //радиус частицы 0.5
    config::Instance()->m = 1.; //вектор = 2R;
    config::Instance()->set2D();
    int experiments = 100; //количество экспериментов
    clock_t time; //время рассчета

    f.open(argv[1],ios_base::trunc);

    f<<
        "x\t"<<
        "y\t"<<
        "parts\t"<<
        "replicas\t"<<
        "steps\t"<<
        "t Min\t"<<
        "t Max\t"<<
        "e Real"<<
        "e PT"<<
        "speed"<<endl;

    for (int lattice=3;lattice<=20;lattice++){




        for (int i=0;i<experiments;i++){
            cout<<
                   "start with "<<
                   lattice<<" lattice, "<<
                   argv[2]<<" replicas, "<<
                   argv[3]<<" steps, "<<
                   argv[4]<<" tMin, "<<
                   argv[5]<<" tMax, "<<
                    i+1<<" of "<<experiments<<endl;
            time = clock();
            experiment(lattice, atoi(argv[2]), atoi(argv[3]), atof(argv[4]), atof(argv[5]));
            time = clock() - time;
            f<<(double)time/CLOCKS_PER_SEC<<endl;
        }



    }



    cout<<"finish";
    return 0;
}
