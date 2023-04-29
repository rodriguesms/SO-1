#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>

#define START_IDX 0
#define DURATION_IDX 1

int main(int argc, char* argv[]){

    if(argc != 2)
        std::cout << "Uso correto: ./SO-1 <arquivo-da-instancia>" << std::endl;
   
    std::ifstream instanceFile(argv[1]);

    if(!instanceFile.is_open()){
        std::cout << "Arquivo não encontrado ou corrompido. Abortando." << std::endl;
        exit(-1);
    }
    std::string line;
    std::vector<std::vector<uint>> instance;
    std::vector<uint> process;
    int value;

    while (std::getline(instanceFile, line)) {
        process.clear();
        std::istringstream iss(line);
        while (iss >> value)
            process.push_back(value);
        instance.push_back(process);
    }

    for(uint i = 0; i < instance.size(); i++){
        std::cout << "Processo " << i+1 << ": " << instance[i][START_IDX] << "x" << instance[i][DURATION_IDX] << std::endl;
    }

    return 0;
}