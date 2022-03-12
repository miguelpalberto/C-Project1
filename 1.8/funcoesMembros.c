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

//Regista um novo membro da comunidade:
tipoMembro registarMembro(tipoMembro vetorMembros[], int vetorQuant[])
{

    tipoMembro membro;
    int pos, numeroInserido, totMembros;

    totMembros = vetorQuant[0];
    char e = 'E';
    char d = 'D';
    char t = 'T';
    //char n = 'N';
    //char q = 'Q';
    //char i = 'I';

    limparEcra();
    printf("\n\n-- REGISTAR NOVO MEMBRO --\n\n");

    if (totMembros == MAX_MEMBROS)
    {
        printf("\nImpossivel acrescentar novos elementos\n");
    }
    else
    {

        printf("Numero de Utente: ");
        numeroInserido = lerInteiro(NU_MIN,NU_MAX);

        pos=procuraMembro(vetorMembros, vetorQuant, numeroInserido);
        if (pos != -1)
        {
            printf("\nEsse membro ja existe! - Nao sera acrescentado. \n");
        }
        else
        {
            membro.id = totMembros;
            membro.nUtente = numeroInserido;
            printf("Nome: ");
            lerString(membro.nome, MAX_NOME);
            printf("Tipo (E-Estudante D-Docente T-Tecnico): ");
            membro.tipo = lerCaracter3(e, d, t);
            printf("Ano de nascimento: ");
            membro.anoNascimento = lerInteiro(1900,2022);
            /*printf("Estado vacinacao (0-Sem vacina 1-Uma dose 2-Duas doses 3-Tres doses): ");
            membro.estadoVacina = lerInteiro(0,3);
            if (membro.estadoVacina != 0)
            {
                vetorQuant[1]++;
                printf("Data da ultima vacina tomada: ");
                membro.ultimaVacina = lerData(ANO_MIN,ANO_MAX);
            }
            else{
                membro.ultimaVacina.ano = 0;
                membro.ultimaVacina.mes = 0;
                membro.ultimaVacina.dia = 0;
            }
            printf("Estado de confinamento (N-Nao confinado Q-Em quarentena I-Em isolamento profilatico): ");
            membro.estadoConfinamento = lerCaracter3(n, q, i);*/
            membro.estadoVacina = 0;
            membro.ultimaVacina.ano = 0;
            membro.ultimaVacina.mes = 0;
            membro.ultimaVacina.dia = 0;
            membro.estadoConfinamento = 'N';
            //------
            membro.quantRealizados = 0;
            vetorQuant[0]++;

            printf("\nMembro registado!");
        }
    }

    return membro;
}

//Coloca dados do membro introduzido simplesmente para revisao por parte do utilizador:
void reverMembro(tipoMembro vetorMembros[], int id)
{
    printf("\n\nDADOS MEMBRO:\n");
    printf("\nID\tN.Utente\tTipo_Membro\tAno_Nascim.\tEstado_Vac.\tData_Ult.Vac.\tEstado.Conf.\t\tNome\n");

    printMembro(vetorMembros, id);

    printf("\n\n");
}

//Função usada para apresentar os dados de um membro específico:
void verDadosMembro(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[])
{
    int numeroInserido, id;

    printf("\n\n-- VER DADOS DE MEMBRO --\n\n");

    if (vetorQuant[0] == 0)
    {
        printf("\nNao existem membros!\n");
    }
    else
    {
        printf("Introduza o numero de Utente do Membro:\n");
        numeroInserido = lerInteiro(NU_MIN,NU_MAX);

        id = procuraMembro (vetorMembros, vetorQuant, numeroInserido);
        if (id == -1)
        {
            printf("Membro nao encontrado! (Membro nao esta registado)\n");
        }
        else
        {
            listarUmMembro(vetorMembros, vetorTestes, vetorQuant, id);
            printf("\n");
        }
    }
}

//Lista os dados de um membro (e respetivos testes):
void listarUmMembro(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[], int id)
{
    int totTestesAgendados, numeroInserido;
    numeroInserido = vetorMembros[id].nUtente;
    totTestesAgendados = quantidadeTestesAgendados(vetorTestes, vetorQuant, numeroInserido);

    printf("\nDados Membro %d:", vetorMembros[id].id);
    printf("\nID\tN.Utente\tTipo_Membro\tAno_Nascim.\tEstado_Vac.\tData_Ult.Vac.\tEstado_Conf.\t\tNome");

    printMembro(vetorMembros, id);
    printf("\n");

    if(totTestesAgendados != 0)
    {
        int totTestesRealizados, pos;
        totTestesRealizados = quantidadeTestesRealizados(vetorTestes, vetorQuant, numeroInserido);

        //printf("\n");
        printf("\nTestes Membro %d:\n", vetorMembros[id].id);

        if(totTestesRealizados != 0)    //se tiver alguns testes realizados
        {
            printf("ID\tTipo_Teste\tData\t\tResultado\tHora_Colh.\tDuracao");

            for (pos=0; pos<vetorQuant[2]; pos++)
            {   //mostrar testes com resultado:
                if(vetorTestes[pos].nUtente == numeroInserido && (vetorTestes[pos].resultado == 'P' || vetorTestes[pos].resultado == 'I' || vetorTestes[pos].resultado == 'N'))
                {
                printRealizado(vetorTestes, pos);
                }
                else{   //mostrar testes sem resultado que tambem possa ter (para nao aparecerem valores a zero):
                        if(vetorTestes[pos].nUtente == numeroInserido && (vetorTestes[pos].resultado != 'P' || vetorTestes[pos].resultado != 'I' || vetorTestes[pos].resultado != 'N'))
                {
                printAgendado(vetorTestes, pos);
                }

                }
            }
            printf("\n(%d agendado(s) e deste(s) %d realizado(s))\n", totTestesAgendados, totTestesRealizados);
        }
        else    //se so tiver testes agendados, sem resultado:
        {
            printf("ID\tTipo_Teste\tData");

            for (pos=0; pos<vetorQuant[2]; pos++)
            {
                if(vetorTestes[pos].nUtente == numeroInserido)
                {
                printAgendado(vetorTestes, pos);
                }
            }
            printf("\n(%d agendado(s) e deste(s) %d realizados)\n", totTestesAgendados, totTestesRealizados); //realizados sera 0
        }
    }
    else
    {
        printf("\nTestes Membro %d:\n(sem testes agendados)\n", vetorMembros[id].id);
    }
}

//Recebe o Numero de Utente de Membro e devolve o respetivo ID:
int procuraMembro (tipoMembro vetorMembros[], int vetorQuant[], int numeroInserido)
{
    int i, pos;
    int totMembros;
    totMembros = vetorQuant[0];        /* posicao dos dados do membro a procurar */
    pos = -1;

    for (i=0; i<totMembros; i++)
    {
        if (vetorMembros[i].nUtente == numeroInserido) 	/* Encontrado */
        {
            pos = i;	/* guarda posição de numero*/
            i = totMembros;	/* para concluir pesquisa (sair do for) */
        }
    }
    return pos;
}

//Função usada para listar todos os membros da comunidade (e respetivos testes):
void listarMembros(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[])
{

    int id;

    printf("\n\n-- LISTAR MEMBROS --\n\n");

    if (vetorQuant[0] == 0)
    {
        printf("\nNao existem membros!\n");
    }
    else
    {
        for(id = 0; id<vetorQuant[0]; id++)
        {
            listarUmMembro(vetorMembros, vetorTestes, vetorQuant, id);
            printf("_______________________________________");
        }

        /*
        printf("\nID\tN.Utente\tNome\t\tTipo_Membro\tAno_Nascim.\tEstado_Vac.\tData_Ult.Vac.\tEstado.Conf.\n");

        for (id=0; id<vetorQuant[0]; id++)
        {
        printf("%d\t%d\t", vetorMembros[id].id, vetorMembros[id].nUtente);
        fputs(vetorMembros[id].nome, stdout);
        printf("\t\t%c\t\t%d\t\t%d dose(s)\t%d-%d-%d\t%c\n", vetorMembros[id].tipo, vetorMembros[id].anoNascimento, vetorMembros[id].estadoVacina, vetorMembros[id].ultimaVacina.ano, vetorMembros[id].ultimaVacina.mes, vetorMembros[id].ultimaVacina.dia, vetorMembros[id].estadoConfinamento);
        */
        printf("\n\nLista Concluida.");
    }
}

