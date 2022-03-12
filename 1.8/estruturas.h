#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

#define MAX_MEMBROS 200
#define MAX_QUANT 5
#define MAX_NOME 80
#define ANO_MIN 2020
#define ANO_MAX 2023
#define NU_MIN 100000000
#define NU_MAX 999999999

//Estruturas:
typedef struct
{
    int dia;
    int mes;
    int ano;
} tipoData;

typedef struct
{
    int hora;
    int mins;
} tipoHora;

typedef struct
{
    int id;
    int nUtente;
    char nome[MAX_NOME];
    char tipo;
    int anoNascimento;
    int estadoVacina;
    tipoData ultimaVacina;
    char estadoConfinamento;
    int quantRealizados;
} tipoMembro;

typedef struct
{
    int id;
    char tipo;
    tipoData data;
    int nUtente;
    char resultado;
    tipoHora horaColheita;
    int duracao;
} tipoTeste;

typedef struct
{
    int id;
    int nUtente;
    char nome[MAX_NOME];
    char estadoConfinamento;
    tipoData dataConf;
    int duracaoConf;
} tipoConf;

#endif // ESTRUTURAS_H_INCLUDED
