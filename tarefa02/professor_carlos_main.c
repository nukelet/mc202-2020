#include <stdio.h>
#include "professor_carlos.h"

Aluno parse_aluno()
{
	Aluno NovoAluno;

	scanf(	"%s %s %d %d %d", 
				NovoAluno.nome,
				NovoAluno.sobrenome, 
				
				&NovoAluno.nascimento.dia,
				&NovoAluno.nascimento.mes,
				&NovoAluno.nascimento.ano 	);

	return NovoAluno; 
}

// void print_aluno(Aluno NovoAluno)
// {
// 	printf(	"nome: %s\nsobrenome: %s\nnascimento: %d %d %d\n", 
// 				NovoAluno.nome,
// 				NovoAluno.sobrenome, 
// 				NovoAluno.nascimento.dia,
// 				NovoAluno.nascimento.mes,
// 				NovoAluno.nascimento.ano 	);
// }

// void print_turma(Turma arg)
// {
// 	Turma *pTurma = &arg;
// 	int qtd_alunos = pTurma->qtd;
// 	for (int j = 0; j < qtd_alunos; j++)
// 	{
// 		print_aluno(pTurma->alunos[j]);
// 		printf("\n");
// 	}

// 	printf("------------------\n");
// }

// void print_todas_turmas(Turma t[], int qtd_turmas)
// {
// 	Turma *pTurma = t;
// 	for (int i = 0; i < qtd_turmas; i++, pTurma++)
// 	{
// 		print_turma(*pTurma);
// 	}
// }

int main(int argc, char const *argv[])
{
	int qtd_turmas, qtd_comandos;
	scanf("%d %d", &qtd_turmas, &qtd_comandos);

	// printf("qtd_turmas: %d\nqtd_comandos: %d\n", qtd_turmas, qtd_comandos);
	// printf("------------------\n");

	Turma t[50];
	Turma *pTurma = t;


	// lê as turmas da entrada
	for (int i = 0; i < qtd_turmas; i++, pTurma++)
	{
		int qtd_alunos;
		scanf("%d", &qtd_alunos);
		pTurma->qtd = qtd_alunos;

		for (int j = 0; j < qtd_alunos; j++)
		{
			pTurma->alunos[j] = parse_aluno();
		}
	}

	for (int i = 0; i < qtd_comandos; i++)
	{
		int id; scanf("%d", &id);
		// printf("executing task: %d\n", id);

		if (id == 1)
		{
			int j; scanf("%d", &j);
			Aluno MaisNovo = procura_novo_na_turma(t, qtd_turmas, j);
			printf("%s\n", MaisNovo.nome);
		}

		else if (id == 2)
		{
			int j; scanf("%d", &j);
			Aluno MaisVelho = procura_velho_na_turma(t, qtd_turmas, j);
			printf("%s\n", MaisVelho.sobrenome);
		}

		else if (id == 3)
		{
			Aluno MaisVelho = procura_velho_todas_turmas(t, qtd_turmas);
			printf("%s\n", MaisVelho.nome);
		}

		else if (id == 4)
		{
			Aluno MaisNovo = procura_novo_todas_turmas(t, qtd_turmas);
			printf("%s\n", MaisNovo.sobrenome);
		}

		// TODO: verificar se não dá merda guardar a string sem
		// definir um vetor 
		else if (id == 5)
		{
			// definindo padrao[10] pra garantir que 
			// nao haja overflow (len(padrao) <= 5)
			char padrao[10]; scanf("%s", padrao);
			int count = conta_substrings(t, qtd_turmas, padrao);
			printf("%d\n", count);
		}

		else if (id == 6)
		{
			int j; scanf("%d", &j);
			Aluno NovoAluno = parse_aluno();
			int nova_qtd = add_aluno(t, NovoAluno, j);
			printf("%d\n", nova_qtd);
		}

		else if (id == 7)
		{
			int j; scanf("%d", &j);
			int nova_qtd = remove_aluno(t, j);
			printf("%d\n", nova_qtd);
		}
	}

	return 0;
}