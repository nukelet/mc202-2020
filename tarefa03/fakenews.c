#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _termo
{
	char *nome;
	double max, min, media, dp;

	/*
		classificacao:
			0 - bot
			1 - surpreendente
			2 - normal
			3 - local
			4 - irrelevante
	*/

	int classificacao;
} termo;

// TODO: lembrar de alocar a string lida com malloc na hora de dar parse nos dados
termo* new_termo(char *arg_nome, double arg_max, double arg_min, double arg_media, double arg_dp, int classificacao)
{
	termo *pNovoTermo = malloc(sizeof(*pNovoTermo));
	pNovoTermo->nome = arg_nome;
	pNovoTermo->max = arg_max;
	pNovoTermo->min = arg_min;
	pNovoTermo->media = arg_media;
	pNovoTermo->dp = arg_dp;
	pNovoTermo->classificacao = classificacao;

	return pNovoTermo;
}

void destroy_termo(termo* arg_termo)
{
	free(arg_termo->nome);
	free(arg_termo);
}


typedef double* historico;

double get_max_historico(historico arg_historico, int size_historico)
{
	double *it = arg_historico;	// iterador pro começo
	double max = *it;

	for (int i = 0; i < size_historico; i++, it++)
	{
		if (*it > max)
			max = *it;
	}

	return max;
}

double get_min_historico(historico arg_historico, int size_historico)
{
	double *it = arg_historico;	// iterador pro começo
	double min = *it;

	for (int i = 0; i < size_historico; i++, it++)
	{
		if (*it < min)
			min = *it;
	}

	return min;
}

double get_media_historico(historico arg_historico, int size_historico)
{
	double *it = arg_historico;
	double media = 0;

	for (int i = 0; i < size_historico; i++, it++)
	{
		media += *it;
	}

	media /= size_historico;

	return media;
}

double get_dp_historico(historico arg_historico, double media_historico, int size_historico)
{
	double *it = arg_historico;
	double dp = 0;

	for (int i = 0; i < size_historico; i++, it++)
	{
		dp += pow((*it - media_historico),2);
	}

	dp /= size_historico; dp = sqrt(dp);

	return dp;
}

termo* parse_termo(int size_historico)
{
	char *str_nome = malloc(30*sizeof(char));	// alocando espaço pra uma string de 30 caracteres
	scanf("%s", str_nome);

	historico termo_historico = malloc(size_historico*sizeof(double));	// TODO: lembrar de dar free()
	double *it = termo_historico;

	for (int i = 0; i < size_historico; i++, it++)
	{
		scanf("%lf", it);
	}

	double max = get_max_historico(termo_historico, size_historico);
	double min = get_min_historico(termo_historico, size_historico);
	double media = get_media_historico(termo_historico, size_historico);
	double dp = get_dp_historico(termo_historico, media, size_historico);

	int classificacao;

	if (media >= 60.0 && dp > 15.0)
		classificacao = 0;

	else if (media >= 60.0 && dp <= 15.0)
		classificacao = 1;

	else if (media < 60.0 && max >= 80.0 && min > 20.0)
		classificacao = 2;

	else if (media < 60.0 && max >= 80.0 && min <= 20.0)
		classificacao = 3;

	else if (media < 60.0 && max < 80.0)
		classificacao = 4;

	termo* ParsedTermo = new_termo(str_nome, max, min, media, dp, classificacao);

	free(termo_historico);
	return ParsedTermo;
}

int main(int argc, char const *argv[])
{
	int numero_termos, size_historico; scanf("%d %d", &numero_termos, &size_historico);
	termo **ArrayTermos = malloc(numero_termos*sizeof(**ArrayTermos));	// array de termos; TODO: alguma problema aqui
	termo **it = ArrayTermos;

	for (int i = 0; i < numero_termos; i++, it++)
	{
		*it = parse_termo(size_historico);
	}

	it = ArrayTermos;

	for (int i = 0; i < numero_termos; i++, it++)
	{
		printf("%s %.2lf %.2lf %.2lf %.2lf\n", (*it)->nome, (*it)->max, (*it)->min, (*it)->media, (*it)->dp);
	}

	printf("\nRESULTADO:\n");


	for (int type = 0; type < 5; type++)
	{
		it = ArrayTermos;
		int counter = 0;

		for (int i = 0; i < numero_termos; i++, it++)
		{
			if ( (*it)->classificacao == type )
			{
				counter++;
			}
		}

		switch(type)
		{
			case 0:
				printf("Bot (%d):", counter);
				break;

			case 1:
				printf("Surpreendente (%d):", counter);
				break;

			case 2:
				printf("Normal (%d):", counter);
				break;

			case 3:
				printf("Local (%d):", counter);
				break;

			case 4:
				printf("Irrelevante (%d):", counter);
				break;
		}

		it = ArrayTermos;

		for (int i = 0; i < numero_termos; i++, it++)
		{
			if ( (*it)->classificacao == type )
			{
				printf(" %s", (*it)->nome);
			}
		}

		printf("\n");
	}

	//printf("\n");


	// free array
	it = ArrayTermos;
	for (int i = 0; i < numero_termos; i++, it++)
	{
		destroy_termo(*it);
	}

	free(ArrayTermos);

	return 0;
}