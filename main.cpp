#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>

#define ID 2
#define START_IDX 0
#define DURATION_IDX 1
#define QUANTUM 2

struct processStats {
    uint turnaroundTime = 0;
    uint responseTime = 0;
    uint waitTime = 0;
};

using Process = std::vector<uint>;
using Instance = std::vector<Process>;
using Queue = std::vector<Process>;


void shortest_job_first(Instance instance){

    std::vector<uint> durationCopy;    
    uint time = 0;
    uint jobQuant = instance.size();
    Queue sjf_queue;
    std::vector<int> removePositions;
    processStats stats;

    for(uint i = 0; i < instance.size(); i++){
        durationCopy.push_back(instance[i][DURATION_IDX]);
    }

    std::sort(instance.begin(), instance.end(), [](Process p1, Process p2) {
        return p1[DURATION_IDX] < p2[DURATION_IDX];
    });


    // std::cout << "[SJF] Processos ainda não-iniciados: [ ";
    // for(uint j = 0; j < instance.size(); j++){
    //     std::cout << instance[j][ID] << " ";
    // }
    // std::cout << "]" << std::endl;
    
    while(sjf_queue.size() != 0 || instance.size() != 0){

        removePositions.clear();

        // std::cout << "-------------------------------------------------------" << std::endl;
        // std::cout << "[SJF] Tempo: " << time << std::endl;
    
        for(uint i = 0; i < instance.size(); i++){
            bool inserted = false;
            if(instance[i][START_IDX] <= time){
                for(uint j = 0; j < sjf_queue.size() && !inserted; j++){
                    if(instance[i][DURATION_IDX] < sjf_queue[j][DURATION_IDX]){
                        sjf_queue.insert(sjf_queue.begin()+j, instance[i]);
                        inserted=true;
                    }
                }
                if(!inserted)
                    sjf_queue.insert(sjf_queue.end(), instance[i]);
                removePositions.push_back(i);
            }
        }

        for(int j = removePositions.size() - 1; j >= 0; j--){
            instance.erase(instance.begin()+removePositions[j]);
        }


        // std::cout << "[SJF] Processos na fila: [ ";
        // for(uint j = 0; j < sjf_queue.size(); j++){
        //     std::cout << sjf_queue[j][ID] << " ";
        // }
        // std::cout << "]" << std::endl;

        // std::cout << "[SJF] Processos ainda não-iniciados: ";
        // for(uint j = 0; j < instance.size(); j++){
        //     std::cout << instance[j][ID] << " ";
        // }
        // std::cout << std::endl;


        if(sjf_queue.size()>0){
            for(uint queueProcess = 0; queueProcess < sjf_queue.size(); queueProcess++){
                if(queueProcess==0){
                    stats.turnaroundTime++;
                    sjf_queue[0][DURATION_IDX]--;
                    // std::cout << "[SJF] Processo " << sjf_queue[0][ID] << " executando. (Execuções restante: " << sjf_queue[0][DURATION_IDX] << ")" << std::endl;
                }else{
                    if(sjf_queue[queueProcess][DURATION_IDX] == durationCopy[sjf_queue[queueProcess][ID]-1]) // Se ainda não foi executado nenhuma vez
                        stats.waitTime++;
                    stats.responseTime++;
                    stats.turnaroundTime++;
                    // std::cout << "[SJF] Processo " << sjf_queue[queueProcess][ID] << " esperando.  (Execuções restante: " << sjf_queue[queueProcess][DURATION_IDX] << ")" << std::endl;
                }
            }

            if(sjf_queue[0][DURATION_IDX]==0)
                sjf_queue.erase(sjf_queue.begin());
        }
        time++;
    }
    // std::cout << "-----------------------------------------------------" << std::endl;
    // std::cout << "Turnaround time: " << stats.turnaroundTime << std::endl;
    // std::cout << "Response time: " << stats.responseTime << std::endl;
    // std::cout << "Wait time: " << stats.waitTime << std::endl;

    std::cout << "SJF " << (float)stats.turnaroundTime/jobQuant << " " <<  (float)stats.waitTime/jobQuant << " " << (float)stats.responseTime/jobQuant << std::endl;

}

void first_come_first_served(Instance instance){
    
    std::vector<uint> durationCopy;
    uint time = 0;
    uint jobQuant = instance.size();
    Queue fcfs_queue;
    std::vector<int> removePositions;
    processStats stats;

    for(uint i = 0; i < instance.size(); i++){
        durationCopy.push_back(instance[i][DURATION_IDX]);
    }


    std::sort(instance.begin(), instance.end(), [](Process p1, Process p2) {
        return p1[START_IDX] < p2[START_IDX];
    });

    // std::cout << "[FCFS] Processos ainda não-iniciados: [ ";
    // for(uint j = 0; j < instance.size(); j++){
    //     std::cout << instance[j][ID] << " ";
    // }
    // std::cout << "]" << std::endl;

    while(fcfs_queue.size() != 0 || instance.size() != 0){

        removePositions.clear();

        // std::cout << "-------------------------------------------------------" << std::endl;
        // std::cout << "[FCFS] Tempo: " << time << std::endl;
    
        for(uint i = 0; i < instance.size(); i++){
            if(instance[i][START_IDX] <= time){
                fcfs_queue.insert(fcfs_queue.end(), instance[i]);
                removePositions.push_back(i);
            }
        }

        for(int j = removePositions.size() - 1; j >= 0; j--){
            instance.erase(instance.begin()+removePositions[j]);
        }


        // std::cout << "[FCFS] Processos na fila: [ ";
        // for(uint j = 0; j < fcfs_queue.size(); j++){
        //     std::cout << fcfs_queue[j][ID] << " ";
        // }
        // std::cout << "]" << std::endl;

        // std::cout << "[FCFS] Processos ainda não-iniciados: [ ";
        // for(uint j = 0; j < instance.size(); j++){
        //     std::cout << instance[j][ID] << " ";
        // }
        // std::cout << "]" << std::endl;


        if(fcfs_queue.size()>0){
            for(uint queueProcess = 0; queueProcess < fcfs_queue.size(); queueProcess++){
                if(queueProcess==0){
                    stats.turnaroundTime++;
                    fcfs_queue[0][DURATION_IDX]--;
                    // std::cout << "[FCFS] Processo " << fcfs_queue[0][ID] << " executando. (Execuções restante: " << fcfs_queue[0][DURATION_IDX] << ")" << std::endl;
                }else{
                    if(fcfs_queue[queueProcess][DURATION_IDX] == durationCopy[fcfs_queue[queueProcess][ID]-1]) // Se ainda não foi executado nenhuma vez
                        stats.waitTime++;
                    stats.responseTime++;
                    stats.turnaroundTime++;
                    // std::cout << "[FCFS] Processo " << fcfs_queue[queueProcess][ID] << " esperando.  (Execuções restante: " << fcfs_queue[queueProcess][DURATION_IDX] << ")" << std::endl;
                }
            }

            if(fcfs_queue[0][DURATION_IDX]==0)
                fcfs_queue.erase(fcfs_queue.begin());
        }
        time++;
    }

    // std::cout << "-----------------------------------------------------" << std::endl;
    // std::cout << "Turnaround time: " << stats.turnaroundTime << std::endl;
    // std::cout << "Response time: " << stats.responseTime << std::endl;
    // std::cout << "Wait time: " << stats.waitTime << std::endl;

    std::cout << "FCFS " << (float)stats.turnaroundTime/jobQuant << " " <<  (float)stats.waitTime/jobQuant << " " << (float)stats.responseTime/jobQuant << std::endl;

}

void round_robin(Instance& instance){

    std::vector<uint> durationCopy;
    uint time = 0;
    uint jobQuant = instance.size();
    Queue rr_queue;
    std::vector<int> removePositions;
    processStats stats;
    uint quantumCount = 1;

    for(uint i = 0; i < instance.size(); i++){
        durationCopy.push_back(instance[i][DURATION_IDX]);
    }


    // std::cout << "[RR] Processos ainda não-iniciados: [ ";
    // for(uint j = 0; j < instance.size(); j++){
    //     std::cout << instance[j][ID] << " ";
    // }
    // std::cout << "]" << std::endl;


    std::sort(instance.begin(), instance.end(), [](Process p1, Process p2) {
        return p1[START_IDX] < p2[START_IDX];
    });

    while(rr_queue.size() != 0 || instance.size() != 0){

        removePositions.clear();

        // std::cout << "-------------------------------------------------------" << std::endl;
        // std::cout << "[RR] Tempo: " << time << std::endl;
    
        for(uint i = 0; i < instance.size(); i++){
            if(instance[i][START_IDX] <= time){
                rr_queue.insert(rr_queue.end(), instance[i]);
                removePositions.push_back(i);
            }
        }

        for(int j = removePositions.size() - 1; j >= 0; j--){
            instance.erase(instance.begin()+removePositions[j]);
        }

        if(quantumCount==1 && rr_queue.size() > 1)
            std::rotate(rr_queue.begin(), rr_queue.begin()+1, rr_queue.end());

        // std::cout << "[RR] Processos na fila: [ ";
        // for(uint j = 0; j < rr_queue.size(); j++){
        //     std::cout << rr_queue[j][ID] << " ";
        // }
        // std::cout << "]" << std::endl;

        // std::cout << "[RR] Processos ainda não-iniciados: [ ";
        // for(uint j = 0; j < instance.size(); j++){
        //     std::cout << instance[j][ID] << " ";
        // }
        // std::cout << "]" << std::endl;

        if(rr_queue.size()>0){
            for(uint queueProcess = 0; queueProcess < rr_queue.size(); queueProcess++){
                if(queueProcess==0){
                    stats.turnaroundTime++;
                    rr_queue[0][DURATION_IDX]--;
                    // std::cout << "[RR] Processo " << rr_queue[0][ID] << " executando. (Execuções restante: " << rr_queue[0][DURATION_IDX] << ")" << std::endl;
                }else{
                    if(rr_queue[queueProcess][DURATION_IDX] == durationCopy[rr_queue[queueProcess][ID]-1]) // Se ainda não foi executado nenhuma vez
                        stats.waitTime++;
                    stats.responseTime++;
                    stats.turnaroundTime++;
                    // std::cout << "[RR] Processo " << rr_queue[queueProcess][ID] << " esperando.  (Execuções restante: " << rr_queue[queueProcess][DURATION_IDX] << ")" << std::endl;
                }
            }
            if(rr_queue[0][DURATION_IDX]==0)
                rr_queue.erase(rr_queue.begin());
        }
        quantumCount = quantumCount < QUANTUM ? quantumCount+1 : 1;
        time++;
    }

    // std::cout << "-----------------------------------------------------" << std::endl;
    // std::cout << "Turnaround time: " << stats.turnaroundTime << std::endl;
    // std::cout << "Response time: " << stats.responseTime << std::endl;
    // std::cout << "Wait time: " << stats.waitTime << std::endl;

    std::cout << "RR " << (float)stats.turnaroundTime/jobQuant << " " <<  (float)stats.waitTime/jobQuant << " " << (float)stats.responseTime/jobQuant << std::endl;
}

int main(int argc, char* argv[]){

    if(argc != 2)
        std::cout << "Uso correto: <executavel> <arquivo-da-instancia>" << std::endl;

    std::ifstream instanceFile(argv[1]);

    if(!instanceFile.is_open()){
        std::cout << "Arquivo não encontrado ou corrompido. Abortando." << std::endl;
        exit(-1);
    }
    std::string line;
    Instance instance;
    Process process;

    int value;
    uint id = 1;

    while (std::getline(instanceFile, line)) {
        process.clear();
        std::istringstream iss(line);
        while (iss >> value)
            process.push_back(value);
        process.push_back(id);
        id++;
        instance.push_back(process);
    }

    first_come_first_served(instance);
    shortest_job_first(instance);
    round_robin(instance);

    return 0;
}