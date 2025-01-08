//
//  main.cpp
//  DecisionMaking
//
//  Created by Bilal on 11/23/21.
//
#include <filesystem>
#include <unistd.h>
#include <iostream>
#include "npv.hpp"

using namespace std;
npv np(5);
int main(int argc, const char * argv[]) {
    // insert code here...
    char tmp[256];
    string filename;
    string result;
    string directory="/Users/bilal/Desktop/cppexamples/DecisionMaking/DecisionMaking/DecisionMaking/";
    getcwd(tmp, 256);
    cout<<"directory ="<<tmp<<endl;
    cout<<"Enter the file name that has your input: ";
    cin>>filename;
    filename=directory+filename;
    np.readInputFile(filename);
    result=np.toString();
    cout<< result;
    np.writeToFile(directory+"result.txt",result);
    return 0;
}
