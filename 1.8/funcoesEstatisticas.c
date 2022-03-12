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

//Vê quantos membros têm pelo menos uma dose de vacinação:
int contarVacinados(tipoMembro vetorMembros[], int vetorQuant[])
{

    int i, totMembros;
    int totVacinados;
    totVacinados = 0;
    totMembros = vetorQuant[0];

    for (i=0; i<totMembros; i++)
    {
        if (vetorMembros[i].estadoVacina == 1 || vetorMembros[i].estadoVacina == 2 || vetorMembros[i].estadoVacina == 3)
        {
            totVacinados++;
        }
        else {}
    }
    return totVacinados;
}

//Apresenta as estatisticas:
void estatisticasGerais(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[])
{

    int somaEst, somaDoc, somaTec, somaDuracao, somaInc, i, quantMembros, quantAgendados, quantRealizados;
    float mediaDuracao, percInc;
    somaEst = 0;
    somaDoc = 0;
    somaTec = 0;
    somaDuracao = 0;
    quantMembros = vetorQuant[0];
    quantAgendados = vetorQuant[2];
    quantRealizados = vetorQuant[3];

    //Ver Quantidade cada tipo de membro
    for (i=0; i<quantMembros; i++)
    {
        if(vetorMembros[i].tipo == 'E')
        {
            somaEst++;
        }
        else
        {
            if(vetorMembros[i].tipo == 'D')
            {
                somaDoc++;
            }
            else
            {
                if(vetorMembros[i].tipo == 'T')
                {
                    somaTec++;
                }
            }
        }
    }

    //Ver tempo medio de duracao e percentagem de Inconclusivos
    if (quantRealizados != 0)
    {
        for (i=0; i<quantAgendados; i++)
        {
            if(vetorTestes[i].resultado == 'P' || vetorTestes[i].resultado == 'N' || vetorTestes[i].resultado == 'I')
            {
                somaDuracao = somaDuracao + vetorTestes[i].duracao;
                if(vetorTestes[i].resultado == 'I')
                {
                    somaInc++;
                }
            }
        }
        mediaDuracao = (float) somaDuracao/quantRealizados;
        percInc = (float) somaInc/quantRealizados*100;
    }



    printf("\n\n-- ESTATISTICAS GERAIS --\n\n");
    printf("\n\t Quantidades de cada Tipo de Membro:");
    printf("\n\t Estudantes: %d \t Docentes: %d \t Tecnicos: %d\n", somaEst, somaDoc, somaTec);////////

    printf("\n\t Tempo Medio de Duracao de cada Teste Realizado:");
    if(quantRealizados == 0)
    {
        printf("\n\t (sem testes realizados)\n");
    }
    else
    {
        printf("\n\t %.2f\n", mediaDuracao);
    }
    printf("\n\t Percentagem de Testes Inconclusivos:");
    if(quantRealizados == 0)
    {
        printf("\n\t (sem testes realizados)\n\n");
    }
    else
    {
        printf("\n\t %.2f\n\n", percInc);
    }

}

//Lista os membros com menos testes com resultado registado:
void membrosMenosTestes(tipoMembro vetorMembros[], int vetorQuant[])
{

    int i, valor;


    printf("\n\n-- MEMBROS COM MENOR QUANTIDADE DE TESTES REALIZADOS --\n\n");

    if(vetorQuant[0]==0)
    {
        printf("\n\tNao existem membros registados!\n");

    }
    else
    {
        if(vetorQuant[2]==0)
        {
            printf("\n\tNao existem testes agendados!\n");

        }
        if(vetorQuant[3]==0)
        {
            printf("\n\tNao existem testes com resultado registado!\n");

        }
        if(vetorQuant[2]==0 || vetorQuant[3]==0)
        {
            printf("\n\tPelo que os respetivos membros com menos testes sao:\n");

        }
        //ver valor menor:
        valor = vetorMembros[0].quantRealizados;

            for(i=1; i<(vetorQuant[0]); i++)
            {
                if(vetorMembros[i].quantRealizados < valor) //&& (vetorMembros[i].tipo == 'E' || vetorMembros[i].tipo == 'D' || vetorMembros[i].tipo == 'T'
                {
                    valor = vetorMembros[i].quantRealizados;

                }
            }


        //mostrar membros com esse valor:
        printf("\n\tID\tN.Utente\tQuant.Testes\tNome\n");
        for(i=0; i<(vetorQuant[0]); i++)
        {
            if(vetorMembros[i].quantRealizados == valor) //&& (vetorMembros[i].tipo == 'E' || vetorMembros[i].tipo == 'D' || vetorMembros[i].tipo == 'T')
            {
                printf("\t%d\t%d\t%d\t\t", vetorMembros[i].id, vetorMembros[i].nUtente, vetorMembros[i].quantRealizados);
                fputs(vetorMembros[i].nome, stdout);
                printf("\n");
            }
        }
        printf("\n\nLista Concluida.");


    }
}

//Lista os testes com a data mais recente:
void testesRecentes(tipoTeste vetorTestes[], int vetorQuant[])
{
    int i, j, k, ano, mes, dia;

    printf("\n\n-- TESTES REALIZADOS MAIS RECENTES --\n\n");

    if(vetorQuant[2]==0)
    {
        printf("\n\tNao existem testes agendados!\n");

    }
    else
    {
        if(vetorQuant[3]==0)
        {
            printf("\n\tNao existem testes com resultado registado!\n");

        }
        else
        {
            //Ver data mais recente com teste(s):
            //ano mais recente:
            ano = vetorTestes[0].data.ano;
            mes = vetorTestes[0].data.mes;
            dia = vetorTestes[0].data.dia;

                for(i=1; i<(vetorQuant[2]); i++)
                {
                    if(vetorTestes[i].data.ano > ano && (vetorTestes[i].resultado == 'P' || vetorTestes[i].resultado == 'I' || vetorTestes[i].resultado == 'N'))
                    {
                        ano = vetorTestes[i].data.ano;
                        mes = vetorTestes[i].data.mes;
                        dia = vetorTestes[i].data.dia;
                    }

                }

            //mes mais recente desse ano:
            for(j=i; j<(vetorQuant[2]); j++)
            {
                    if(vetorTestes[j].data.mes > mes && vetorTestes[j].data.ano == ano && (vetorTestes[i].resultado == 'P' || vetorTestes[i].resultado == 'I' || vetorTestes[i].resultado == 'N'))
                    {
                        mes = vetorTestes[j].data.mes;
                        dia = vetorTestes[j].data.dia;
                    }

            }
            //dia mais recente desse mes desse ano:
            for(k=j; k<(vetorQuant[2]); k++)
            {

                    if(vetorTestes[k].data.dia > dia && vetorTestes[k].data.mes == mes && vetorTestes[k].data.ano == ano && (vetorTestes[i].resultado == 'P' || vetorTestes[i].resultado == 'I' || vetorTestes[i].resultado == 'N'))
                    {
                        dia = vetorTestes[k].data.dia;
                    }

            }

            //Ver teste(s) dessa data:
            printf("\nID\tTipo\t\tData\t\tResultado\tHora_Colh.\tDuracao\t\tN.Utente\n");

            for (i=0; i<(vetorQuant[2]); i++)
            {

                    if(vetorTestes[i].data.ano == ano && vetorTestes[i].data.mes == mes && vetorTestes[i].data.dia == dia && (vetorTestes[i].resultado == 'P' || vetorTestes[i].resultado == 'I' || vetorTestes[i].resultado == 'N'))
                    {

                        printRealizado(vetorTestes, i);
                        printf("\t\t%d", vetorTestes[i].nUtente);
                        /*
                        printf("%d\t\t%d\t\t", vetorTestes[i].id, vetorTestes[i].nUtente);

                        printf("\t%d-%d-%d\t", vetorTestes[i].data.ano, vetorTestes[i].data.mes, vetorTestes[i].data.dia);

                        printf("\t\t%dh%dm\t\t%dm\n", vetorTestes[i].horaColheita.hora, vetorTestes[i].horaColheita.mins, vetorTestes[i].duracao);
                    */
                    }

            }
            printf("\n\nLista Concluida.");
        }
    }
}
