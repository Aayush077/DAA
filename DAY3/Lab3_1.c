/*Write a menu-driven program in C to implement a stack using an array.
The program must allow the user to perform the following operations:

Menu:
1. Push an element onto the stack
2. Pop an element from the stack
3. Peek (View the top element)
4. Check if the stack is empty
5. Check if the stack is full
6. Display all elements in the stack
7. Exit

*/

#include<stdio.h>
#include<stdlib.h>

struct stack 
{
    int size;
    int top;
    int *arr;
} st;

int isEmpty(struct stack *st)
{
    if(st->top == -1)
    {
        return 1;
    }
    return 0;
}

int isFull(struct stack *st)
{
    if(st->top == st->size - 1)
    {
        return 1;
    }
    return 0;
}

void push(struct stack *st, int x)
{
    if(isFull(st))
    {
        printf("Stack Overflow\n");
    }
    else
    {
        st->top++;
        st->arr[st->top] = x;
    }
}

int pop(struct stack *st)
{
    if(isEmpty(st))
    {
        printf("Stack Underflow\n");
        return -1;
    }
    else
    {
        int x = st->arr[st->top];
        st->top--;
        return x;
    }
}

void peek(struct stack *st)
{
    if (isEmpty(st))
    {
        printf("Stack is empty\n");
    }
    else
    {
        printf("Top element is: %d\n", st->arr[st->top]);
    }
}

int display(struct stack *st)
{
	printf("Stack elements are: ");
    for (int i = st->top; i >= 0; i--)
    {
        printf("%d ", st->arr[i]);
    }   
    printf("\n");
}

int main()
{
    int n, value, choice;
    printf("Enter the size of the stack: ");
    scanf("%d", &st.size);
    st.arr = (int *)malloc(st.size * sizeof(int));
    st.top = -1;
    while(1)
    {
        printf("1. Push\n2. Pop\n3. Check stack is empty or not\n4. Check stack is full or not\n5. Peek\n6. Display stack elements\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                printf("Enter the value to push: ");
                scanf("%d", &value);
                push(&st, value);
                break;
            case 2:
                printf("Popped element is: %d\n", pop(&st));
                break;
            case 3:
                if(isEmpty(&st))
                {
                    printf("Stack is empty\n");
                }
                else
                {
                    printf("Stack is not empty\n");
                }
                break;
            case 4:
                if(isFull(&st))
                {
                    printf("Stack is full\n");
                }
                else
                {
                    printf("Stack is not full\n");
                }
                break;
            case 5:
                peek(&st);
                break;
            case 6:
                display(&st);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

