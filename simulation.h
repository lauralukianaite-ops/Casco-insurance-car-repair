#ifndef SIMULATION_H
#define SIMULATION_H

typedef struct{
    long model_time;
    int K;
    int T1;
    int T2;
    int A;
    int A1;
    int U;
} SimulationParams;

void simulate(SimulationParams p);
void readParamsFromFile(const char* filename, SimulationParams* params);

#endif