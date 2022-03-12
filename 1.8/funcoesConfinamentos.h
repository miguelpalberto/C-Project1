#ifndef FUNCOESCONFINAMENTOS_H_INCLUDED
#define FUNCOESCONFINAMENTOS_H_INCLUDED

#include "estruturas.h"

void confinarMembro(tipoMembro vetorMembros[], int vetorQuant[]);
void listarConfinamentos(int vetorQuant[]);

void autoConfinamento(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[], int pos);

#endif // FUNCOESCONFINAMENTOS_H_INCLUDED
