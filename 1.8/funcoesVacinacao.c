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

//Atualiza o estado de vacinação de membro:
void vacinarMembro(tipoMembro vetorMembros[], int vetorQuant[])
{

    int numeroInserido, id, previaDose, posDose, ignora;
    ignora = 1;
    char escolha = 'X';
    char a = 'A';
    char v = 'V';

    printf("\n\n-- ATUALIZAR ESTADO DE VACINACAO DE MEMBRO --\n\n");

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
            printf("Membro nao encontrado!\n");
        }
        else
        {
            printf("\nIntroduza:\n");
            printf("Estado vacinacao (0-Sem vacina 1-Uma dose 2-Duas doses 3-Tres doses): \n");

            previaDose = vetorMembros[id].estadoVacina;
            posDose = lerInteiro(0,3);

            if(posDose<=previaDose)
            {
                ignora = -1;
                printf("\nMembro ja tem %d dose(s)!\n", previaDose);
                printf("Insira 'A' se pretender atualizar estado e/ou data de vacina de qualquer das formas.\n");
                printf("Insira 'V' para voltar ao menu.\n");
                escolha = lerCaracter2(a,v);
            }
            if(escolha == a || ignora == 1)
            {
                vetorMembros[id].estadoVacina = posDose;

                if(vetorMembros[id].estadoVacina == 1 || vetorMembros[id].estadoVacina == 2 || vetorMembros[id].estadoVacina == 3)
                {
                    printf("Data da vacinacao: ");
                    vetorMembros[id].ultimaVacina = lerData(ANO_MIN,ANO_MAX);
                }
                else
                {
                    vetorMembros[id].ultimaVacina.ano = 0;
                    vetorMembros[id].ultimaVacina.mes = 0;
                    vetorMembros[id].ultimaVacina.dia = 0;
                }
                vetorQuant[1] = contarVacinados(vetorMembros, vetorQuant);  //conta de novo para o caso do utilizador ter mudado o estado de vacinacao para 0 por motivos de correcao de dados
                gravarVetorMembros(vetorMembros, vetorQuant);
                gravarVetorQuant(vetorQuant);
                printf("\nEstado de vacinacao atualizado.");
                reverMembro(vetorMembros, id);
                voltarMenu();
            }

        }
    }
}

