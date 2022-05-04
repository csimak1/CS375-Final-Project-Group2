#include "NumberGenerator.h"

NumGen::NumGen(string alg1){
    alg = alg1;
}

vector<int> NumGen::make_data(int size, string type){
    if(type == "heap"){
        vector<int> data;
        int min = 0;
        int max = size;
        for(int i = 0; i < size; i++){
            data.push_back(min + (rand() % (max - min + 1)));
        }
        return data;   
    }
}
