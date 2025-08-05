/*Write a menu-driven program in C to implement a queue using a singly linked list.
Your program must allow the user to perform the following queue operations:

Menu:
1. Enqueue (Insert an element at the rear)
2. Dequeue (Remove an element from the front)
3. Peek (View the front element)
4. Check if the queue is empty
5. Display all elements in the queue
6. Exit*/

#include <stdio.h>
#include <stdlib.h>

struct Queue
{
    int size;
    int front;
    int rear;
    int *Q;
};

void enqueue(struct Queue *q,int x)
{
    if(q->rear == q->size-1)
        printf("Queue is full");
    else
    {
        q->rear++;
        q->Q[q->rear] = x;
    }
}

void dequeue(struct Queue *q,int x)
{
    if(q->front == q->rear)
        printf("Queue is empty");
    else
    {
        q->front++;
        x=q->Q[q->front];
    }
}

void peek(struct Queue *q)
{
    if(q->front == q->rear)
        printf("Queue is empty");
    else
        printf("Front element is: %d\n", q->Q[q->front + 1]);

}

void isEmpty(struct Queue *q)
{
    if(q->front == q->rear)
        printf("Queue is Empty");
    else
        printf("Queue has elements");
}

void display(struct Queue q)
{
    printf("Queue elements are: ");
    for(int i = q.front+1;i<=q.rear;i++)
    {
        printf("%d ", q.Q[i]);
    }
    printf("\n");
}


int main()
{
    struct Queue q;
    printf("Enter the size of the queue: ");
    scanf("%d", &q.size);
    q.front = q.rear = -1;
    q.Q = (int *)malloc(q.size * sizeof(int));
    int choice, x;

    while(1)
    {
        printf("Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Check if the queue is empty\n");
        printf("5. Display all elements in the queue\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter element to enqueue: ");
                scanf("%d", &x);
                enqueue(&q, x);
                break;
            case 2:
                dequeue(&q, x);
                break;
            case 3:
                peek(&q);
                break;
            case 4:
                isEmpty(&q);
                break;
            case 5:
                display(q);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}
