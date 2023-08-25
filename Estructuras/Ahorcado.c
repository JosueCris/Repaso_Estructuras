#include <stdio.h>
#include <stdlib.h>

void instructions();
int length(char *cad);
char *asteriscos(char *cad, int len);
int discover(char *orig, char *ocul, char prop, int score);
int compare(char *orig, char *ocul);
void play(char *prop, char *ocul, int *score);
void game_over(char *player1, int score1, char *player2, int score2);

int main()
{
    int punt1=100, punt2=100, long1, long2;
    char palabra1[20], palabra2[20], jugador1[10], jugador2[10], *oculta1, *oculta2;
    
    instructions();
    printf("\n");

    //  Registro de ambos jugadores
    printf("Ingrese el nombre del jugador 1: ");
    scanf("%s", jugador1);
    printf("Ingrese el nombre del jugador 2: ");
    scanf("%s", jugador2);
    system("clear || cls");

    //  Ambos jugadores ingresan sus palabras.
    printf("%s:\n", jugador1);
    printf("Ingresa una palabra: ");
    scanf("%s", palabra1);

    system("clear || cls");

    printf("%s:\n", jugador2);
    printf("Ingresa una palabra: ");
    scanf("%s", palabra2);

    //  Obtenemos la longitud de las dos palabras.
    long1 = length(palabra1);
    long2 = length(palabra2);

    //  Las palabras dadas son ocultas en asteriscos para poder adivinarlas.
    //oculta1 = asteriscos(palabra1, long1);
    //oculta2 = asteriscos(palabra2, long2);
    oculta1 = asteriscos(palabra1, length(palabra1));
    oculta2 = asteriscos(palabra2, length(palabra2));

    system("clear || cls");

    //  Fuerzo un ciclo para que los dos jugadores estren en el juego.
    while(1)
    {
       /* printf("Turno de %s: \n", jugador1);
        if (punt1 <= 0)
            break;
*/
        while(compare(palabra2, oculta2) != 0) //  Va validando iterativamente si la palabra se va acercando.
        {
            play(palabra2, oculta2, &punt1); // El jugador va ingresando las letras.
            system("cls || clear");
            //  Estado del jugador por intento.
            printf("Turno de %s: \n", jugador1);
            printf("Palabra oculta: %s \n", oculta2);
            printf("Puntaje actual: %d \n\n", punt1);
        }
        printf("%s ha descifrado la palabra de %s !!! \n\n", jugador1, jugador2);
        system("clear || cls");

        //  Todo lo mismo pero con el jugador 2.
        printf("Turno de %s: \n", jugador2);
       /* if (punt2 <= 0)
            break;
*/
        while(compare(palabra1, oculta1) != 0)
        {
            play(palabra1, oculta1, &punt2);
            system("cls || clear");
            printf("Turno de %s: \n", jugador2);
            printf("Palabra oculta: %s \n", oculta1);
            printf("Puntaje actual: %d \n\n", punt2);
        }
        printf("%s ha descifrado la palabra de %s !!! \n\n", jugador2, jugador1);
        system("clear || cls");
        break;
    }

    game_over(jugador1, punt1, jugador2, punt2);  // Puntuaciones finales y quien es el ganador.

    return 0;
}

void instructions()
{
    printf("*** (o_o) BIENVENIDO AL JUEGO DEL AHORCADO !!! ***\n");
    printf("Esta es una variante del juego original.\nPermiteme explicarte las reglas.\n\n");
    printf("INSTRUCCIONES: \n\t");
    printf("1.- Este es un juego para dos jugadores y cada uno empezara con 100 puntos. \n\t");
    printf("2.- Cada jugador debera ingresar una palabra para que el contricante pueda adivinarla. \n\t");
    printf("3.- El jugador en turno intentara adivinar la palabra ingresando letras, si la letra es correcta\n\t    se ira descubriendo incluso si es repetida, pero si es incorrecta se le restaran 2 puntos.\n\t");
    printf("4.- Al final del juego se compararan los puntajes y se mostrara al ganador. \n\n");
    printf("Mucha suerte y diviertanse :) \n");
}

/*  Esta funcion me sirve para calcular la longitud de la palabra, ambos jugadores no siempre pondran palabras de 
    la misma longitud.    */
/*
int length(char *cad)
{
    int count = 0;
    while (*cad != '\0')
    {
        count++;
        cad++;
    }
    return count;
}*/


//  La misma funcion length pero en recursivo, ambas funcionan, ocupa el que mas te agrade comentando una y descomentando otra.
/*
int length(char *cad)
{
    if(*cad == '\0')
        return 0;
    return 1 + length(++cad);
}*/


//  Sintaxis endulzada de la funcion recursiva, funciona igual que las otras dos.
int length(char *cad)
{
    return (*cad == '\0') ? 0 : (1 + length(++cad));
}


/*  En esta funcion genero una nueva cadena de asteriscos con la misma cantidad de caracteres (para eso ocupo length) 
    que la palabra dada, esto con el fin de aparentar que oculto la palabra sin modificar la original necesariamente   */
char *asteriscos(char *cad, int len)
{
    char *aux = (char *) malloc((len + 1) * sizeof(char));
    int i;
    for (i=0; i<len; i++)
        aux[i] = '*';
    aux[i] = '\0';
    return aux;
}


/*  En esta funcion mi cadena de asteriscos si se vera modificada cada vez que el jugador acierte, cada asterisco sera
    remplazada por la letra correcta, si se equivoca el puntaje decrementa de 2 en 2.  */
int discover(char *orig, char *ocul, char prop, int score)
{
    int i;
    int acertado = 0;
/*
    if (score <= 0) {
        printf("Perdiste tus puntos !!!\n");
        return score;
    }*/

    for (i=0; i<length(orig); i++)
    {
        if ((orig[i] == prop) && (ocul[i] == '*'))
        {
            ocul[i] = prop;
            acertado = 1;
        }
    }

    if (!acertado)
        score -= 2;

    return score;
}


/*  Esto me servira al final para comparar los asteriscos modificados con la palabra original,
    si la funcion devuelve 0 significa que las palabras no son iguales, y si retorna 1, indica que si lo son */
int compare(char *orig, char *ocul)
{
    if (*orig == *ocul) {
        if (*orig == '\0')
            return 0;
        return compare(++orig, ++ocul);
    }
    return 1;
}


/*  Aqui se ingresa la letra y se manda a llamar la funcion discover, esta funcion se manda a llamar en
    el main constantemente.*/
void play(char *prop, char *ocul, int *score)
{
    char letra;
    printf("Ingresa una letra: ");
    scanf(" %c", &letra);

    *score = discover(prop, ocul, letra, *score);
}


//  En esta parte mostramos los resultados finales.
void game_over(char *player1, int score1, char *player2, int score2)
{
    printf("*** (x_x) Fin del juego !!! *** \n\n");
    printf("Marcador Final: \n");
    printf("%s: %d puntos \n", player1, score1);
    printf("%s: %d puntos \n\n", player2, score2);

    if (score1 > score2)
        printf("%s ha sido el/la ganador(a) !!! \n", player1);
    else 
        if (score2 > score1)
            printf("%s ha sido el/la ganador(a) !!! \n", player2);
    else
        printf("Es un empate !!! \n");
}