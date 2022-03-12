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

//Apresenta o menu principal:
char menuPrincipal(int vetorQuant[])
{
    char op;

    limparEcra();
    printf("\n\t\t************\tMENU PRINCIPAL \t ************\n\n");
    printf("\t  Membros:\t%3d\t\tTestes Agendados :\t%d\n", vetorQuant[0], vetorQuant[2]);
    printf("Membros Vacinados:\t%3d\t\tTestes Realizados:\t%d\n\n\n", vetorQuant[1], vetorQuant[3]);
    printf("\tSelecione uma opcao:\n");
    printf("\n\t M - Membros");
    printf("\n\t T - Testes");
    printf("\n\t V - Vacinacoes");
    printf("\n\t C - Confinamentos");
    //printf("\n");
    printf("\n\t E - Estatisticas");
    printf("\n");
    printf("\n\t L - Ler/Carregar dados");
    printf("\n\t G - Gravar dados");
    printf("\n\t S - Sair");
    //printf("\n\n\t\t************\t\t\t ************");
    printf("\n\n\t Opcao (M,T,V,C,E,L,G,S) --> ");

    op = getchar();
    op = toupper(op);
    limpaBufferStdin();

    return op;
}

//Apresenta o menu dos membros:
char opcaoMembros()
{
    char opcao;
    char r = 'R';
    char d = 'D';
    char l = 'L';
    char v = 'V';

    printf("\n\n\t\t-----------\tMEMBROS DA COMUNIDADE\t -----------\n");
    printf("\n\t R - Registar Novo Membro");
    printf("\n\t D - Ver Dados de Um Membro");
    printf("\n\t L - Listar Membros");
    printf("\n\t V - Voltar ao Menu Principal");
    printf("\n\n\t Opcao --> ");

    opcao = lerCaracter4(r,d,l,v);
    return opcao;
}

//Apresenta o menu dos testes:
char opcaoTestes()
{
    char opcao;
    char n = 'N';
    char a = 'A';
    char r = 'R';
    char d = 'D';
    char l = 'L';
    char v = 'V';

    printf("\n\n\t\t-----------\tTESTES DE DIAGNOSTICO\t -----------\n");
    printf("\n\t N - Novo Agendamento");
    printf("\n\t A - Alterar Data de Agendamento");
    printf("\n\t R - Registar Resultado");
    printf("\n\t D - Ver Dados de Um Teste");
    printf("\n\t L - Listar Dados de Todos os Testes Realizados");
    printf("\n\t V - Voltar ao Menu Principal");
    printf("\n\n\t Opcao --> ");

    opcao = lerCaracter6(n,a,r,d,l,v);
    return opcao;
}

//Apresenta o menu das vacinações:
char opcaoVacinacoes()
{
    char opcao;
    char a = 'A';
    char v = 'V';

    printf("\n\n\t\t-----------\tVACINACOES\t -----------\n");
    printf("\n\t A - Atualizar/Registar Estado de Vacinacao de Membro");
    printf("\n\t V - Voltar ao Menu Principal");
    printf("\n\n\t Opcao --> ");

    opcao = lerCaracter2(a,v);
    return opcao;
}

//Apresenta o menu dos confinamentos:
char opcaoConfinamentos()
{
    char opcao;
    char a = 'A';
    char l = 'L';
    char v = 'V';

    printf("\n\n\t\t-----------\tCONFINAMENTOS\t -----------\n");
    printf("\n\t A - Atualizar/Registar Estado de Confinamento de Membro");
    printf("\n\t L - Listar Casos de Confinamento");
    printf("\n\t V - Voltar ao Menu Principal");
    printf("\n\n\t Opcao --> ");

    opcao = lerCaracter3(a,l,v);
    return opcao;
}

//Apresenta o menu das estatísticas:
char opcaoEstatisticas()
{
    char opcao;
    char e = 'E';
    char m = 'M';
    char t = 'T';
    char v = 'V';

    printf("\n\n\t\t-----------\tESTATISTICAS\t -----------\n");
    printf("\n\t E - Estatisticas Gerais");
    printf("\n\t M - Membros com Menor Quantidade de Testes Realizados");
    printf("\n\t T - Testes Realizados Mais Recentes");
    printf("\n\t V - Voltar ao Menu Principal");
    printf("\n\n\t Opcao --> ");

    opcao = lerCaracter4(e,m,t,v);
    return opcao;
}

//Apresenta o submenu para registar resultado de teste: (facultativo)
char opcaoSubRegistar(){
    char opcao;
    char u = 'U';
    char i = 'I';
    char v = 'V';

    printf("\n\n\t\t-- REGISTAR RESULTADO DE TESTE --\n");
    printf("\n\t\t U - Atraves do Numero de Utente do Membro");
    printf("\n\t\t I - Atraves do ID do Teste");
    printf("\n\t\t V - Voltar ao Menu Principal");
    printf("\n\n\t\t Opcao --> ");

    opcao = lerCaracter3(u,i,v);
    return opcao;
}
