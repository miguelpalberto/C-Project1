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

/////GERAL//////

//Lê os dados do ficheiro binário contendo os valores dos contadores (vetorQuant):
void loadVetorQuant(int vetorQuant[])
{

    FILE *ficheiro;
    int erro, i;

    ficheiro = fopen("dadosVetorQuant.dat", "rb");
    if (ficheiro == NULL)
    {
        printf ("\nErro na abertura do ficheiro (dadosVetorQuant.dat) (ou primeira abertura do programa)\n");
    }
    else
    {
        for(i=0; i<MAX_QUANT; i++)
        {
            fread(&vetorQuant[i],sizeof(int),1,ficheiro);
        }

        erro = fclose(ficheiro);
        if (erro != 0)
        {
            printf("\nErro %d no fecho do ficheiro (dadosVetorQuant.dat)\n", erro);
        }
    }
}

//Lê os dados do ficheiro binário contendo a informação dos membros da comunidade:
void loadVetorMembros(tipoMembro vetorMembros[], int vetorQuant[])
{

    FILE *ficheiro;
    int erro, totMembros;
    totMembros = vetorQuant[0];

    ficheiro = fopen("dadosVetorMembros.dat", "rb");
    if (ficheiro == NULL)
    {
        if(vetorQuant[0] != 0)  //Condição adicionada apenas para não aparecer esta mensagem de erro na primeira inicialização do programa (que será também quando o número de membros é igual zero)
        {
            printf ("\nErro na abertura do ficheiro (dadosVetorMembros.dat)\n");
        }
    }
    else
    {

        fread(vetorMembros,sizeof(tipoMembro),totMembros,ficheiro);


        erro = fclose(ficheiro);
        if (erro != 0)
        {
            printf("\nErro %d no fecho do ficheiro (dadosVetorMembros.dat)\n", erro);
        }
    }
}

//Lê os dados do ficheiro binário contendo a informação dos testes de diagnóstico:
tipoTeste *loadVetorTestes(tipoTeste *vetorTestes, int vetorQuant[])
{

    FILE *ficheiro;
    int erro, totTestes;
    totTestes = vetorQuant[2];

    ficheiro = fopen("dadosVetorTestes.dat", "rb");
    if (ficheiro == NULL)
    {
        if(vetorQuant[2] != 0) //Condição adicionada apenas para não aparecer esta mensagem de erro na primeira inicialização do programa (que será também quando o número de testes agendados é igual zero)
        {
            printf ("\nErro na abertura do ficheiro (dadosVetorTestes.dat)\n");
        }
    }
    else
    {
        vetorTestes = realloc(vetorTestes,totTestes*sizeof(tipoTeste));
        if(vetorTestes == NULL && totTestes != 0)
        {
            printf("\nErro ao reservar memoria para vetor dinamico (vetorTestes)\n");
            //vetorQuant[0] = 0;
            //vetorQuant[1] = 0;
            vetorQuant[2] = 0;
            vetorQuant[3] = 0;
            //vetorQuant[4] = 0;
        }
        else
        {
            fread(vetorTestes,sizeof(tipoTeste),totTestes,ficheiro);

            erro = fclose(ficheiro);
            if (erro != 0)
            {
                printf("\nErro %d no fecho do ficheiro (dadosVetorTestes.dat)\n", erro);
            }
        }
    }
    return vetorTestes;
}

//Escreve os dados dos contadores (vetorQuant) no respetivo ficheiro binário:
void gravarVetorQuant(int vetorQuant[])
{

    FILE *ficheiro;
    int erro, i;

    ficheiro = fopen("dadosVetorQuant.dat", "wb");
    if (ficheiro == NULL)
    {
        printf ("\nErro na abertura do ficheiro (dadosVetorQuant.dat)\n");
    }
    else
    {
        for(i=0; i<MAX_QUANT; i++)
        {
            fwrite(&vetorQuant[i],sizeof(int),1,ficheiro);
        }

        erro = fclose(ficheiro);
        if (erro != 0)
        {
            printf("\nErro %d no fecho do ficheiro (dadosVetorQuant.dat)\n", erro);
        }
    }
}

//Escreve os dados dos membros da comunidade (vetorMembros) no respetivo ficheiro binário:
void gravarVetorMembros(tipoMembro vetorMembros[], int vetorQuant[])
{

    FILE *ficheiro;
    int erro, totMembros;
    totMembros = vetorQuant[0];

    ficheiro = fopen("dadosVetorMembros.dat", "wb");
    if (ficheiro == NULL)
    {
        printf ("\nErro na abertura do ficheiro (dadosVetorMembros.dat)\n");
    }
    else
    {

        fwrite(vetorMembros,sizeof(tipoMembro),totMembros,ficheiro);


        erro = fclose(ficheiro);
        if (erro != 0)
        {
            printf("\nErro %d no fecho do ficheiro (dadosVetorMembros.dat)\n", erro);
        }
    }
}

//Escreve os dados dos testes de diagnóstico (vetorTestes) no respetivo ficheiro binário:
void gravarVetorTestes(tipoTeste vetorTestes[], int vetorQuant[])
{

    FILE *ficheiro;
    int erro, totTestes;
    totTestes = vetorQuant[2];

    ficheiro = fopen("dadosVetorTestes.dat", "wb");
    if (ficheiro == NULL)
    {
        printf ("\nErro na abertura do ficheiro (dadosVetorTestes.dat)\n");
    }
    else
    {

        fwrite(vetorTestes,sizeof(tipoTeste),totTestes,ficheiro);


        erro = fclose(ficheiro);
        if (erro != 0)
        {
            printf("\nErro %d no fecho do ficheiro (dadosVetorTestes.dat)\n", erro);
        }
    }
}

//Escreve(acrescenta) no log, os novos registos dos resultados dos testes:
void gravarLogTestesTxt(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[], int posicao)
{

    int numeroUtente, posicaoMembro, erro;
    FILE *ficheiro;

    numeroUtente = vetorTestes[posicao].nUtente;

    posicaoMembro = procuraMembro(vetorMembros, vetorQuant, numeroUtente);

    ficheiro = fopen("logTestes.txt", "a");
    if (ficheiro == NULL)
    {
        printf ("\nErro na abertura do ficheiro (logTestes.txt)\n");
    }
    else
    {
        fprintf(ficheiro,"\n%d\t",vetorMembros[posicaoMembro].id);
        fprintf(ficheiro,"%d\t",vetorMembros[posicaoMembro].nUtente);
        fputs(vetorMembros[posicaoMembro].nome, ficheiro);
        fprintf(ficheiro,"\t\t\t%d dose(s)",vetorMembros[posicaoMembro].estadoVacina);
        fprintf(ficheiro,"\t\tresultado %c",vetorTestes[posicao].resultado);
        fprintf(ficheiro, "\t\t%dh", vetorTestes[posicao].horaColheita.hora);
        fprintf(ficheiro, "%dm", vetorTestes[posicao].horaColheita.mins);
        fprintf(ficheiro, "\t\t%dm", vetorTestes[posicao].duracao);

        erro=fclose(ficheiro);
        if (erro != 0)
        {
            printf("\nErro %d no fecho do ficheiro (logTestes.txt)\n", erro);
        }
    }
}



/////CONFINAMENTOS//////

//Escreve(acrescenta) no log de confinamentos, os novos registos de casos de confinamento:
void gravarLogConfinamentos(tipoConf conf)
{
    FILE *ficheiro;
    int erro;

    ficheiro = fopen("logConfinamentos.dat", "ab");
    if (ficheiro == NULL)
    {
        printf ("\nErro na abertura do ficheiro (logConfinamentos.dat)\n");
    }
    else
    {
        fwrite(&conf, sizeof(tipoConf),1,ficheiro);

        erro=fclose(ficheiro);
        if (erro != 0)
        {
            printf("\nErro %d no fecho do ficheiro (logConfinamentos.dat)\n", erro);
        }

    }
}

//Lê o log de confinamentos, contendo os registos de casos de confinamento:
tipoConf *lerLogConfinamentos(tipoConf *vetorConf, int vetorQuant[])
{
    FILE *ficheiro;
    int erro, totConfs;
    totConfs = vetorQuant[4];

    ficheiro = fopen("logConfinamentos.dat", "rb");
    if (ficheiro == NULL)
    {
        printf ("\nErro na abertura do ficheiro (logConfinamentos.dat)\n");
    }
    else
    {

        fread(vetorConf,sizeof(tipoConf),totConfs,ficheiro);

        erro = fclose(ficheiro);
        if (erro != 0)
        {
            printf("\nErro %d no fecho do ficheiro (logConfinamentos.dat)\n", erro);
        }
    }
    return vetorConf;
}

/*
//Escreve, em ficheiro de texto, o log de confinamentos, contendo os registos de casos de confinamento (usado apenas para monitorização):
void gravarLogConfinamentosTxt(tipoConf conf) //facultativo - apenas para monitorizacao
{

    FILE *ficheiro;
    //int erro;

    ficheiro = fopen("logConfinamentos.txt", "a");
    // if (ficheiro == NULL)
    //   {
    //       printf ("\nErro na abertura do ficheiro (logConfinamentos.txt)\n");
    //   }
    //   else
    //   {

    fprintf(ficheiro, "\n%d", conf.id);
    fprintf(ficheiro, "\t%d\t", conf.nUtente);
    fputs(conf.nome, ficheiro);
    fprintf(ficheiro, "\t\t\t%c", conf.estadoConfinamento);
    fprintf(ficheiro, "\t%d", conf.dataConf.ano);
    fprintf(ficheiro, "-%d", conf.dataConf.mes);
    fprintf(ficheiro, "-%d", conf.dataConf.dia);
    fprintf(ficheiro, "\t%d dias", conf.duracaoConf);

    //        erro = fclose(ficheiro);
    //        if (erro != 0)
    //        {
    //            printf("\nErro %d no fecho do ficheiro (logConfinamentos.txt)\n", erro);
    //        }
    //    }
}
*/
