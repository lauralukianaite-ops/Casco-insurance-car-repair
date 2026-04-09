#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInt.h"
#include "pqueue.h"

int main(){
    printf("Trying to connect files...\n");

    //Tikrinamas BigInt
    BigInt *number = bigint_from_str("100");
    char *text = bigint_to_str(number);
    printf("BigInt working, the number is: %s\n", text);

    //Tikrinamas PQueue
    PQueue *queue = create_pq();
    push_pq(queue, 50, 1);
    printf("Priority Queue is working, number of elements: %d\n", count_pq(queue));

    //Isvaloma atmintis
    free(text);
    bigint_free(number);
    destruct_pq(&queue);

    printf("All good\n");
    return 0;
}