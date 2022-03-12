#ifndef FUNCOESAPOIO_H_INCLUDED
#define FUNCOESAPOIO_H_INCLUDED


#include "estruturas.h"


void lerString(char vetor[], int max);
int lerInteiro(int min, int max);
float lerFloat(int min, int max);
void limpaBufferStdin(void);
void limparEcra(void);
char lerCaracter2(char a, char b);
char lerCaracter3(char a, char b, char c);
char lerCaracter4(char a, char b, char c, char d);
char lerCaracter6(char a, char b, char c, char d, char e, char f);
tipoData lerData(int min, int max);
tipoHora lerHora(int min, int max);
void voltarMenu(void);



#endif // FUNCOESAPOIO_H_INCLUDED
