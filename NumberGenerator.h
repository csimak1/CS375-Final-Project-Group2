#ifndef _NumberGenerator_h
#define _NumberGenerator_h
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

class NumGen{
    NumGen(string alg1);
    vector<int> make_data(int size, string type);
    string alg;
    vector<int> heap_data1;
    vector<int> heap_data2;
    vector<int> heap_data3;


};

#endif