#include <stdio.h>
#include <stdlib.h>

#define MAX 100   

typedef struct {
    int *arr;
    int front, rear, count, size;
} CircularQueue;


void initialize(CircularQueue *q, int size);
int isEmpty(CircularQueue *q);
int isFull(CircularQueue *q);
void enqueue(CircularQueue *q, int value);
int dequeue(CircularQueue *q);
void display(CircularQueue *q);
void reverseFirstK(CircularQueue *q, int k);

int main() {
    CircularQueue q;
    int n, choice, value, k;

    printf("Enter the size of the circular queue (max %d): ", MAX);
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Queue size must be between 1 and %d.\n", MAX);
        return 0;
    }

    initialize(&q, n);

    while (1) {
        printf("\n=== Circular Queue Menu ===\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Reverse first k elements\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;

            case 2:
                value = dequeue(&q);
                if (value != -1)
                    printf("Dequeued element: %d\n", value);
                break;

            case 3:
                display(&q);
                break;

            case 4:
                printf("Enter k (number of elements to reverse): ");
                scanf("%d", &k);
                reverseFirstK(&q, k);
                break;

            case 5:
                printf("Exiting program...\n");
                free(q.arr);
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}


void initialize(CircularQueue *q, int size) {
    q->arr = (int *)malloc(size * sizeof(int));
    q->front = 0;
    q->rear = -1;
    q->count = 0;
    q->size = size;
}


int isEmpty(CircularQueue *q) {
    return q->count == 0;
}

int isFull(CircularQueue *q) {
    return q->count == q->size;
}


void enqueue(CircularQueue *q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow! Cannot insert more elements.\n");
        return;
    }
    q->rear = (q->rear + 1) % q->size;
    q->arr[q->rear] = value;
    q->count++;
    printf("%d enqueued successfully.\n", value);
}


int dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! Cannot dequeue.\n");
        return -1;
    }
    int value = q->arr[q->front];
    q->front = (q->front + 1) % q->size;
    q->count--;
    return value;
}


void display(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue contents: ");
    for (int i = 0; i < q->count; i++) {
        int index = (q->front + i) % q->size;
        printf("%d ", q->arr[index]);
    }
    printf("\n");
}


void reverseFirstK(CircularQueue *q, int k) {
    if (k > q->count || k <= 0) {
        printf("Invalid value of k.\n");
        return;
    }

    int *stack = (int *)malloc(k * sizeof(int));

    
    for (int i = 0; i < k; i++) {
        stack[i] = dequeue(q);
    }

    
    for (int i = k - 1; i >= 0; i--) {
        enqueue(q, stack[i]);
    }

    
    for (int i = 0; i < q->count - k; i++) {
        enqueue(q, dequeue(q));
    }

    free(stack);
    printf("First %d elements reversed successfully.\n", k);
}
