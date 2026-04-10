#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "BigInt.h"
#include "pqueue.h"

typedef struct{
    long model_time; //kiek laiko trunka simuliacija
    int K; //darbuotoju skaicius
    int T1; //vip kliento tikimybe
    int T2; //paprasto kliento tikimybe
    int TR; //maksimalus automobilio taisymo laikas
    int A; //francize uz kuria servisas gauna papildomu pajamu
    int A1; //suma, atitenkanti servisui
    int U; //darbuotojo atlyginimas
}Params;

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

    Params p;
    FILE *f = fopen(file_name, "r");
    if(f==NULL){
        printf("Error! Cannot open file %s\n",file_name);
        return 1;
    }
    if(fscanf(f, "%ld %d %d %d %d %d %d %d", &p.model_time, &p.K, &p.T1, &p.T2, &p.TR, &p.A, &p.A1, &p.U) != 8){
        printf("Error! Parameters missing or entered in incorrect format\n");
        return 1;
    }
    fclose(f);

    //Ar teisingai perskaite
    printf("Model time: %ld\n", p.model_time);
    printf("Workers: %d\n", p.K);
    return 0;
}