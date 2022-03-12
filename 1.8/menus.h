#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED


#include "estruturas.h"
/*
void menuMembros(int vetorQuant[], tipoMembro vetorMembros[], tipoTeste vetorTestes[]);
void menuTestes(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[]);
void menuVacinacoes(tipoMembro vetorMembros[], int vetorQuant[]);
void menuConfinamentos(tipoMembro vetorMembros[], int vetorQuant[]);
void menuEstatisticas(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[]);
*/

char menuPrincipal(int vetorQuant[]);

char opcaoMembros();
char opcaoTestes();
char opcaoVacinacoes();
char opcaoConfinamentos();
char opcaoEstatisticas();
char opcaoSubRegistar();

#endif // MENUS_H_INCLUDED
