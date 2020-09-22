#include <stdio.h>

int main()
{
	int apostadores;	// n° de apostadores
	double premio;		// prêmio total
	scanf("%d %lf", &apostadores, &premio);

	/*
		Guarda cada volante como um vetor de 60
		posições onde numeros_apostados[i][num-1] 
		é igual a:
			1, se num tiver sido apostado
			0, se num não tiver sido apostado
	*/

	int numeros_apostados[1000][60];

	for (int i = 0; i < apostadores; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			scanf("%d", &numeros_apostados[i][j]);
		}
	}

	// Lê os números sorteados

	int numeros_sorteados[6];
	for (int it = 0; it < 6; it++)
	{
		scanf("%d", &numeros_sorteados[it]);
	}

	int faixa_1 = 0, faixa_2 = 0, faixa_3 = 0;		// guarda o número de pessoas em cada faixa
	int faixa_apostador[1000];						// guarda a faixa de cada apostador

	for (int i = 0; i < apostadores; i++)
	{
		int count = 0;

		for (int j = 0; j < 6; j++)
		{
			int index = numeros_sorteados[j] - 1;
			if (numeros_apostados[i][index])
				count++;
		}

		/*
			sintaxe:
				0 - nenhum prêmio
				1 - sena
				2 - quina
				3 - quadra

		*/

		switch(count)
		{
			case 4:
				faixa_apostador[i] = 3;
				faixa_3++;
				break;

			case 5:
				faixa_apostador[i] = 2;
				faixa_2++;
				break;

			case 6:
				faixa_apostador[i] = 1;
				faixa_1++;
				break;

			default:
				faixa_apostador[i] = 0;
		}
	}

	double premio_apostador[1000];

	// Distribui os prêmios

	for (int i = 0; i < apostadores; i++)
	{
		switch(faixa_apostador[i])
		{
			case 3:
				premio_apostador[i] = (0.19 * premio)/faixa_3;
				break;

			case 2:
				premio_apostador[i] = (0.19 * premio)/faixa_2;
				break;

			case 1:
				premio_apostador[i] = (0.62 * premio)/faixa_1;
				break;
				
			default:
				premio_apostador[i] = 0;
		}
	}

	// Imprime os prêmios

	for (int i = 0; i < apostadores; i++)
	{
		printf("%.2f\n", premio_apostador[i]);
	}

}