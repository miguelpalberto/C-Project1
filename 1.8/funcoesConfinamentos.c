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

//Regista um novo confinamento (Quarentena ou Isolamento Profilático):
void confinarMembro(tipoMembro vetorMembros[], int vetorQuant[])
{
    int numeroInserido, id;
    char n = 'N';
    char q = 'Q';
    char i = 'I';
    tipoConf conf;

    printf("\n\n-- ATUALIZAR CASO DE CONFINAMENTO DE MEMBRO --\n\n");

    if (vetorQuant[0] == 0)
    {
        printf("\nNao existem membros!\n");
    }
    else
    {
        printf("Introduza o numero de utente do membro:\n");
        numeroInserido = lerInteiro(NU_MIN,NU_MAX);

        id = procuraMembro (vetorMembros, vetorQuant, numeroInserido);
        if (id == -1)
        {
            printf("Membro nao encontrado!\n");
        }
        else
        {
            conf.id = vetorQuant[4];
            conf.nUtente = vetorMembros[id].nUtente;
            strncpy(conf.nome, vetorMembros[id].nome, MAX_NOME);
            printf("\nIntroduza:\n");
            printf("Novo estado de confinamento (N-Nao Confinado Q-Em Quarentena I-Em Isolamento Profilatico): \n");
            vetorMembros[id].estadoConfinamento = lerCaracter3(n, q, i);
            conf.estadoConfinamento = vetorMembros[id].estadoConfinamento;
            if(conf.estadoConfinamento == 'Q' || conf.estadoConfinamento == 'I')
            {
                printf("Data de confinamento: ");
                conf.dataConf = lerData(ANO_MIN,ANO_MAX);
                printf("Duracao de confinamento (em dias): ");
                conf.duracaoConf = lerInteiro(1,90);

                vetorQuant[4]++;
                gravarLogConfinamentos(conf);
                //gravarLogConfinamentosTxt(conf);//facultativo - apenas para monitorizacao
                gravarVetorQuant(vetorQuant);
                printf("\nConfinamento registado!");
            }
            else
            {

                printf("\nAlteracao registada!");
            }

            gravarVetorMembros(vetorMembros, vetorQuant);
        }
    }
}

//Lista todos os casos de confinamento ocorridos:
void listarConfinamentos(int vetorQuant[])
{
    int i;
    tipoConf *vetorConf;
    vetorConf = NULL;
    int totConfs = vetorQuant[4];

    printf("\n\n-- LISTAR CASOS DE CONFINAMENTO --\n\n");

    if(vetorQuant[4] == 0)
    {
        printf("\nSem confinamentos registados!\n");
    }
    else
    {
        vetorConf = realloc(vetorConf,(totConfs)*sizeof(tipoConf));
        if(vetorConf == NULL)
        {
            printf("\nErro ao criar o vetorConf\n");
            vetorQuant[4]=0;
        }
        else
        {
            printf("ID\tN.Utente\tTipo_Conf.\t\tData_Conf.\tDuracao_Conf.\tNome_Membro\n");

            vetorConf = lerLogConfinamentos(vetorConf, vetorQuant);

            for(i=0; i<totConfs; i++)
            {
                printf("\n");
                printf("%d", vetorConf[i].id);
                printf("\t%9d\t", vetorConf[i].nUtente);
                printPalavra(vetorConf[i].estadoConfinamento);
                printf("\t%d", vetorConf[i].dataConf.ano);
                printf("-%d", vetorConf[i].dataConf.mes);
                printf("-%d", vetorConf[i].dataConf.dia);
                printf("\t%d\t\t", vetorConf[i].duracaoConf);
                fputs(vetorConf[i].nome, stdout);
            }

            printf("\n\nLista Concluida.");
        }
        free(vetorConf);
    }
}

//Atualiza "automaticamente" o estado de confinamento de um membro depois de um resultado de um teste comprometedor:
void autoConfinamento(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[], int pos)
{
    int id, nUtente;
    tipoConf conf;
    nUtente = vetorTestes[pos].nUtente;

    if(vetorTestes[pos].resultado == 'P' || vetorTestes[pos].resultado == 'I')
    {
        id = procuraMembro (vetorMembros, vetorQuant, nUtente);

        if(vetorTestes[pos].resultado == 'P')
        {
            vetorMembros[id].estadoConfinamento = 'I';
            printf("\nUm teste com resultado Positivo resulta em Confinamento automatico (Isolamento Profilatico) a partir da data de registo do resultado");
        }
        else              //if(vetorTestes[pos].resultado == 'I')
        {
            vetorMembros[id].estadoConfinamento = 'Q';
            printf("\nUm teste com resultado Inconclusivo resulta em Confinamento automatico (Quarentena) a partir da data de registo do resultado");
        }

        conf.id = vetorMembros[id].id;
        conf.nUtente = vetorMembros[id].nUtente;
        strncpy(conf.nome, vetorMembros[id].nome, MAX_NOME);
        conf.estadoConfinamento = vetorMembros[id].estadoConfinamento;
        conf.dataConf = vetorTestes[pos].data;

        printf("\nInsira apenas a duracao de confinamento (em dias): ");
        conf.duracaoConf = lerInteiro(1,90);

        vetorQuant[4]++;
        gravarVetorMembros(vetorMembros, vetorQuant);
        gravarLogConfinamentos(conf);
        //gravarLogConfinamentosTxt(conf);//facultativo - apenas para monitorizacao
        gravarVetorQuant(vetorQuant);
        printf("\nConfinamento registado!");

    }
}

