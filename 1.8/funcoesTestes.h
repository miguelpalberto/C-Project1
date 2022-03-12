#ifndef FUNCOESTESTES_H_INCLUDED
#define FUNCOESTESTES_H_INCLUDED


#include "estruturas.h"

tipoTeste *agendarTeste(tipoMembro vetorMembros[], tipoTeste *vetorTestes, int vetorQuant[]);
int procuraTestesDia(tipoTeste vetorTestes[], int vetorQuant[], tipoData dataInserida);
int verTesteRepetido(tipoTeste vetorTestes[], int vetorQuant[], tipoTeste teste);
//int verTesteUnico(tipoTeste vetorTestes[], int vetorQuant[], tipoTeste teste);
void alterarAgendamento(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[]);
void registarResultado(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[]);
void registarResultadoId(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[]);

void listarTestesRealizados(tipoTeste vetorTestes[], int vetorQuant[]);
void listarTestesNaoRealizados(tipoTeste vetorTestes[], int vetorQuant[]);
void listarUmTeste(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[]);
int quantidadeTestesPositivos(tipoTeste vetorTestes[], int vetorQuant[], int nUtente);
int quantidadeTestesAgendados(tipoTeste vetorTestes[], int vetorQuant[], int nUtente);
int quantidadeTestesRealizados(tipoTeste vetorTestes[], int vetorQuant[], int nUtente);

tipoTeste *autoAgendamento(tipoTeste *vetorTestes, int vetorQuant[], int posicao);

#endif // FUNCOESTESTES_H_INCLUDED
