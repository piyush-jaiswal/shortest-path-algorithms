// #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Stack using dynamic arrays
typedef struct stack
{
    int top;
    int size;
    int *st;
}Stack;

void push_reallocate_stack(Stack *s)
{
    int i;
    int *ar = (int*) malloc(s -> size * 2 * sizeof(int));
    
    for (i = 0; i <= s -> top; i++)
        ar[i] = s -> st[i];
    
    s -> size *= 2;
    free(s -> st);
    s -> st = ar;
}

void pop_reallocate_stack(Stack *s)
{
    int i;
    int *ar = (int*) malloc(s -> size / 2 * sizeof(int));
    
    for (i = 0; i <= s -> top; i++)
        ar[i] = s -> st[i];
    
    s -> size /= 2;
    free(s -> st);
    s -> st = ar;
}

void push(Stack* s, int x)
{
    if (s -> top == s -> size - 1)
        push_reallocate_stack(s);
    s -> top++;
    s -> st[s -> top] = x;
}

bool empty(Stack *s)
{
    return s -> top == -1;
}

void pop(Stack *s)
{
    s -> top--;
    if (!empty(s))
    {
        if (s -> top == s -> size / 2 - 1)
            pop_reallocate_stack(s);
    }
}

int top(Stack *s)
{
    if (!empty(s))
        return s -> st[s -> top];
    return -99999999;
}

// Returns a stack with initial size as 1
Stack* createStack()
{
    Stack *s = (Stack*) malloc(sizeof(Stack));
    s -> top = -1;
    s -> size = 1;
    s -> st = (int*) malloc(s -> size * sizeof(int));
    return s;
}

// int main()
// {
//     Stack *s = createStack();

//     push(s, 1);
//     printf("%d\n", top(s));
//     push(s, 2);
//     printf("%d\n", top(s));
//     push(s, 3);
//     printf("%d\n", top(s));
//     push(s, 4);
//     printf("%d\n", top(s));
//     push(s, 5);
//     printf("%d\n", top(s));
//     push(s, 6);
//     printf("%d\n", top(s));
//     push(s, 7);
//     printf("%d\n", top(s));
//     push(s, 8);
//     printf("%d\n", top(s));

//     printf("\n\n\n");

//     printf("%d\n", top(s));
//     pop(s) ;
//     printf("%d\n", top(s));
//     pop(s) ;
//     printf("%d\n", top(s));
//     pop(s) ;
//     printf("%d\n", top(s));
//     pop(s) ;
//     printf("%d\n", top(s));
//     pop(s) ;
//     printf("%d\n", top(s));
//     pop(s) ;
//     printf("%d\n", top(s));
//     pop(s) ;
//     printf("%d\n", top(s));
//     pop(s);

//     printf("%d\n", top(s));
//     pop(s) ;

//     return 0;
// }
