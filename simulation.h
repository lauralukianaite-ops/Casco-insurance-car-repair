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
} Params;

void simulate(Params p);

#endif