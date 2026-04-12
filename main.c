#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "BigInt.h"
#include "pqueue.h"
#define WORK_HOURS 8

typedef struct{
    long model_time; //kiek laiko trunka simuliacija
    int K; //darbuotoju skaicius
    int T1; //vip kliento tikimybe
    int T2; //paprasto kliento tikimybe
    int A; //francize
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
    if(fscanf(f, "%ld %d %d %d %d %d %d", &p.model_time, &p.K, &p.T1, &p.T2, &p.A, &p.A1, &p.U) != 7){
        printf("Error! Parameters missing or entered in incorrect format\n");
        return 1;
    }

    //Modeliavimo paruosimas
    PQueue *queue = create_pq();
    int *workers = calloc(p.K, sizeof(int));
    BigInt *profit = bigint_from_str("0");  

    //Pagalbiniai BigInt kintamieji
    char buffer[32];
    sprintf(buffer, "%d", p.U);
    BigInt *salary = bigint_from_str(buffer);
    sprintf(buffer, "%d", 2*p.U);
    BigInt *overtime_salary = bigint_from_str(buffer);
    sprintf(buffer, "%d", p.A - p.A1);
    BigInt *profit_reg = bigint_from_str(buffer);
    sprintf(buffer, "%d", p.A + p.A1);
    BigInt *profit_vip = bigint_from_str(buffer);

    int total_vip = 0;
    int total_reg = 0;
    int total_overtime_h = 0;

    for(int i=0; i < p.model_time; i++){
        //Darbuotojai gauna iprasta atlyginima kiekviena valanda
        for(int j=0; j<p.K; j++){
            BigInt *temp = bigint_sub(profit, salary);
            bigint_free(profit);
            profit = temp;
            if(workers[j]>0){
                workers[j]--;
            }
        }

        int r = rand() % 100;
        int TR_random = (rand() % p.K*5) + 1;

        if(r < p.T1){
            total_vip++;

            BigInt *temp = bigint_add(profit, profit_vip);
            bigint_free(profit);
            profit = temp;

            if(TR_random > WORK_HOURS){
                int overtime = TR_random - WORK_HOURS;
                total_overtime_h += overtime;
                for(int o = 0; o < overtime; o++){
                    BigInt *temp = bigint_sub(profit, overtime_salary);
                    bigint_free(profit);
                    profit = temp;
                }
            }

            //Priskiriamas laisvas darbuotojas
            int found = 0;
            for(int j = 0; j < p.K; j++){ 
                if(workers [j] == 0){
                    workers[j] = TR_random;
                    found = 1;
                    break;
                }
            }
            if(!found){
                push_pq(queue, TR_random, 0);
            }
        } else if(r <= p.T1 + p.T2){
            push_pq(queue,TR_random,1);
            total_reg++;
            BigInt *temp = bigint_add(profit, profit_reg);
            bigint_free(profit);
            profit = temp;
        }

        //Laisviems darbuotojams priskiriamas automobilis is eiles
        for(int j=0; j<p.K; j++){
            if(workers[j] == 0 && !isEmpty_pq(queue)){
                workers[j] = pop_pq(queue);
            }
        }
    }

    //Modeliavimo rezultatai
    char *final_profit_str = bigint_to_str(profit);
    printf("VIP cutomers: %d, regular customers: %d\n", total_vip, total_reg);
    printf("Total overtime work hours: %d\n", total_overtime_h);
    printf("Total profit: %s\n", final_profit_str);

    free(final_profit_str);
    bigint_free(profit);
    bigint_free(salary);
    bigint_free(profit_reg);
    bigint_free(profit_vip);
    free(workers);
    destruct_pq(&queue);
    return 0;
}