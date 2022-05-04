#include "NumberGenerator.h"

NumGen::NumGen(string alg1){
    alg = alg1;
}

vector<int> NumGen::make_data(int size, string type){
    vector<int> data;
    if(type == "random"){
        //vector<int> data;
        int min = 0;
        int max = size;
        for(int i = 0; i < size; i++){
            data.push_back(min + (rand() % (max - min + 1)));
        }
        return data;   
    }
    else if (type == "reverse"){
        for (int i = size; i > 0; i--){
            data.push_back(i);
        }
        return data;
    }
    else if (type == "sorted"){
        for (int i = 0; i < size; i++){
            data.push_back(i);
        }
        return data;
    }
    else if(type == "highValue"){
        //vector<int> data;
        int min = 100000 * size;
        int max = 1000000 * size;
        for(int i = 0; i < size; i++){
            data.push_back(min + (rand() % (max - min + 1)));
        }
        return data;   
    }
    else if(type == "Single High Val"){

    }
    return data;
    
}
