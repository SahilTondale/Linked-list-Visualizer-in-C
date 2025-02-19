// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// #define MAX_SIZE 100

// struct stack
// {
//     int arr[MAX_SIZE];
//     int top;
// };

// void initialize(struct stack* p_stack)
// {
//     p_stack->top = -1;// Set top 1 to indicate an empty stack
// }

// bool is_empty(struct stack* p_stack)
// {
//     return (p_stack->top == -1);
// }

// bool is_full(struct stack* p_stack)
// {
//     return (p_stack->top == MAX_SIZE - 1);
// }

// void push(struct stack* p_stack, int value)
// {
//     if(is_full(p_stack))
//     {
//         puts("Stack Overflow!");
//         return;
//     }

//     p_stack->arr[++p_stack->top] = value;
//     printf("Pushed %d onto the stack\n", value);
// }

// int pop(struct stack* p_stack)
// {
//     if(is_empty(p_stack))
//     {
//         puts("Stack Underflow");
//         return (-1);
//     }
//     int popped = p_stack->arr[p_stack->top];
//     p_stack->top--;
//     printf("Popped %d from the stack\n", popped);
//     return (popped);
// }

// int peek(struct stack* p_stack)
// {
//     if(is_empty(p_stack))
//     {
//         printf("Stack is Empty\n");
//         return (-1);
//     }
//     return (p_stack->arr[p_stack->top]);
// }

// int main(void)
// {
//     struct stack my_stack;
//     initialize(p_stack);

//     push(p_stack, 3);
//     printf("Top Element:%d\n", peek(p_stack));

//     push(p_stack, 5);
//     printf("Top Element:%d\n", peek(p_stack));

//     push(p_stack, 2);
//     printf("Top element: %d\n", peek(p_stack));

//     push(p_stack, 8);
//     printf("Top element: %d\n", peek(p_stack));

//     while (!is_empty(p_stack)) {
//         printf("Top element: %d\n", peek(p_stack));
//         printf("Popped element: %d\n", pop(p_stack));
//     }

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE   100

struct stack
{
    int arr[MAX_SIZE];
    int top;
};

struct stack* create_stack(void);
void initialize(struct stack* p_stack);
int is_empty(struct stack* p_stack);
int is_full(struct stack* p_stack);
void push(struct stack* p_stack, int value);
void pop(struct stack* p_stack, int* popped);
int peek(struct stack* p_stack);


int main(void)
{
    int data;
    struct stack* p_stack = NULL;
    p_stack = create_stack();
    push(p_stack, 3);
    printf("Top Element:%d\n", peek(p_stack));

    push(p_stack, 5);
    printf("Top Element:%d\n", peek(p_stack));

    push(p_stack, 2);
    printf("Top element: %d\n", peek(p_stack));

    push(p_stack, 8);
    printf("Top element: %d\n", peek(p_stack));

    while (!is_empty(p_stack)) {
        printf("Top element: %d\n", peek(p_stack));
        pop(p_stack, &data);
        printf("Popped element: %d\n", data);
    }
    return (0);

}

struct stack* create_stack(void)
{
    struct stack* p_stack = NULL;
    p_stack = (struct stack*)malloc(sizeof(struct stack));
    if(p_stack == NULL)
    {
        puts("Error in Allocating Memory!");
        exit(-1);
    }
    return (p_stack);
}

void initialize(struct stack* p_stack)
{
    p_stack->top = -1;
}

int is_empty(struct stack* p_stack)
{
    return (p_stack->top == -1);
}

int is_full(struct stack* p_stack)
{
    return (p_stack->top == MAX_SIZE - 1);
}

void push(struct stack* p_stack, int value)
{
    if(is_full(p_stack))
    {
        puts("STACK OVERFLOW!!");
        return;
    }

    p_stack->arr[++p_stack->top] = value;
    printf("Pushed %d onto stack\n", value);
}

void pop(struct stack* p_stack, int* popped)
{
    if(is_empty(p_stack))
    {
        puts("STACK UNDERFLOW");
        return;
    }

    *popped = p_stack->arr[p_stack->top];
    p_stack->top--;
}

int peek(struct stack* p_stack)
{
    if(is_empty(p_stack))
    {
        puts("Stack is empty!!");
        return (-1);
    }
    return (p_stack->arr[p_stack->top]);
}
