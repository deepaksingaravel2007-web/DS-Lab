#include <stdio.h>
#include <stdlib.h>

struct heap {
    int c;      // capacity
    int s;      // size
    int *element;
};

typedef struct heap *pqueue;

pqueue initialize(int max) {
    pqueue heap1;
    if (max <= 3) {
        printf("\n Priority queue is too small\n");
        exit(EXIT_FAILURE);
    }
    heap1 = (pqueue)malloc(sizeof(struct heap));
    if (heap1 == NULL) {
        printf("\n Out of space\n");
        exit(EXIT_FAILURE);
    }
    heap1->element = (int *)malloc((max + 1) * sizeof(int));
    if (heap1->element == NULL) {
        printf("\n Out of space\n");
        exit(EXIT_FAILURE);
    }
    heap1->c = max;
    heap1->s = 0;
    heap1->element[0] = 0;  // sentinel
    return heap1;
}

void insert(int x, pqueue H) {
    int i;
    if (H->s == H->c) {
        printf("\n Priority queue is full\n");
        return;
    }
    for (i = ++H->s; H->element[i / 2] > x; i /= 2)
        H->element[i] = H->element[i / 2];
    H->element[i] = x;
}

int deleteMin(pqueue H) {
    int i, child;
    int minElement, lastElement;

    if (H->s == 0) {
        printf("\n Priority queue is empty\n");
        return -1;
    }

    minElement = H->element[1];
    lastElement = H->element[H->s--];

    for (i = 1; i * 2 <= H->s; i = child) {
        child = i * 2;
        if (child != H->s && H->element[child + 1] < H->element[child])
            child++;
        if (lastElement > H->element[child])
            H->element[i] = H->element[child];
        else
            break;
    }
    H->element[i] = lastElement;
    return minElement;
}

void display(pqueue H) {
    if (H->s == 0) {
        printf("Priority Queue is empty\n");
        return;
    }
    printf("Priority Queue elements: ");
    for (int i = 1; i <= H->s; i++) {
        printf("%d ", H->element[i]);
    }
    printf("\n");
}

int main() {
    int max, choice, x;
    printf("Enter the maximum size of priority queue: ");
    scanf("%d", &max);

    pqueue H = initialize(max);

    while (1) {
        printf("\n*** Priority Queue (Min Heap) ***\n");
        printf("1. Insert\n");
        printf("2. Delete Min\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &x);
                insert(x, H);
                break;
            case 2:
                x = deleteMin(H);
                if (x != -1)
                    printf("Deleted min element: %d\n", x);
                break;
            case 3:
                display(H);
                break;
            case 4:
                free(H->element);
                free(H);
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
