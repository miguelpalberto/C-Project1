#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "menus.h"
#include "estruturas.h"
#include "funcoesApoio.h"
#include "funcoesFicheiros.h"
#include "funcoesMembros.h"
#include "funcoesPrint.h"
#include "funcoesTestes.h"
#include "funcoesVacinacao.h"
#include "funcoesConfinamentos.h"
#include "funcoesEstatisticas.h"

//Funcoes Standard:


void lerString(char vetor[], int max)
{
    int tamanhoString;
    do   /* Repete leitura se introduzida string apenas com o \n*/
    {
        fgets(vetor, max, stdin);
        tamanhoString = strlen(vetor);

        if(tamanhoString == 1)
        {
            printf("Insira caracteres: \n");
        }
    }
    while (tamanhoString == 1);
    if (vetor[tamanhoString-1] != '\n')
    {
        limpaBufferStdin(); /* limpa dados do buffer stdin */
    }
    else
    {
        vetor[tamanhoString-1] ='\0'; /* substitui por \0 o caracter \n da string armazenada */
    }
}

void limpaBufferStdin(void)
{
    char lixo;
    do
    {
        lixo = getchar();
    }
    while (lixo!='\n' && lixo!=EOF);
}

int lerInteiro(int min, int max)
{
    int numero, controlo;
    do 	/* Repete leitura enquanto valor introduzido nao for numerico e nao estiver no intervalo desejado (min -> max)*/
    {
        controlo = scanf("%d", &numero); /* scanf devolve quantidade de valores validos obtidos*/
        limpaBufferStdin();   /* limpa dados do buffer stdin */

        if (controlo == 0)
        {
            printf("Insira um numero inteiro (%d a %d): \n", min, max);
        }
        else
        {
            if(numero<min || numero>max)
            {
                printf("Valor introduzido invalido. Insira novamente (%d a %d): \n", min, max);
            }
        }
    }
    while (numero<min || numero>max || controlo==0);
    return numero;
}

float lerFloat(int min, int max)
{
    float numero;
    int controlo;
    do  // Repete leitura enquanto valor introduzido não for numérico e não estiver no intervalo desejado (min -> max)
    {
        controlo = scanf("%f", &numero); // scanf devolve quantidade de valores válidos obtidos
        limpaBufferStdin(); // limpa dados do buffer stdin
        if (controlo == 0)
        {
            printf("Insira um numero decimal (float)(%d a %d): \n", min, max);
        }
        else
        {
            if(numero<min || numero>max)
            {
                printf("Valor introduzido invalido. Insira novamente (%d a %d): \n", min, max);
            }
        }
    }
    while (numero<min || numero>max || controlo==0);
    return numero;
}

char lerCaracter2(char a, char b)
{
    char caracter;
    do
    {
        caracter = getchar();
        caracter = toupper(caracter);
        limpaBufferStdin();

        if(caracter!=a && caracter!=b)
        {
            printf("Caracter introduzido invalido. Insira novamente: \n");
        }
    }
    while (caracter!=a && caracter!=b);
    return caracter;
}

char lerCaracter3(char a, char b, char c)
{
    char caracter;
    do
    {
        caracter = getchar();
        caracter = toupper(caracter);
        limpaBufferStdin();

        if(caracter!=a && caracter!=b && caracter!=c)
        {
            printf("Caracter introduzido invalido. Insira novamente: \n");
        }
    }
    while (caracter!=a && caracter!=b && caracter!=c);
    return caracter;
}

char lerCaracter4(char a, char b, char c, char d)
{
    char caracter;
    do
    {
        caracter = getchar();
        caracter = toupper(caracter);
        limpaBufferStdin();

        if(caracter!=a && caracter!=b && caracter!=c && caracter!=d)
        {
            printf("Caracter introduzido invalido. Insira novamente: \n");
        }
    }
    while (caracter!=a && caracter!=b && caracter!=c && caracter!=d);
    return caracter;
}

char lerCaracter6(char a, char b, char c, char d, char e, char f)
{
    char caracter;
    do
    {
        caracter = getchar();
        caracter = toupper(caracter);
        limpaBufferStdin();

        if(caracter!=a && caracter!=b && caracter!=c && caracter!=d && caracter!=e && caracter!=f)
        {
            printf("Caracter introduzido invalido. Insira novamente: \n");
        }
    }
    while (caracter!=a && caracter!=b && caracter!=c && caracter!=d && caracter!=e && caracter!=f);
    return caracter;
}

tipoData lerData(int min, int max)
{
    tipoData data;
    int maxDiaMes;

    printf("\nAno (%d a %d): ",min,max);
    data.ano = lerInteiro(min,max);

    printf("Mes (%d a %d): ",1,12);
    data.mes = lerInteiro(1,12);

    switch (data.mes)
    {
    case 2:
        if((data.ano%400==0) || (data.ano%4==0 && data.ano%100!=0))
        {
            maxDiaMes = 29;    /* Ano bissexto */
        }
        else
        {
            maxDiaMes = 28;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        maxDiaMes = 30;
        break;
    default:
        maxDiaMes = 31;
    }
    printf("Dia (%d a %d): ",1,maxDiaMes);
    data.dia = lerInteiro(1,maxDiaMes);

    return data;
}

tipoHora lerHora(int min, int max)
{
    tipoHora horaTotal;

    printf("\n\tHora (%d a %d): ",min,max);
    horaTotal.hora = lerInteiro(min,max);

    printf("\tMinutos: ");
    horaTotal.mins = lerInteiro(0,59);
    printf("\n");

    return horaTotal;
}

//Função simples, apenas para adicionar algum espaçamento entre textos, no ecrã:
void limparEcra(void)
{
    for (int i = 0; i < 5; i++)
    {
        printf("\n");
    }
}
//Função para pedir caracter 'V' ao utilizador para continuar
void voltarMenu(void)
{
    char caracter;
    printf("\n");
    do
    {
        printf("Insira 'V' para voltar.\n");
        caracter = getchar();
        caracter = toupper(caracter);
        limpaBufferStdin();

    }
    while (caracter != 'V');
}
