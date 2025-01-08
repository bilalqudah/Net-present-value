//
//  npv.cpp
//  DecisionMaking
//
//  Created by Bilal on 11/23/21.
//

#include "npv.hpp"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <math.h>

// values n
//        r B C
void npv::readInputFile(string fileName) {
  
    int n=0;
    float r=0, B = 0, C=0;
    string temp;
    ifstream infile(fileName);
    cout<<"File name="<<fileName<<endl;
    if (!(infile >> n)) {
        cout<< "error, could not read first line! Abort." <<endl;
        exit(-1);
    }else{
        cout<<"Number of years in the file ="<<n<<endl;
        npv::setNumberOfYears(n);
        int i=0;
        while(infile >>r >>B >> C) {
            npv::npvTable[i].setYear(i+1);   // is the year index
            npv::npvTable[i].setR(r);   //
            npv::npvTable[i].setB(B);   //
            npv::npvTable[i].setC(C);   //
            cout<<"--> year "<<(i+1)<<" Data inserted [OK] T="<<npv::npvTable[i].getYear()
            <<", R= "<< npv::npvTable[i].getR()<<", B="<< npv::npvTable[i].getB()<<", C="<< npv::npvTable[i].getC()<<endl;
            i++;
        }
        
    }

};

 float npv::getSumNPV(){
    float sum=0;
    for (int i=0; i< npv::numberOfYears; i++){
        sum+=npv::npvTable[i].getNPV();
    }
    return (sum);
 };

int npv::getNumberOfYears(){
    return npv::numberOfYears;
};


string npv::toString () {
    int n=0;
    char xx[1000];
    string result="";
    char star;
    int location=0;
    n=sprintf (xx, "%s\t|%7s |%-10s|%-10s| %-5s | %-8s | %-10s | %-10s | %-12s| %-12s | %-10s|%s",
               "\n\n\t----------------------------------------------------------------------------------------------------------------------\n",
               "Year","Cost","Benefit","r","DF","DB","DC","NPV","CNPV","R to 0-NPV",
               "\n\t______________________________________________________________________________________________________________________\n");
    result+=xx;
    
    for (int i=0; i< npv::numberOfYears; i++){
        star=npv::markCNPVPositive(i, location);
        n=sprintf (xx, "\t|  [%-3d] |%-9.1f |%-9.1f | %-5.3f | %-8.3f | %-10.3f |%-10.3f | %-12.3f| %-13.3f|%-10.3f |%c\n",
                   (i+1),npv::npvTable[i].getC(),npv::npvTable[i].getB(),npv::npvTable[i].getR(),npv::npvTable[i].getDF(), npv::npvTable[i].getDB(),npv::npvTable[i].getDC(),
                   npv::npvTable[i].getNPV(), npv::getCNPV(i),npv::inZeroNPVGetR(i+1),star);
        result+=xx;
    }
    
    result+="\n\t---------------------------------------------------------------------------------------------------------------------";
    result+="\n\t\tNPVs SUM        ....   ∑ npv     = "+to_string(npv::getSumNPV());
    result+="\n\t\tThe ROI         ....   ∑npv/∑DC  = "+to_string(npv::getROI());
    result+="\n\t\tPositive CNPV /The Pay Back Year = [ "+to_string(location)+" ]"
            "\n\t______________________________________________________________________________________________________________________\n\n";
    return result;
};

void npv::writeToFile(string fileName, string result){
    ofstream myfile;
     myfile.open (fileName);
    myfile << result;
    myfile.close();
    cout<<"\n\t --> result written to file "+fileName+"\n\n";
}
float npv::getCNPV(int year){
    float sum=0;
    for (int i=0; i< year+1; i++){
        sum+=npv::npvTable[i].getNPV();
    }
    return sum;
}

float npv::getSumDC(){
    float sum=0;
    for (int i=0; i<npv::getNumberOfYears(); i++){
        sum+=npv::npvTable[i].getDC();
    }
    
    return sum;    
}

float npv::getROI(){
    
    return (npv::getSumNPV()/npv::getSumDC());
}

char npv::markCNPVPositive(int year, int &location){
    char mark=' ';
    if(npv::getCNPV(year)>0 && npv::getCNPV(year-1)<0){
        mark='*';
        location =year+1;
    }
    return mark;
}

float npv::inZeroNPVGetR(int t){
    if (t==0) return -999;
    cout<<"incomint t = "<<t<<"npv::npvTable["<<t<<"].getT() = "<<npv::npvTable[t-1].getYear()<<endl;
    float result=pow((npv::npvTable[t-1].getC()/npv::npvTable[t-1].getDB()), (1/npv::npvTable[t-1].getYear()))-1;
    return result;
}
