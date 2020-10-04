#include "professor_carlos.h"
#include <stdlib.h> // para permitir usar ponteiros NULL
#include <stdio.h>


// retorna ponteiro pro aluno MAIS NOVO; retorna NULL
// caso ambos tenham nascido no mesmo dia
 
/*
    0: nascimentos iguais
    1: AlunoA é mais novo
    2: AlunoA é mais velho
    
*/

int comparar_datas(Aluno AlunoA, Aluno AlunoB)
{
    Data a = AlunoA.nascimento, b = AlunoB.nascimento;
    if (a.ano > b.ano)
        return 1;

    else if (a.ano < b.ano)
        return 2;

    else if (a.ano == b.ano)
    {
        if (a.mes > b.mes)
            return 1;

        else if (a.mes < b.mes)
            return 2;

        else if (a.mes == b.mes)
        {
            if (a.dia > b.dia)
                return 1;

            else if (a.dia < b.dia)
                return 2;

            else if (a.dia == b.dia)
                return 0;
        }
    }

    return -1;
}

// retorna ponteiro pro aluno com menor nome em ordem 
// lexicográfica, ou menor sobrenome em caso de empate

Aluno comparar_nomes(Aluno AlunoA, Aluno AlunoB)
{
    // printf("comparing: \"%s\" and \"%s\"\n", AlunoA->nmoe, AlunoB->nome);
    // lembrete: é possível dar typecast de char pra int
    for (int i = 0; i < 15 && AlunoA.nome[i] != '\0' && AlunoB.nome[i] != '\0'; i++)
    {
        int LetraA = AlunoA.nome[i], LetraB = AlunoB.nome[i];

        // printf("comparing \"%d\" and \"%d\"\n", LetraA, LetraB);

        if (LetraA == LetraB)
            continue;

        else if (LetraA < LetraB)
            return AlunoA;

        else if (LetraB < LetraA)
            return AlunoB;
    }

    // printf("same name; checking surname...\n");
    // printf("comparing: \"%s\" and \"%s\"\n", AlunoA->sobrenome, AlunoB->sobrenome);

    // continua pros sobrenomes se os nomes forem iguais
    for (int i = 0; i < 15 && AlunoA.sobrenome[i] != '\0' && AlunoB.sobrenome[i] != '\0'; i++)
    {
        int LetraA = AlunoA.sobrenome[i], LetraB = AlunoB.sobrenome[i];


        if (LetraA == LetraB)
            continue;

        else if (LetraA < LetraB)
        {
            // printf("comparing \"%s\" and \"%s\"\nchoice: \"%s\"\n", AlunoA.sobrenome, AlunoB.sobrenome, AlunoA.sobrenome);
            return AlunoA;
        }

        else if (LetraB < LetraA)
        {
            // printf("comparing \"%s\" and \"%s\"\nchoice: \"%s\"\n", AlunoA.sobrenome, AlunoB.sobrenome, AlunoB.sobrenome);
            return AlunoB;
        }
    }

    // printf("names are equal\n");
    // se chegou aqui, os dois nomes completos são iguais
    return AlunoA;
}

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j)
{
    Turma TurmaAtual = t[j];
    Aluno MaisNovo = TurmaAtual.alunos[0];

    for (int i = 0; i < TurmaAtual.qtd; i++)
    {
        if (comparar_datas(MaisNovo, TurmaAtual.alunos[i]) == 0)
        {
            MaisNovo = comparar_nomes(MaisNovo, TurmaAtual.alunos[i]);
            continue;
        }

        if (comparar_datas(MaisNovo, TurmaAtual.alunos[i]) == 2)
            MaisNovo = TurmaAtual.alunos[i];
    }

    return MaisNovo;
}

Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas)
{
    // Turma TurmaAtual;
    Aluno MaisNovo = t[0].alunos[0];   // primeiro aluno da primeira turma

    for (int i = 0; i < qtd_turmas; i++)
    {
        // TurmaAtual = t[i];
        Aluno MaisNovoTurma = procura_novo_na_turma(t, qtd_turmas, i);

        if (comparar_datas(MaisNovo, MaisNovoTurma) == 0)
        {
            // printf("MaisNovo: %s %s; ", MaisNovo.nome, MaisNovo.sobrenome);
            MaisNovo = comparar_nomes(MaisNovo, MaisNovoTurma);
            // printf("Novo MaisNovo: %s %s\n", MaisNovo.nome, MaisNovo.sobrenome);
            continue;
        }

        if (comparar_datas(MaisNovo, MaisNovoTurma) == 2)
            MaisNovo = MaisNovoTurma;
    }

    return MaisNovo;
}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j)
{
    Turma TurmaAtual = t[j];

    Aluno MaisVelho = TurmaAtual.alunos[0];

    for (int i = 0; i < TurmaAtual.qtd; i++)
    {
        if (comparar_datas(MaisVelho, TurmaAtual.alunos[i]) == 0)
        {
            MaisVelho = comparar_nomes(MaisVelho, TurmaAtual.alunos[i]);
            continue;
        }

        if (comparar_datas(MaisVelho, TurmaAtual.alunos[i]) == 1)
            MaisVelho = TurmaAtual.alunos[i];
    }

    return MaisVelho;
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas)
{
    Aluno MaisVelho = t[0].alunos[0];

    for (int i = 0; i < qtd_turmas; i++)
    {
        Aluno MaisVelhoTurma = procura_velho_na_turma(t, qtd_turmas, i);

        if (comparar_datas(MaisVelho, MaisVelhoTurma) == 0)
        {
            MaisVelho = comparar_nomes(MaisVelho, MaisVelhoTurma);
            continue;
        }

        if (comparar_datas(MaisVelho, MaisVelhoTurma) == 1)
            MaisVelho = MaisVelhoTurma;
    }

    return MaisVelho;
}

// assumindo que um caractere '\0' denota o final da string padrao!!!
// retorna 1 caso seja encontrado e 0 caso contrário
int procura_substring(char str[], char *padrao)
{
    int size = 15;

    for (int i = 0; i < size && str[i] != '\0'; i++)
    {
        int flag = 1;
        if (str[i] == *padrao)
        {
            char *it = padrao;

            for (int j = i; j < size && *it != '\0'; j++, it++)
            {                
                if (str[j] != *it) 
                { 
                    flag = 0; break; 
                }
            }

            if (flag)
            {
                //printf("posicao: %d\n", i);
                return 1;
            }
        }
    }

    return 0;
}

int conta_substrings(Turma t[], int qtd_turmas, char *padrao)
{
    int count = 0;
    Turma *pTurma = t;
    for (int i = 0; i < qtd_turmas; i++, pTurma++)
    {
        Aluno *pAluno = pTurma->alunos;
        for (int j = 0; j < pTurma->qtd; j++, pAluno++)
        {
            if (procura_substring(pAluno->nome, padrao))
            {
                //printf("substring \"%s\" encontrada em \"%s\"\n", padrao,pAluno->nome);
                count++;
            }
        }
    }

    return count;
}

int add_aluno(Turma t[], Aluno A, int j)
{
    Turma *pTurma = t+j;
    int size = pTurma->qtd;

    pTurma->alunos[size] = A;
    pTurma->qtd += 1;

    return pTurma->qtd;
}

int remove_aluno(Turma t[], int j)
{
    Turma *pTurma = t+j;
    pTurma->qtd--;

    return pTurma->qtd;
}