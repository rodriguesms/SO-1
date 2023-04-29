#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>

#define START_IDX 0
#define DURATION_IDX 1

class Job {

    private:
        uint id;
        uint enterTime;
        uint duration;

    public:
        Job();
        Job(uint id, uint startTime, uint duration);
        void printJob();
        // uint getEnterTime();
        // uint getDuration();
        // bool setEnterTime(uint);
        // bool setDuration(uint);
};

class Instance {

    private:
        std::vector<Job> jobList;
    
    public:
        Instance();
        Instance(char* filePath);
        std::vector<Job> getJobList();
        void addJob(Job&);
        void printInstance();
};