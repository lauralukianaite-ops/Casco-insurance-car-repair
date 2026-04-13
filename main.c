#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simulation.h"

void readParamsFromFile(const char* filename, SimulationParams* params) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error! Cannot open file %s\n", filename);
        exit(1); 
    }

    int* fields[] = {
        (int*)&params->model_time, &params->K, &params->T1, &params->T2, &params->A, &params->A1, &params->U
    };

    char line[256];
    for (int i = 0; i < 7; ++i) {
        if (fgets(line, sizeof(line), file)) {
            sscanf(line, "%d", fields[i]);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]){
    char file_name[256] = "";
    int seed = -1;

    //Ieskoma -rnd ir failo vardo
    for(int i=1; i < argc; i++){
        if(strcmp(argv[i], "-rnd") == 0 && i + 1 < argc){
            seed = atoi(argv[i+1]);
            i++;
        } else if(file_name[0] == '\0'){ //ar failo vardas dar neivestas, jei ne rnd - tai bus config failas
            strcpy(file_name, argv[i]);
        }
    }

    if(file_name[0] == '\0'){
        strcpy(file_name, argv[0]);
        char *dot = strrchr(file_name, '.');
        if(dot != NULL){
            strcpy(dot, ".cfg");
        } else { //jei galunes nebuvo
            strcat(file_name, ".cfg");
        }
    }

    if(seed == -1) {
        seed = (int)time(NULL) % 1000;
    }
    srand(seed);
    printf("Initialising seed: %d\n",seed);

    SimulationParams p;
    readParamsFromFile(file_name, &p);
    
    simulate(p);
    return 0;
}