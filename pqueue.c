#include <stdio.h>
#include <stdlib.h>

#define MAX_PQ_SIZE 50

typedef struct Node
{
    int value;
    int priority;
    struct Node *next;
} Node;

typedef struct PQueue
{
    int size;
    Node *top;
} PQueue;

PQueue *create_pq()
{
    PQueue *pq = (PQueue*)malloc(sizeof(PQueue));
    pq->size = 0;
    pq->top = NULL;
    return pq;
}

int count_pq(PQueue *pq)
{
    int cnt = 0;
    if(pq->top == NULL)
    {
        return cnt;
    }

    Node *node = pq->top;
    while(node != NULL)
    {
        cnt++;
        node = node->next;
    }

    return cnt;
}

int isEmpty_pq(PQueue *pq)
{
    return (count_pq(pq)) ? 0 : 1;
}

int isFull_pq(PQueue *pq)
{
    if(count_pq(pq) >= MAX_PQ_SIZE) return 1;
    else return 0;
}
void push_pq(PQueue *pq, int value, int priority)
{
    if(isFull_pq(pq) == 1) return;

    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->value = value;
    newnode->priority = priority;
    newnode->next = NULL;

    if (pq->size == 0|| pq->top->priority > priority)
    {
        newnode->next = pq->top;
        pq->top = newnode;
    }
    else
    {
        Node *dabar = pq->top;
        while (dabar->next != NULL && dabar->next->priority >= priority)
        {
            dabar = dabar->next;
        }
        newnode->next = dabar->next;
        dabar->next = newnode;
    }

    pq->size++;
}

int pop_pq(PQueue *pq)
{
    if (pq->size==0)
    {
        return -1;
    }

    Node *temp = pq->top;
    int value = temp->value;

    pq->top = temp->next;
    free(temp);

    pq->size--;

    return value;
}


void toString_pq(PQueue *pq)
{
    if(pq->top == NULL)
    {
        return;
    }

    Node *node = pq->top;
    int cnt = 0;
    while(node != NULL && cnt <= 10)
    {
        cnt++;
        printf("(%d, p=%d)->", node->value, node->priority);
        node = node->next;
    }
    printf("\n");
}

int peek_pq(PQueue *pq)
{
    if(pq == NULL) printf("Empty.");
    else return (pq->top->value);
}

PQueue *clone_pq (PQueue *pq)
{
    

    PQueue *naujas = (PQueue*)malloc(sizeof(PQueue));

    if(pq == NULL) return NULL;


    naujas->size = pq->size;
    if(naujas->size == 0) return naujas;

    if(pq->top == NULL)
    {
        naujas->top = NULL;
        return naujas;
    }

    Node *node = pq->top;
    Node *nnode = (Node*)malloc(sizeof(Node));
    nnode->priority = node->priority;
    nnode->value = node->value;
    nnode->next = NULL;
    naujas->top = nnode;
    while(node->next != NULL)
    {
        Node *tmp = (Node*)malloc(sizeof(Node));
        node = node->next;
        tmp->value = node->value;
        tmp->priority = node->priority;
        tmp->next = NULL;

        nnode->next = tmp;
        nnode = tmp;
    }

    return naujas;
}

void makeEmpty_pq(PQueue *pq)
{
    while(pq->top != NULL){
        Node *temp = pq->top;

        pq->top = temp->next;
        free(temp);
        pq->size--;
    }

}

void destruct_pq(PQueue **pq)
{
    makeEmpty_pq(*pq);
    free(*pq);
    *pq = NULL;
}