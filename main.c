#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(){
    char file_name[50] = "data.txt";
    Params p;

    FILE *f = fopen(file_name, "r");
    if(f==NULL){
        printf("Error! Cannot open file %s\n",file_name);
    }
    if(fscanf(f, "%ld %d %d %d %d %d %d %d", &p.model_time, &p.K, &p.T1, &p.T2, &p.TR, &p.A, &p.A1, &p.U) != 8){
        printf("Error! Parameters missing or entered in incorrect format\n");
    }
    fclose(f);

    //Ar teisingai perskaite
    printf("Model time: %ld\n", p.model_time);
    printf("Workers: %d\n", p.K);
    return 0;
}