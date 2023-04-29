#include "instance.h"

Job::Job(){
    this->enterTime = 0;
    this->duration = 0;
    this->id = 0;
}

Job::Job(uint id, uint enterTime, uint duration){
    this->enterTime = enterTime;
    this->duration = duration;
    this->id = id;
}


void Job::printJob(){
    std::cout << "[Id " << id << "]" << " Enter time: " << enterTime << " | " << "Duration: " << duration << std::endl;
}


Instance::Instance(){
    this->jobList={};
}

Instance::Instance(char* filePath){

    std::ifstream instanceFile(filePath);

    if(!instanceFile.is_open()){
        std::cout << "Arquivo não encontrado ou corrompido. Abortando." << std::endl;
        exit(-1);
    }

    uint id = 0;
    std::string line;
    std::vector<uint> row;
    int value;

    while (std::getline(instanceFile, line)) {
        row.clear();
        std::istringstream iss(line);
        while (iss >> value) {
            //std::cout << value << std::endl;
            row.push_back(value);
        }
        Job job = Job((uint)(id+1), (uint)row[START_IDX], (uint)row[DURATION_IDX]);
        this->addJob(job);
        id+=1;
    }

    // std::ifstream instanceFile(filePath);
    // Instance instance;
    // uint value;

    // if(!instanceFile.is_open()){
    //     std::cout << "Arquivo não encontrado ou corrompido. Abortando." << std::endl;
    //     exit(-1);
    // }

    // while(instanceFile >> value){
    //     mask.push_back(std::vector<float>());
    //     mask.back().push_back(value);
    //     while(instanceFile.peek() != '\n' && instanceFile >> value){
    //         mask.back().push_back(value);
    //     }
    // }

    // instanceFile.close();
}

void Instance::addJob(Job &job){
    this->jobList.push_back(job);
}

void Instance::printInstance(){
    for(uint i = 0; i < jobList.size(); i++)
        jobList[i].printJob();
}

