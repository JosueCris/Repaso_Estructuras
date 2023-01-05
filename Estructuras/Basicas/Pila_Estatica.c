/*
    Implementacion de una pila estatica
    Utilizando un arreglo
*/
#include <stdio.h>
#include <stdlib.h>
#define size 5

struct Pila_Estatica
{
    int index;
    int storage[size];
};

typedef struct Pila_Estatica Stack;

void stack_begin(Stack *start);
void stack_free(Stack *start);
int is_empty(Stack *start);
int is_full(Stack *start);
int push(Stack *start, int N);
int pop(Stack *start);
void seek(Stack *start);


int main(int argc, char const *argv[])
{
    Stack stack;

    stack_begin(&stack);
    printf("Longitud pila: %d \n", stack.index);
    int num = 1;
    while (!is_full(&stack))
    {
        push(&stack, num);
        num++;
    }
    push(&stack, 9);
    
    // push(&stack, 1);
    // push(&stack, 2);
    // push(&stack, 3);
    // push(&stack, 4);
    // push(&stack, 5);

    printf("PILA: \n");
    seek(&stack);    
    printf("Longitud pila: %d \n", stack.index);

    // for (int i=0; i<size; i++)
    //     printf("%d \n", pop(&stack));
    printf("QUITANDO . . . \n");
    while(!is_empty(&stack))
	{
		printf("%d \n", pop(&stack));
	}
    pop(&stack);

    printf("PILA: \n");
    seek(&stack);
    printf("Longitud pila: %d \n", stack.index);


    return 0;
}

void stack_begin(Stack *start)
{
	start->index = 0;
}

void stack_free(Stack *start)
{
    while (!is_empty(start))
        printf("%d \n", pop(start));
    
}

int is_empty(Stack *start)
{
    if (start->index == 0)
        return 1;
    return 0;
}

int is_full(Stack *start)
{
    if (start->index == size)
        return 1;
    return 0;
}

int push(Stack *start, int N)
{
    if(is_full(start))
    {
        printf("Stack Overflow !!!\n");
        return 0;
    }
    start->storage[start->index] = N;
    start->index++;
	return 1;
}

int pop(Stack *start)
{
    if (is_empty(start))
    {    
        printf("Stack Underflow!!!\n");
        return 0;
    }
    // int aux = start->storage[start->index];
    // (start->index)--;
	// return aux;
    return start->storage[--(start->index)];
}

void seek(Stack *start)
{
    for(int i=start->index-1; i>-1; i--)
		printf("%d \n", start->storage[i]);
}