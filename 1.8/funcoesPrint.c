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


//Função para imprimir no ecrã o significado do respetivo caracter de entrada (para Tipo de Membro, para Estado de Confinamento, e para Tipo de Teste):
void printPalavra(char caracter){
    switch (caracter){
    case 'E':
        printf("Estudante");
    break;
    case 'D':
        printf("Docente  ");
    break;
    case 'T':
        printf("Tecnico  ");
    break;
    case 'N':
        printf("Nao Confinado     ");
    break;
    case 'Q':
        printf("Quarentena        ");
    break;
    case 'I':
        printf("Isolamento Profil.");
    break;
    case 'P':
        printf("PCR      ");
    break;
    case 'A':
        printf("Antigeneo");
    break;

    default:
        printf("0\t");

    }
}

//Função para imprimir no ecrã o significado do respetivo caracter de entrada (para Resultado do Teste):
void printPalavraR(char caracter){
    switch (caracter){
    case 'P':
        printf("Positivo    ");
    break;
    case 'N':
        printf("Negativo    ");
    break;
    case 'I':
        printf("Inconclusivo");
    break;

    default:
        printf("0\t");

    }
}

//Função para imprimir no ecrã os dados de um membro da comunidade:
void printMembro(tipoMembro vetorMembros[], int id){

    printf("\n");
    printf("%d\t%d\t", vetorMembros[id].id, vetorMembros[id].nUtente);
    //fputs(vetorMembros[id].nome, stdout);
    //printf("\t\t");
    printPalavra(vetorMembros[id].tipo);
    printf("\t%d\t\t%d dose(s)\t", vetorMembros[id].anoNascimento, vetorMembros[id].estadoVacina);
    if (vetorMembros[id].estadoVacina == 0){
    printf("        \t");
    }
    else{
    printf("%d-%d-%d\t", vetorMembros[id].ultimaVacina.ano, vetorMembros[id].ultimaVacina.mes, vetorMembros[id].ultimaVacina.dia);
    }
    printPalavra(vetorMembros[id].estadoConfinamento);
    printf("\t");
    fputs(vetorMembros[id].nome, stdout);


}

//Função para imprimir no ecrã os dados de um teste agendado, ainda sem o respetivo resultado registado:
void printAgendado(tipoTeste vetorTestes[], int pos){

printf("\n%d\t", vetorTestes[pos].id);
printPalavra(vetorTestes[pos].tipo);
printf("\t%d-%d-%d", vetorTestes[pos].data.ano, vetorTestes[pos].data.mes, vetorTestes[pos].data.dia);

}

//Função para imprimir no ecrã os dados de um teste com o respetivo resultado já registado:
void printRealizado(tipoTeste vetorTestes[], int pos){

printf("\n%d\t", vetorTestes[pos].id);
printPalavra(vetorTestes[pos].tipo);
printf("\t%d-%d-%d\t", vetorTestes[pos].data.ano, vetorTestes[pos].data.mes, vetorTestes[pos].data.dia);
printPalavraR(vetorTestes[pos].resultado);
printf("\t%dh%dm\t\t%dm", vetorTestes[pos].horaColheita.hora, vetorTestes[pos].horaColheita.mins, vetorTestes[pos].duracao);

}








