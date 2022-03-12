#ifndef FUNCOESFICHEIROS_H_INCLUDED
#define FUNCOESFICHEIROS_H_INCLUDED

#include "estruturas.h"
void loadVetorQuant(int vetorQuant[]);
void loadVetorMembros(tipoMembro vetorMembros[], int vetorQuant[]);
tipoTeste *loadVetorTestes(tipoTeste *vetorTestes, int vetorQuant[]);
void gravarVetorQuant(int vetorQuant[]);
void gravarVetorMembros(tipoMembro vetorMembros[], int vetorQuant[]);
void gravarVetorTestes(tipoTeste vetorTestes[], int vetorQuant[]);

void gravarLogTestesTxt(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[], int posicao);

void gravarLogConfinamentos(tipoConf conf);
//void gravarLogConfinamentosTxt(tipoConf conf);
tipoConf *lerLogConfinamentos(tipoConf *vetorConf, int vetorQuant[]);

#endif // FUNCOESFICHEIROS_H_INCLUDED
