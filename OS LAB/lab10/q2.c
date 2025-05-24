#include <stdio.h>
#include <stdlib.h>

#define maxp 100
#define timequant 5

typedef struct {
    int id, bt, remt, arrt, qlvl;
} Process;

typedef struct {
    Process *processes[maxp];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, Process *p) {
    if (q->rear == maxp - 1) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(q)) q->front = 0;
    q->processes[++q->rear] = p;
}

Process* dequeue(Queue *q) {
    if (isEmpty(q)) return NULL;
    Process *p = q->processes[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return p;
}

Process* createProcess(int id, int bt, int arrt, int qlvl) {
    Process *p = malloc(sizeof(Process));
    *p = (Process){id, bt, bt, arrt, qlvl};
    return p;
}

void processFCFS(Queue *q) {
    while (!isEmpty(q)) {
        Process *p = dequeue(q);
        printf("Processing P%d (FCFS) for %d time units.\n", p->id, p->remt);
        free(p);
    }
}

void processSJF(Queue *q) {
    while (!isEmpty(q)) {
        int minIndex = q->front;
        for (int i = q->front; i <= q->rear; i++) {
            if (q->processes[i]->remt < q->processes[minIndex]->remt) {
                minIndex = i;
            }
        }
        Process *temp = q->processes[q->front];
        q->processes[q->front] = q->processes[minIndex];
        q->processes[minIndex] = temp;

        Process *p = dequeue(q);
        printf("Processing P%d (SJF) for %d time units.\n", p->id, p->remt);
        free(p);
    }
}

void processRoundRobin(Queue *q, Queue *nextQueue) {
    while (!isEmpty(q)) {
        Process *p = dequeue(q);
        int timeToProcess = (p->remt < timequant) ? p->remt : timequant;

        printf("Processing P%d (Round Robin) for %d time units.\n", p->id, timeToProcess);
        p->remt -= timeToProcess;

        if (p->remt > 0) {
            if (nextQueue != NULL) {
                p->qlvl++;
                printf("Moving P%d to Queue Level %d.\n", p->id, p->qlvl);
                enqueue(nextQueue, p);
            } else {
                enqueue(q, p);
            }
        } else {
            printf("Process P%d completed.\n", p->id);
            free(p);
        }
    }
}

void multilevelQueueScheduler(Queue queues[], int numQueues) {
    for (int i = 0; i < numQueues; i++) {
        if (!isEmpty(&queues[i])) {
            printf("\nProcessing Queue Level %d:\n", i);
            switch (i) {
                case 0:
                    processFCFS(&queues[i]);
                    break;
                case 1:
                    processSJF(&queues[i]);
                    break;
                case 2:
                    processRoundRobin(&queues[i], NULL);
                    break;
                default:
                    printf("Unknown queue level %d\n", i);
            }
        }
    }
}

int main() {
    Queue queues[3];
    for (int i = 0; i < 3; i++) initQueue(&queues[i]);

    enqueue(&queues[0], createProcess(1, 10, 0, 0)); 
    enqueue(&queues[1], createProcess(2, 5, 0, 1));
    enqueue(&queues[2], createProcess(3, 8, 0, 2));
    enqueue(&queues[2], createProcess(4, 2, 0, 2));
    enqueue(&queues[1], createProcess(5, 3, 0, 1));
    enqueue(&queues[0], createProcess(6, 1, 0, 0));
    enqueue(&queues[2], createProcess(7, 6, 0, 2));
    enqueue(&queues[0], createProcess(8, 4, 0, 0));

    printf("Starting Multilevel Queue Scheduling:\n");
    multilevelQueueScheduler(queues, 3);

    return 0;
}
