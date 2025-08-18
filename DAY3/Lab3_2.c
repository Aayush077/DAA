/*Write a menu-driven program in C to implement a queue using a singly linked list.
Your program must allow the user to perform the following queue operations:

Menu:
1. Enqueue (Insert an element at the rear)
2. Dequeue (Remove an element from the front)
3. Peek (View the front element)
4. Check if the queue is empty
5. Display all elements in the queue
6. Exit*/

#include<stdio.h>
#include<stdlib.h> 

struct Node
{
    int data;
    struct Node *next;
}*front = NULL, *rear = NULL;

void enqueue(int x)
{
    struct Node *t;
    t=(struct Node *)malloc(sizeof(struct Node));
    if(t==NULL)
    {
        printf("Queue is full\n");
    }
    else
    {
        t->data =x;
        t->next =NULL;
        if(front == NULL)
        {
            front = rear =t;
        }
        else
        {
            rear->next = t;
            rear = t;
        }
    }
}

int dequeue()
{
    int x=-1;
    struct Node *t;

    if(front == NULL)
    {
        printf("Queue is empty\n");
    }
    else
    {
        x=front->data;
        t=front;
        front = front->next;
        free(t);
    }
    return x;
}

void peek()
{
    if(front == NULL)
    {
        printf("Queue is empty\n");
    }
    else
    {
        printf("Front element: %d\n", front->data);
    }
}

int isEmpty()
{
    return front == NULL;
}

int isFull()
{
    struct Node *t = (struct Node *)malloc(sizeof(struct Node));
    if(t == NULL)
    {
        return 1; // Queue is full
    }
    free(t);
    return 0; // Queue is not full
}

void display()
{
    struct Node *p = front;
    while (p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}



int main()
{
    int value, choice;
    while(1)
    {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Check if queue is empty\n");
        printf("5. Display all elements in the queue\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                value = dequeue();
                if(value != -1)
                    printf("Dequeued element: %d\n", value);
                break;
            case 3:
                peek();
                break;
            case 4:
                if(isEmpty())
                    printf("Queue is empty.\n");
                else
                    printf("Queue is not empty.\n");
                break;
            case 5:
                display();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}