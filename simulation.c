#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"
#include "pqueue.h"
#include "BigInt.h"

#define WORK_HOURS 8

void simulate(Params p){
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
        int TR_random = (rand() % (p.K*5)) + 1;

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
}

