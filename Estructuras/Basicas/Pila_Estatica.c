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

void menu();
int length(Stack *start);

void stack_begin(Stack *start);
int is_empty(Stack *start);
int is_full(Stack *start);
int push(Stack *start, int N);
int pop(Stack *start);
void seek(Stack *start);
void stack_free(Stack *start);


int main(int argc, char const *argv[])
{
    Stack stack;
    int option, number, buscar;

    stack_begin(&stack);

    do
	{
		menu();
		scanf("%d", &option);

		switch(option)
		{
			case 1:
				printf("Insert the number in the stack: ");
				scanf("%d", &number);
				if (push(&stack, number))
                    printf("Inserted \n\n");
                else
                    printf("No inserted!!! \n\n");
				break;

			case 2:
				printf("\nSTACK: \n");
				seek(&stack);
				printf("\n\n");
				break;		
			
			case 3: 
// 				printf("Insert the number to search: ");
// 				scanf("%d", &number);
// //				Stack *item = search(&stack, NULL, number);
// 				search(&stack, NULL, number);
// /*				if (item)
// 					printf("Founded: %d \n\n", item->data);
// 				else
// 					printf("No Exist!!!\n\n");
// */
// 				break;

			case 4:
				if (pop(&stack))
                    printf("Deleted \n\n");
                else
                    printf("No delete!!! \n\n");
				break;

			case 0:
				printf("\nSee you later :D \n\n");
				return 0;
				break;	

			default:
				printf("Try Again!!!");
				break;	
		}
	}while(option != 0);

    // printf("Longitud pila: %d \n", stack.index);
    // int num = 1;
    // while (!is_full(&stack))
    // {
    //     push(&stack, num);
    //     num++;
    // }
    // push(&stack, 9);

    // printf("PILA: \n");
    // seek(&stack);    
    // printf("Longitud pila: %d \n", stack.index);

    // printf("QUITANDO . . . \n");
    // while(!is_empty(&stack))
	// {
	// 	printf("%d \n", pop(&stack));
	// }
    // pop(&stack);

    // printf("PILA: \n");
    // seek(&stack);
    // printf("Longitud pila: %d \n", stack.index);


    return 0;
}

void menu()
{
	printf("Select your option to choice from the stack: \n\t");
	printf("[1]: Insert\n\t[2]: Show\n\t[3]: Search\n\t[4]: Delete\n\t[0]: Exit\n> ");
}

int length(Stack *start)
{
    return start->index;
}

void stack_begin(Stack *start)
{
	start->index = 0;
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

void stack_free(Stack *start)
{
    while (!is_empty(start))
        printf("%d \n", pop(start));
    
}