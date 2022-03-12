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

//Agenda um novo teste para um membro (é pedido o seu Numero de Utente):
tipoTeste *agendarTeste(tipoMembro vetorMembros[], tipoTeste *vetorTestes, int vetorQuant[])
{

    tipoTeste teste, *paux;
    int pos, numeroInserido, totTestes, ver;

    paux = vetorTestes;
    totTestes = vetorQuant[2];
    char a = 'A';
    char p = 'P';
    ver = 0;

    limparEcra();

    printf("\n\n-- AGENDAR NOVO TESTE --\n\n");
    teste.id = totTestes;

    printf("Numero de Utente do Membro a testar: ");
    numeroInserido = lerInteiro(NU_MIN,NU_MAX);
    pos = procuraMembro (vetorMembros, vetorQuant, numeroInserido);
    if(pos == -1)
    {
        printf("\nEsse membro nao esta registado! \n");
    }
    else
    {
        teste.nUtente = numeroInserido;

        printf("Tipo de teste a agendar (A-Antigeneo P-PCR): ");
        teste.tipo = lerCaracter2(a,p);


        printf("Data de Agendamento: ");
        teste.data = lerData(ANO_MIN,ANO_MAX);


        ver = verTesteRepetido(vetorTestes, vetorQuant, teste);
        if(ver != -1)
        {
            printf("\nMembro inserido ja tem um teste do mesmo tipo agendado para a mesma data\n");
        }
        else
        {
            int maxquinze;
            tipoData dataInserida;

            dataInserida.ano = teste.data.ano;
            dataInserida.mes = teste.data.mes;
            dataInserida.dia = teste.data.dia;
            maxquinze = procuraTestesDia(vetorTestes, vetorQuant, dataInserida);  //15 PCR max

            if (teste.tipo == 'P' && maxquinze >= 15)
            {
                printf("\nImpossivel agendar novos testes PCR para este dia (maximo 15)!\n");
            }
            else
            {
                vetorTestes = realloc(vetorTestes,(totTestes+1)*sizeof(tipoTeste));
                if(vetorTestes == NULL)
                {
                    printf("Erro ao aumentar vetor");
                    vetorTestes = paux;
                }
                else
                {

                    vetorTestes[totTestes].id = teste.id;
                    vetorTestes[totTestes].tipo = teste.tipo;
                    vetorTestes[totTestes].nUtente = teste.nUtente;
                    vetorTestes[totTestes].data.ano = teste.data.ano;
                    vetorTestes[totTestes].data.mes = teste.data.mes;
                    vetorTestes[totTestes].data.dia = teste.data.dia;
                    vetorTestes[totTestes].resultado = 0;
                    vetorTestes[totTestes].horaColheita.hora = 0;
                    vetorTestes[totTestes].horaColheita.mins = 0;
                    vetorTestes[totTestes].duracao = 0;

                    vetorQuant[2]++;

                    gravarVetorTestes(vetorTestes, vetorQuant);
                    gravarVetorQuant(vetorQuant);

                    printf("\nAgendamento concluido!\n");
                }
            }
        }
    }
    return vetorTestes;
}

//Altera a data de agendamento de um teste já agendado:
void alterarAgendamento(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[])
{
    int i, numeroInserido, totTestes, soma, maxquinze;
    tipoTeste teste;
    tipoData dataInserida;
    int pos = 0;
    char a = 'A';
    char p = 'P';
    totTestes = vetorQuant[2];
    soma = 0;

    printf("\n\n-- ALTERAR DATA DE AGENDAMENTO --\n\n");

    if(vetorQuant[2] == 0)
    {
        printf("Nao existem testes agendados para poderem ser alterados! \n");
    }
    else
    {

        printf("O teste a re-agendar corresponde a que Membro?\n");
        printf("Insira o respetivo Numero de Utente: ");
        numeroInserido = lerInteiro(NU_MIN,NU_MAX);

        pos = procuraMembro (vetorMembros, vetorQuant, numeroInserido);
        if(pos == -1)
        {
            printf("\nEsse membro nao esta registado! \n");
        }
        else
        {

            teste.nUtente = numeroInserido;

            for (i=0; i<totTestes; i++)
            {
                if (vetorTestes[i].nUtente == teste.nUtente)
                {
                    printf("\n\tEncontrado teste agendado a %d-%d-%d (teste tipo %c);", vetorTestes[i].data.ano, vetorTestes[i].data.mes, vetorTestes[i].data.dia, vetorTestes[i].tipo);
                    pos = i;
                    soma++;
                }
                else {}
            }
            if (soma == 0)  //Se nao houver testes agendados para o membro introduzido:
            {
                printf("\nEsse membro nao tem testes agendados!\n");
            }
            else
            {

                if (soma == 1)  //Se so houver 1 teste agendado para o membro introduzido (escolher esse teste automaticamente):
                {

                    teste.tipo = vetorTestes[pos].tipo;

                    printf("\n\nInsira a NOVA data para o teste: ");
                    teste.data = lerData(ANO_MIN,ANO_MAX);

                    dataInserida.ano = teste.data.ano;
                    dataInserida.mes = teste.data.mes;
                    dataInserida.dia = teste.data.dia;
                    maxquinze = procuraTestesDia(vetorTestes, vetorQuant, dataInserida);  //15 PCR max

                    if (teste.tipo == 'P' && maxquinze >= 15)
                    {
                        printf("\nImpossivel agendar novos testes PCR para este dia (maximo 15)!\n");
                    }
                    else
                    {

                        vetorTestes[pos].data.ano = teste.data.ano;
                        vetorTestes[pos].data.mes = teste.data.mes;
                        vetorTestes[pos].data.dia = teste.data.dia;

                        gravarVetorTestes(vetorTestes, vetorQuant);

                        printf("\nAgendamento alterado com sucesso!\n");
                    }
                }
                else        //Se houver mais que 1 teste agendado para o membro introduzido:
                {

                    printf("\n\nInsira a data ORIGINAL do teste a re-agendar: ");
                    teste.data = lerData(ANO_MIN,ANO_MAX);
                    soma = 0;

                    for (i=0; i<totTestes; i++)
                    {
                        if (vetorTestes[i].nUtente == teste.nUtente && vetorTestes[i].data.ano == teste.data.ano && vetorTestes[i].data.mes == teste.data.mes && vetorTestes[i].data.dia == teste.data.dia)
                        {
                            soma++;
                        }
                        else {}
                    }
                    if (soma == 0)
                    {
                        printf("\nEsse membro nao tem testes agendados para essa data!\n");
                    }
                    else
                    {
                        printf("\nConfirme o tipo de teste do teste a re-agendar (A-Antigeneo ou P-PCR): ");
                        teste.tipo = lerCaracter2(a,p);
                        pos = verTesteRepetido(vetorTestes, vetorQuant, teste);
                        if(pos == -1)
                        {
                            printf("\n\nMembro inserido nao tem um teste desse tipo agendado para essa data!\n");
                        }
                        else
                        {
                            printf("\nInsira a NOVA data para o teste: ");
                            teste.data = lerData(ANO_MIN,ANO_MAX);

                            dataInserida.ano = teste.data.ano;
                            dataInserida.mes = teste.data.mes;
                            dataInserida.dia = teste.data.dia;
                            maxquinze = procuraTestesDia(vetorTestes, vetorQuant, dataInserida);  //15 PCR max

                            if (teste.tipo == 'P' && maxquinze >= 15)
                            {
                                printf("\nImpossivel agendar novos testes PCR para este dia (maximo 15)!\n");
                            }
                            else
                            {
                                vetorTestes[pos].data.ano = teste.data.ano;
                                vetorTestes[pos].data.mes = teste.data.mes;
                                vetorTestes[pos].data.dia = teste.data.dia;

                                gravarVetorTestes(vetorTestes, vetorQuant);

                                printf("\nAgendamento alterado com sucesso!\n");
                            }
                        }
                    }
                }
            }
        }
    }
}

//Regista o resultado de um teste (a partir do Numero de Utente do Membro):
void registarResultado(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[])
{
    int i, posM, pos, numeroInserido, totTestes, soma;
    char positivo = 'P';
    char negativo = 'N';
    char inc = 'I';
    char a = 'A';
    char p = 'P';
    tipoTeste teste;
    totTestes = vetorQuant[2];
    soma = 0;

    printf("\n\n-- REGISTAR RESULTADO DE TESTE --\n\n");

    if(vetorQuant[2] == 0)
    {
        printf("Nao existem testes agendados! \n");
    }
    else
    {

        printf("O resultado a registar corresponde a que Membro?\n");
        printf("Insira o respetivo Numero de Utente: ");
        numeroInserido = lerInteiro(NU_MIN,NU_MAX);

        posM = procuraMembro (vetorMembros, vetorQuant, numeroInserido);
        if(posM == -1)
        {
            printf("\nEsse membro nao esta registado! \n");
        }
        else
        {
            teste.nUtente = numeroInserido;

            for (i=0; i<totTestes; i++)
            {
                if (vetorTestes[i].nUtente == teste.nUtente)
                {
                    printf("\n\tEncontrado teste agendado a %d-%d-%d (teste tipo %c); ", vetorTestes[i].data.ano, vetorTestes[i].data.mes, vetorTestes[i].data.dia, vetorTestes[i].tipo);
                    pos = i;
                    soma++;
                }
                else {}
            }
            if (soma == 0)  //Se nao houver testes agendados para o membro introduzido:
            {
                printf("\nEsse membro nao tem testes agendados!\n");
            }
            else
            {

                if (soma == 1)  //Se so houver 1 teste agendado para o membro introduzido (escolher esse teste automaticamente):
                {

                    if (vetorTestes[pos].resultado == 'P' || vetorTestes[pos].resultado == 'N' || vetorTestes[pos].resultado == 'I')
                    {
                        printf("\n\n\tEste teste ja tem o respetivo resultado registado!\n");
                    }
                    else
                    {

                        printf("\n\nInsira o resultado do teste (P-Positivo N-Negativo I-Inconclusivo): ");
                        teste.resultado = lerCaracter3(positivo,negativo,inc);
                        printf("Insira a hora da respetiva colheita: ");
                        teste.horaColheita = lerHora(0,23);
                        printf("Insira a duracao (em minutos) da respetiva colheita: ");
                        teste.duracao = lerInteiro(0,90);
                        printf("\nResultado registado!\n");

                        vetorTestes[pos].resultado = teste.resultado;
                        vetorTestes[pos].horaColheita.hora = teste.horaColheita.hora;
                        vetorTestes[pos].horaColheita.mins = teste.horaColheita.mins;
                        vetorTestes[pos].duracao = teste.duracao;

                        vetorQuant[3]++;
                        vetorMembros[posM].quantRealizados++;

                        gravarVetorTestes(vetorTestes, vetorQuant);
                        gravarVetorQuant(vetorQuant);
                        gravarVetorMembros(vetorMembros, vetorQuant);
                        gravarLogTestesTxt(vetorMembros, vetorTestes, vetorQuant, pos);

                        vetorTestes = autoAgendamento(vetorTestes, vetorQuant, pos);
                        autoConfinamento(vetorMembros, vetorTestes, vetorQuant, pos);

                    }
                }
                else        //Se houver mais que 1 teste agendado para o membro introduzido:
                {

                    printf("\n\nInsira a data ORIGINAL do teste a re-agendar: ");
                    teste.data = lerData(ANO_MIN,ANO_MAX);
                    soma = 0;

                    for (i=0; i<totTestes; i++)
                    {
                        if (vetorTestes[i].nUtente == teste.nUtente && vetorTestes[i].data.ano == teste.data.ano && vetorTestes[i].data.mes == teste.data.mes && vetorTestes[i].data.dia == teste.data.dia)
                        {
                            soma++;
                        }
                        else {}
                    }
                    if (soma == 0)
                    {
                        printf("\nEsse membro nao tem testes agendados para essa data!\n");
                    }
                    else
                    {
                        printf("\nConfirme o tipo de teste a registar o resultado (A-Antigeneo ou P-PCR): ");
                        teste.tipo = lerCaracter2(a,p);
                        pos = verTesteRepetido(vetorTestes, vetorQuant, teste);/////////////
                        if(pos == -1)
                        {
                            printf("\nMembro inserido nao tem um teste desse tipo agendado para essa data!\n");
                        }
                        else
                        {
                            if (vetorTestes[pos].resultado == 'P' || vetorTestes[pos].resultado == 'N' || vetorTestes[pos].resultado == 'I')
                            {
                                printf("\nEste teste ja tem o respetivo resultado registado!\n");
                            }
                            else
                            {

                                printf("\n\nInsira o resultado do teste (P-Positivo N-Negativo I-Inconclusivo): ");
                                teste.resultado = lerCaracter3(positivo,negativo,inc);
                                printf("Insira a hora da respetiva colheita: ");
                                teste.horaColheita = lerHora(0,23);
                                printf("Insira a duracao (em minutos) da respetiva colheita: ");
                                teste.duracao = lerInteiro(0,90);
                                printf("\nResultado registado!\n");

                                vetorTestes[pos].resultado = teste.resultado;
                                vetorTestes[pos].horaColheita.hora = teste.horaColheita.hora;
                                vetorTestes[pos].horaColheita.mins = teste.horaColheita.mins;
                                vetorTestes[pos].duracao = teste.duracao;

                                vetorQuant[3]++;
                                vetorMembros[posM].quantRealizados++;

                                gravarVetorTestes(vetorTestes, vetorQuant);
                                gravarVetorQuant(vetorQuant);
                                gravarVetorMembros(vetorMembros, vetorQuant);
                                gravarLogTestesTxt(vetorMembros, vetorTestes, vetorQuant, pos);

                                vetorTestes = autoAgendamento(vetorTestes, vetorQuant, pos);
                                autoConfinamento(vetorMembros, vetorTestes, vetorQuant, pos);

                            }
                        }
                    }
                }
            }
        }
    }
}


//Pede para agendar novo teste PCR caso o resultado registado seja inconclusivo ou, seja positivo a partir de teste antigeneo
tipoTeste *autoAgendamento(tipoTeste *vetorTestes, int vetorQuant[], int posicao)
{
        tipoTeste teste, *paux;
        int totTestes = vetorQuant[2];
        int maxquinze, ver;
        tipoData dataInserida;
        paux = vetorTestes;

    if(vetorTestes[posicao].resultado == 'I' || (vetorTestes[posicao].resultado == 'P' && vetorTestes[posicao].tipo == 'A'))
    {


        printf("\n\nUm teste com resultado Inconclusivo (ou Positivo se for de um teste Antigeneo) obriga a um novo agendamento de teste PCR\n");

        teste.id = totTestes;
        teste.nUtente = vetorTestes[posicao].nUtente;
        teste.tipo = 'P';

        do
        {
            printf("Insira uma data para o agendamento referido: ");
            teste.data = lerData(ANO_MIN,ANO_MAX);

            dataInserida.ano = teste.data.ano;
            dataInserida.mes = teste.data.mes;
            dataInserida.dia = teste.data.dia;
            maxquinze = procuraTestesDia(vetorTestes, vetorQuant, dataInserida);  //15 PCR max

            if(maxquinze >= 15)
            {
                printf("\nImpossivel agendar novos testes PCR para este dia (maximo 15)!\n");
            }
        }
        while(maxquinze >= 15);

        ver = verTesteRepetido(vetorTestes, vetorQuant, teste);
        if(ver != -1)
        {
            printf("\nMembro inserido ja tem um teste PCR agendado para a mesma data, pelo que podera utiliza-lo como novo agendamento obrigatorio\n");
            printf("Assim, nenhum novo agendamento obrigatorio sera registado\n");
        }
        else
        {
            vetorTestes = realloc(vetorTestes,(totTestes+1)*sizeof(tipoTeste));
                if(vetorTestes == NULL)
                {
                    printf("Erro ao aumentar vetor");
                    vetorTestes = paux;
                }
                else
                {

            vetorTestes[totTestes].id = teste.id;
            vetorTestes[totTestes].tipo = teste.tipo;
            vetorTestes[totTestes].nUtente = teste.nUtente;
            vetorTestes[totTestes].data.ano = teste.data.ano;
            vetorTestes[totTestes].data.mes = teste.data.mes;
            vetorTestes[totTestes].data.dia = teste.data.dia;
            vetorTestes[totTestes].resultado = 0;
            vetorTestes[totTestes].horaColheita.hora = 0;
            vetorTestes[totTestes].horaColheita.mins = 0;
            vetorTestes[totTestes].duracao = 0;

            vetorQuant[2]++;

            gravarVetorTestes(vetorTestes, vetorQuant);
            gravarVetorQuant(vetorQuant);

            printf("\nAgendamento registado!\n");
                }
        }
    }
    return vetorTestes;
}

//Regista o resultado de um teste (a partir do ID do teste):
void registarResultadoId(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[])
{
    int posM, pos, idMax, nUtente;
    char positivo = 'P';
    char negativo = 'N';
    char inc = 'I';
    tipoTeste teste;
    idMax = vetorQuant[2]-1;

    printf("\n\n-- REGISTAR RESULTADO DE TESTE --\n\n");

    if(vetorQuant[2] == 0)
    {
        printf("Nao existem testes agendados! \n");
    }
    else
    {
        printf("Insira o ID do teste a registar resultado (0 a %d): ", idMax);
        pos = lerInteiro(0,idMax);

        /*pos = procuraTeste(vetorTestes, vetorQuant, numeroInserido);
        if(pos == -1)
        {
            printf("\nTeste nao encontrado! \n");
        }
        else
        {*/
        if (vetorTestes[pos].resultado == 'P' || vetorTestes[pos].resultado == 'N' || vetorTestes[pos].resultado == 'I')
        {
            printf("\nEste teste ja tem o respetivo resultado registado!\n");
        }
        else
        {
            nUtente = vetorTestes[pos].nUtente;

            printf("\n\nInsira o resultado do teste (P-Positivo N-Negativo I-Inconclusivo): ");
            teste.resultado = lerCaracter3(positivo,negativo,inc);
            printf("Insira a hora da respetiva colheita: ");
            teste.horaColheita = lerHora(0,23);
            printf("Insira a duracao (em minutos) da respetiva colheita: ");
            teste.duracao = lerInteiro(0,90);
            printf("\nResultado registado!\n");

            vetorTestes[pos].resultado = teste.resultado;
            vetorTestes[pos].horaColheita.hora = teste.horaColheita.hora;
            vetorTestes[pos].horaColheita.mins = teste.horaColheita.mins;
            vetorTestes[pos].duracao = teste.duracao;

            vetorQuant[3]++;
            posM = procuraMembro(vetorMembros, vetorQuant, nUtente);
            vetorMembros[posM].quantRealizados++;

            gravarVetorTestes(vetorTestes, vetorQuant);
            gravarVetorQuant(vetorQuant);
            gravarVetorMembros(vetorMembros, vetorQuant);
            gravarLogTestesTxt(vetorMembros, vetorTestes, vetorQuant, pos);

            vetorTestes = autoAgendamento(vetorTestes, vetorQuant, pos);
            autoConfinamento(vetorMembros, vetorTestes, vetorQuant, pos);

            //}
        }
    }
}




//Lista todos os testes com resultado registado (com opção para listar testes agendados sem resultado). Se não houver testes com resultado registado, lista testes agendados sem resultado (avisando previamente o utilizador):
void listarTestesRealizados(tipoTeste *vetorTestes, int vetorQuant[])
{

    int pos;
    char caracter;
    char a = 'A';
    char v = 'V';

    printf("\n\n-- TESTES REALIZADOS E REGISTADOS --\n\n");

    if (vetorQuant[2] == 0)
    {
        printf("\nNao existem testes agendados ou registados!\n");
        voltarMenu();
    }
    else
    {
        if (vetorQuant[3] == 0)
        {
            printf("\nTodos os testes agendados ainda tem o respetivo resultado por registar. Estes sao:\n");
            listarTestesNaoRealizados(vetorTestes, vetorQuant);
        }
        else
        {
            printf("Testes agendados com resultado registado:\n");
            printf("\nID\tTipo_Teste\tData\t\tResultado\tHora_Colh.\tDuracao\t\tN.Utente");

            for (pos=0; pos<vetorQuant[2]; pos++)
            {
                if(vetorTestes[pos].resultado == 'P' || vetorTestes[pos].resultado == 'N' || vetorTestes[pos].resultado == 'I')
                {
                    printRealizado(vetorTestes, pos); //printf("%d\t\t%d\t\t%c\t%d-%d-%d\t%c\t\t%dh%dm\t\t%dm\n", vetorTestes[pos].id, vetorTestes[pos].nUtente, vetorTestes[pos].tipo, vetorTestes[pos].data.ano, vetorTestes[pos].data.mes, vetorTestes[pos].data.dia, vetorTestes[pos].resultado, vetorTestes[pos].horaColheita.hora, vetorTestes[pos].horaColheita.mins, vetorTestes[pos].duracao);
                    printf("\t\t%d", vetorTestes[pos].nUtente);
                }
            }

            printf("\n\nLista Concluida.");
            printf("\nSe pretender listar tambem os testes agendados ainda sem resultado insira 'A';\nSe pretender voltar ao menu insira 'V': \n");


            caracter = lerCaracter2(a,v);

            if(caracter == 'A')
            {
                printf("\nTestes agendados sem resultado registado:\n");
                listarTestesNaoRealizados(vetorTestes, vetorQuant);
            }
        }
    }
}

//Função para listar testes agendados sem resultado (facultativo):
void listarTestesNaoRealizados(tipoTeste *vetorTestes, int vetorQuant[])
{

    int pos;

    //printf("\nTestes agendados sem resultado registado:\n");
    printf("\nID\tTipo_Teste\tData\t\tN.Utente");

    for (pos=0; pos<vetorQuant[2]; pos++)
    {
        if(vetorTestes[pos].resultado != 'P' && vetorTestes[pos].resultado != 'N' && vetorTestes[pos].resultado != 'I')
        {
            printAgendado(vetorTestes, pos); //printf("%d\t\t%d\t\t%c\t%d-%d-%d\n", vetorTestes[pos].id, vetorTestes[pos].nUtente, vetorTestes[pos].tipo, vetorTestes[pos].data.ano, vetorTestes[pos].data.mes, vetorTestes[pos].data.dia);
            printf("\t%d", vetorTestes[pos].nUtente);
        }
    }

    printf("\n\nLista Concluida.");

    voltarMenu();

}

//Lista um teste agendado e/ou com resultado registado, pedindo ao utilizador o respetivo ID do teste (tal informação pode ser acedida pelo utilizador ao listar os testes ou ao listar os membros):
void listarUmTeste(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[])
{
    int id, idm;
    int idMax = vetorQuant[2]-1;
    int totTestesPositivos;
    int nUtente;

    printf("\n\n-- INFORMACAO DE TESTE DE DIAGNOSTICO --\n\n");

    if (vetorQuant[2] == 0)
    {
        printf("\nNao existem testes agendados ou registados!\n");
    }
    else
    {
        printf("Insira o ID do TESTE pretendido (0 a %d): ", idMax);

        id = lerInteiro(0,idMax);

        nUtente = vetorTestes[id].nUtente;
        totTestesPositivos = quantidadeTestesPositivos(vetorTestes, vetorQuant, nUtente);
        idm = procuraMembro(vetorMembros, vetorQuant, nUtente);

        //Se teste selecionado ja tenha sido realizado:
        if(vetorTestes[id].resultado == 'P' || vetorTestes[id].resultado == 'N' || vetorTestes[id].resultado == 'I')
        {
            printf("\nDados Teste:");
            printf("\nID\tTipo_Teste\tData\t\tResultado\tHora_Colh.\tDuracao");
            printRealizado(vetorTestes, id);

        }
        //Se teste selecionado tenha sido agendado mas ainda nao realizado:
        else
        {
            printf("\n(O resultado do teste selecionado ainda nao foi registado.) \n");
            printf("\nDados Teste:");
            printf("\nID\tTipo_Teste\tData");
            printAgendado(vetorTestes, id);

        }

        printf("\n\nDados Respetivo Membro:");
        printf("\nN.Utente\tTipo_Membro\tQuant.Testes_Positivos\tNome_Membro\n");
        printf("%d\t", vetorMembros[idm].nUtente);
        printPalavra(vetorMembros[idm].tipo);
        printf("\t%d\t\t\t",totTestesPositivos);
        fputs(vetorMembros[idm].nome, stdout);
        printf("\n");

    }
}

//Ve quantos testes PCR estao agendados para data introduzida:
int procuraTestesDia(tipoTeste vetorTestes[], int vetorQuant[], tipoData dataInserida)
{
    int i;
    int soma;
    int totTestes;
    soma = 0;
    totTestes = vetorQuant[2];

    for (i=0; i<totTestes; i++)
    {
        if (vetorTestes[i].tipo == 'P' && vetorTestes[i].data.ano == dataInserida.ano && vetorTestes[i].data.mes == dataInserida.mes && vetorTestes[i].data.dia == dataInserida.dia)
        {
            soma++;
        }
    }
    return soma;
}
//Confirma se não existe já um teste igual agendado:
int verTesteRepetido(tipoTeste vetorTestes[], int vetorQuant[], tipoTeste teste)
{
    int i, pos;
    int totTestes;
    totTestes = vetorQuant[2];
    pos = -1;

    for (i=0; i<totTestes; i++)
    {
        if (vetorTestes[i].data.ano == teste.data.ano && vetorTestes[i].data.mes == teste.data.mes && vetorTestes[i].data.dia == teste.data.dia && vetorTestes[i].tipo == teste.tipo && vetorTestes[i].nUtente == teste.nUtente)
        {
            pos = i;
            i = totTestes;
        }
        else {}
    }
    return pos;
}
/*
int verTesteUnico(tipoTeste vetorTestes[], int vetorQuant[], tipoTeste teste)
{
    int i, pos;
    int totTestes;
    totTestes = vetorQuant[2];
    pos = -1;

    for (i=0; i<totTestes; i++)
    {
        if (vetorTestes[i].nUtente == teste.nUtente)
        {
            pos = i;
            i = totTestes;
        }
        else {}
    }
    return pos;
}
*/

//Recebe o Numero de Utente de um Membro e devolve a quantidade total de testes que agendou:
int quantidadeTestesAgendados(tipoTeste vetorTestes[], int vetorQuant[], int nUtente)
{

    int pos;
    int soma = 0;

    for (pos = 0; pos<vetorQuant[2]; pos++)
    {
        if(vetorTestes[pos].nUtente == nUtente)
        {
            soma++;
        }
    }
    return soma;
}

//Recebe o Numero de Utente de um Membro e devolve a quantidade de testes que agendou e realizou (facultativa, uma vez que cada membro já tem este "contador" na sua estrutura):
int quantidadeTestesRealizados(tipoTeste vetorTestes[], int vetorQuant[], int nUtente)
{
    int pos;
    int soma = 0;

    for (pos = 0; pos<vetorQuant[2]; pos++)
    {
        if(vetorTestes[pos].nUtente == nUtente && (vetorTestes[pos].resultado == 'P' || vetorTestes[pos].resultado == 'I'))
        {
            soma++;
        }
    }
    return soma;
}

//Recebe o Numero de Utente de um membro e devolve a quantidade de testes que esse membro teve com resultado positivo:
int quantidadeTestesPositivos(tipoTeste vetorTestes[], int vetorQuant[], int nUtente)
{

    int pos;
    int soma = 0;

    for (pos = 0; pos<vetorQuant[2]; pos++)
    {
        if(vetorTestes[pos].nUtente == nUtente && vetorTestes[pos].resultado == 'P')
        {
            soma++;
        }
    }
    return soma;
}








