#ifndef FUNCOESMEMBROS_H_INCLUDED
#define FUNCOESMEMBROS_H_INCLUDED


#include "estruturas.h"

int procuraMembro(tipoMembro vetorMembros[], int vetorQuant[], int numeroInserido);
tipoMembro registarMembro(tipoMembro vetorMembros[], int vetorQuant[]);
void reverMembro(tipoMembro vetorMembros[], int id);
void verDadosMembro(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[]);
void listarMembros(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[]);
void listarUmMembro(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[], int id);


#endif // FUNCOESMEMBROS_H_INCLUDED
