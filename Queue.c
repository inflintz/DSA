#include <stdio.h>
#include <stdlib.h>

struct queue_record {
    unsigned int q_max_size;
    unsigned int q_front;
    unsigned int q_rear;
    unsigned int q_size;
    int *q_array;
};

typedef struct queue_record QUEUE;

void make_null(QUEUE* Q, unsigned int max_size) {
    Q->q_max_size = max_size;
    Q->q_array = (int*)malloc(sizeof(int) * max_size);
    Q->q_front = 0;
    Q->q_rear = -1;
    Q->q_size = 0;
}

int is_full(QUEUE* Q) {
    return Q->q_size == Q->q_max_size;
}

int is_empty(QUEUE* Q) {
    return Q->q_size == 0;
}

void enqueue(int X, QUEUE* Q) {
    if (is_full(Q)) {
        printf("Queue is Full\n");
        return;
    }
    Q->q_rear++;
    Q->q_array[Q->q_rear] = X;
    Q->q_size++;
}

void dequeue(QUEUE* Q) {
    if (is_empty(Q)) {
        printf("Queue is Empty\n");
        return;
    }
    Q->q_front++;
    Q->q_size--;
}

void print_queue(QUEUE* Q) {
    if (is_empty(Q)) {
        printf("Queue is Empty\n");
        return;
    }
    for (unsigned int i = Q->q_front; i <= Q->q_rear; i++) {
        printf("%d ", Q->q_array[i]);
    }
    printf("\n");
}

int main() {
    unsigned int max_size = 10;
    QUEUE Q;

    make_null(&Q, max_size);

    enqueue(10, &Q);
    enqueue(20, &Q);
    enqueue(30, &Q);

    printf("Queue after enqueue operations: ");
    print_queue(&Q);

    dequeue(&Q);

    printf("Queue after one dequeue operation: ");
    print_queue(&Q);

    enqueue(40, &Q);

    printf("Queue after enqueueing 40: ");
    print_queue(&Q);

    return 0;
}
