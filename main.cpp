#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "config.h"
#include "PartArray.h"
#include <ctime>

using namespace std;

struct hist{
    int step;
    double e;
    double eMin;
    double eMax;
    int iteration;
};

void saveVector(char* filename,vector<hist> history){
    ofstream f(filename);
    f<<"step\te\teMin\teMax\titeration"<<endl;
    for (int i=0;i<history.size();i++){
        f<<history[i].step<<"\t"<<
           history[i].e<<"\t"<<
           history[i].eMin<<"\t"<<
           history[i].eMax<<"\t"<<
           history[i].iteration<<"\t"<<endl;
    }
    f.close();
}

int main(){
    config::Instance()->srand(time(NULL));
    int parts = 20;
    int size = 7;

    PartArray *sys1,*sys2;
    vector<double> subHistory;
    vector<hist> history;
    double eTemp,eTemp2;

    //processStep
    for (int i=0;i<100;i++){
        cout<<"start "<<i<<" of PS"<<endl;
        sys1 = new PartArray(size,size,1,parts);
        sys2 = sys1->copy();
        sys1->setToGroundState();
        eTemp = sys1->calcEnergy1();
        sys1->setToMaximalState();
        eTemp2 = sys1->calcEnergy1();

        subHistory = sys2->processStep();

        //заполняем историю
        for (int j=0;j<subHistory.size();j++){
            hist temp = {j,subHistory[j],eTemp,eTemp2,i};
            history.push_back(temp);
        }
        subHistory.clear();
        delete sys1, sys2;
    }
    saveVector("step.txt", history);
    history.clear();

    //processMaxH
    for (int i=0;i<100;i++){
        cout<<"start "<<i<<" of maxH"<<endl;
        sys1 = new PartArray(size,size,1,parts);
        sys2 = sys1->copy();
        sys1->setToGroundState();
        eTemp = sys1->calcEnergy1();
        sys1->setToMaximalState();
        eTemp2 = sys1->calcEnergy1();

        subHistory = sys2->processMaxH();

        //заполняем историю
        for (int j=0;j<subHistory.size();j++){
            hist temp = {j,subHistory[j],eTemp,eTemp2,i};
            history.push_back(temp);
        }
        subHistory.clear();
        delete sys1, sys2;
    }
    saveVector("maxh.txt", history);
    history.clear();


    //processGroupMaxH
    for (int i=0;i<100;i++){
        cout<<"start "<<i<<" of groupMaxH"<<endl;
        sys1 = new PartArray(size,size,1,parts);
        sys2 = sys1->copy();
        sys1->setToGroundState();
        eTemp = sys1->calcEnergy1();
        sys1->setToMaximalState();
        eTemp2 = sys1->calcEnergy1();

        subHistory = sys2->processGroupMaxH();

        //заполняем историю
        for (int j=0;j<subHistory.size();j++){
            hist temp = {j,subHistory[j],eTemp,eTemp2,i};
            history.push_back(temp);
        }
        subHistory.clear();
        delete sys1, sys2;
    }
    saveVector("groupmaxh.txt", history);
    history.clear();


    //processGroupStep
    for (int i=0;i<100;i++){
        cout<<"start "<<i<<" of groupStep"<<endl;
        sys1 = new PartArray(size,size,1,parts);
        sys2 = sys1->copy();
        sys1->setToGroundState();
        eTemp = sys1->calcEnergy1();
        sys1->setToMaximalState();
        eTemp2 = sys1->calcEnergy1();

        subHistory = sys2->processGroupStep();

        //заполняем историю
        for (int j=0;j<subHistory.size();j++){
            hist temp = {j,subHistory[j],eTemp,eTemp2,i};
            history.push_back(temp);
        }
        subHistory.clear();
        delete sys1, sys2;
    }
    saveVector("groupstep.txt", history);
    history.clear();


    //processHEffective
    for (int i=0;i<100;i++){
        cout<<"start "<<i<<" of HEffective"<<endl;
        sys1 = new PartArray(size,size,1,parts);
        sys2 = sys1->copy();
        sys1->setToGroundState();
        eTemp = sys1->calcEnergy1();
        sys1->setToMaximalState();
        eTemp2 = sys1->calcEnergy1();

        subHistory = sys2->processHEffective();

        //заполняем историю
        for (int j=0;j<subHistory.size();j++){
            hist temp = {j,subHistory[j],eTemp,eTemp2,i};
            history.push_back(temp);
        }
        subHistory.clear();
        delete sys1, sys2;
    }
    saveVector("heffective.txt", history);
    history.clear();



    cout<<"finish";
	return 0;
}
