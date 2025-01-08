//
//  npv.hpp
//  DecisionMaking
//
//  Created by Bilal on 11/23/21.
//

#ifndef npv_hpp
#define npv_hpp
#include <stdio.h>
#include<math.h>
#include <iostream>

using namespace std;
/**
  this class represents one year only (one colum) on the represenation or npv
 */


class npv{
public:
    
    npv(int years){
         setNumberOfYears(years);
          
       };
       
    int numberOfYears;
    void readInputFile(string fileName);
    void writeToFile(string fileName,string result);
    string toString ();
    float getSumNPV();
    float getSumDC();
    float getROI();
    char markCNPVPositive(int year, int &location);
    int getNumberOfYears();
    float inZeroNPVGetR(int t);
    float getCNPV(int year);
    friend ostream& operator<<(ostream& os, const npv& s);
    
    
    class singleYear {
    # define DF()  1/pow((1+getR()),getYear())
    # define DB() getDF()*getB()
    # define DC() getDF()*getC()
    # define NPV() DB()-DC()
    
    public:
        float getDF(){
            return (DF());
        }
        float getDB(){
            return DB();
        }
        float getDC(){
            return DC();
        }
        float getNPV(){
            return NPV();
        }
        float getR(){
            return (r);
        }
        void setR(float inR){
            r=inR;
        }
     
        void setB(float inB){
            B=inB;
        }
        float getB(){
            return B;
        }
        void setC(float inC){
            C=inC;
        }
        float getC(){
            return C;
        }
        int getYear(){
            return year;
        }
        void setYear(int inY){
            year=inY;
        }
  
    private:
        float r=0.0f;
        int year=0;
        float B=0.0f;    // benefit
        float C= 0.0f;  // Cost
        
        
    };
    
       
       void setNumberOfYears(int n){
           numberOfYears=n;
           npvTable = new singleYear[numberOfYears];
       };
   
    
    singleYear *npvTable;
  
  
  
};



#endif /* npv_hpp */
