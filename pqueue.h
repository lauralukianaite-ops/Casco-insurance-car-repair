#ifndef PQUEUE_H
#define PQUEUE_H

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


PQueue *create_pq();
void push_pq(PQueue *pq, int value, int priority);
int pop_pq(PQueue *pq);
int count_pq(PQueue *pq);
int isEmpty_pq(PQueue *pq);
int isFull_pq(PQueue *pq);
void toString_pq(PQueue *pq);
int peek_pq(PQueue *pq);
void makeEmpty_pq(PQueue *pq);
PQueue *clone_pq (PQueue *pq);
void destruct_pq(PQueue **pq);

#endif