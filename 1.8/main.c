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

//n.Membros == vetorQuant[0]
//n.Vacinados == vetorQuant[1]
//n.T.Agendados == vetorQuant[2]
//n.T.Registados Res. == vetorQuant[3]
//n.T.Confinamentos == vetorQuant[4]

//////////////
////Main:////
int main()
{
    int vetorQuant[MAX_QUANT] = {0};
    tipoMembro vetorMembros[MAX_MEMBROS] = {0};
    tipoTeste *vetorTestes;
    char op, opcaoM, opcaoT, opcaoV, opcaoC, opcaoE, opcaoSubR;
    vetorTestes = NULL;
    //
    vetorQuant[0] = 0;  //operação repetida apenas por segurança (caso vetorQuant[MAX_QUANT] = {0} não funcione em macOS)
    vetorQuant[1] = 0;  //operação repetida apenas por segurança (caso vetorQuant[MAX_QUANT] = {0} não funcione em macOS)
    vetorQuant[2] = 0;  //operação repetida apenas por segurança (caso vetorQuant[MAX_QUANT] = {0} não funcione em macOS)
    vetorQuant[3] = 0;  //operação repetida apenas por segurança (caso vetorQuant[MAX_QUANT] = {0} não funcione em macOS)
    vetorQuant[4] = 0;  //operação repetida apenas por segurança (caso vetorQuant[MAX_QUANT] = {0} não funcione em macOS)
    //

    loadVetorQuant(vetorQuant);
    loadVetorMembros(vetorMembros, vetorQuant);
    vetorTestes = loadVetorTestes(vetorTestes, vetorQuant);

    do
    {
        op = menuPrincipal(vetorQuant);

        switch (op)
        {
        case 'M':
            opcaoM = opcaoMembros();

            switch (opcaoM)
            {
            case 'R':
                vetorMembros[vetorQuant[0]] = registarMembro(vetorMembros, vetorQuant);
                gravarVetorMembros(vetorMembros, vetorQuant);
                gravarVetorQuant(vetorQuant);
                voltarMenu();
                break;
            case 'D':
                verDadosMembro(vetorMembros, vetorTestes, vetorQuant);
                voltarMenu();
                break;
            case 'L':
                listarMembros(vetorMembros, vetorTestes, vetorQuant);
                voltarMenu();
                break;
            case 'V':
                break;
            }
            break;

        case 'T':
            opcaoT = opcaoTestes();

            switch (opcaoT)
            {
            case 'N':
                vetorTestes = agendarTeste(vetorMembros, vetorTestes, vetorQuant);
                voltarMenu();
                break;
            case 'A':
                alterarAgendamento(vetorMembros, vetorTestes, vetorQuant);
                voltarMenu();
                break;
            case 'R':
                opcaoSubR = opcaoSubRegistar();
                switch (opcaoSubR)
                {
                case 'U':
                    registarResultado(vetorMembros, vetorTestes, vetorQuant);
                    voltarMenu();
                    break;
                case 'I':
                    registarResultadoId(vetorMembros, vetorTestes, vetorQuant);
                    voltarMenu();
                    break;
                }
                break;
            case 'D':
                listarUmTeste(vetorMembros, vetorTestes, vetorQuant);
                voltarMenu();
                break;
            case 'L':
                listarTestesRealizados(vetorTestes, vetorQuant);
                break;
            case 'V':
                break;
            }
            break;

        case 'V':
            opcaoV = opcaoVacinacoes();

            switch (opcaoV)
            {
            case 'A':
                vacinarMembro(vetorMembros, vetorQuant);
                break;
            case 'V':
                break;
            }
            break;

        case 'C':
            opcaoC = opcaoConfinamentos();

            switch (opcaoC)
            {
            case 'A':
                confinarMembro(vetorMembros, vetorQuant);
                voltarMenu();
                break;
            case 'L':
                listarConfinamentos(vetorQuant);
                voltarMenu();
                break;
            case 'V':
                break;
            }
            break;

        case 'E':
            opcaoE = opcaoEstatisticas();

            switch (opcaoE)
            {
            case 'E':
                estatisticasGerais(vetorMembros, vetorTestes, vetorQuant);
                voltarMenu();
                break;
            case 'M':
                membrosMenosTestes(vetorMembros, vetorQuant);
                voltarMenu();
                break;
            case 'T':
                testesRecentes(vetorTestes, vetorQuant);
                voltarMenu();
                break;
            case 'V':
                break;
            }
            break;

        case 'L':
            loadVetorQuant(vetorQuant);
            loadVetorMembros(vetorMembros, vetorQuant);
            vetorTestes = loadVetorTestes(vetorTestes, vetorQuant);
            break;

        case 'G':
            gravarVetorTestes(vetorTestes, vetorQuant);
            gravarVetorMembros(vetorMembros, vetorQuant);
            gravarVetorQuant(vetorQuant);
            break;

        case 'S':
            limparEcra();
            break;
        }

    }
    while(op != 'S');

    free(vetorTestes);
    return 0;
}
////Fim Main////
///////////////









