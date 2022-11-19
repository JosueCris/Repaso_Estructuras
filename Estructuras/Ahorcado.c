#include <stdio.h>
#include <stdlib.h>

int length(char *cad);
char *asteriscos(char *cad, int longitud);
int player(char *original, char *oculta, char *propuesta, int score);

int main(int argc, char const *argv[])
{
	char word1[20], word2[20], *oculto1, *oculto2, letra1[2], letra2[2];
	int score1=100, score2=100;
	
	printf("Ingresa una palabra para el jugador 2: \n> ");
	scanf("%s", &word2);

	oculto2 = asteriscos(word2, length(word2));
	printf("Palabra normal: %s \n", word2);
	printf("Palabra en asteriscos: %s \n", oculto2);

	printf("Ingresa una letra: ");
	scanf("%s", &letra2);
	int puntaje = player(word2, oculto2, letra2, score2);
	printf("\nPuntaje final: %d \n", puntaje);
	return 0;
}

int length(char *cad)
{
	if(*cad == '\0')
		return 0;
	return length(++cad) + 1;
}

char *asteriscos(char *cad, int longitud)
{
	int i;
	char *aux = (char *) malloc(sizeof(longitud));
	for(i=0; i<longitud; i++)
		aux[i] = '*';	
	aux[i] = '\0';
	return aux;
}

int player(char *original, char *oculta, char *propuesta, int score)
{
	int i = 0;
	for(i=0; i<length(original); i++)
	{
		if (*propuesta == original[i])
			oculta[i] = original[i];
		else
			score -= 2;
	}
	printf("Palabra oculta: %s \n", oculta);
	return score;
}

