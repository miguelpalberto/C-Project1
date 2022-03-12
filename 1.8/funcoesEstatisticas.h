#ifndef FUNCOESESTATISTICAS_H_INCLUDED
#define FUNCOESESTATISTICAS_H_INCLUDED


#include "estruturas.h"

int contarVacinados(tipoMembro vetorMembros[], int vetorQuant[]);
void menuEstatisticas(tipoMembro vetorMembros[], tipoTeste vetorTeste[], int vetorQuant[]);

void estatisticasGerais(tipoMembro vetorMembros[], tipoTeste vetorTestes[], int vetorQuant[]);
void membrosMenosTestes(tipoMembro vetorMembros[], int vetorQuant[]);
void testesRecentes(tipoTeste vetorTestes[], int vetorQuant[]);



#endif // FUNCOESESTATISTICAS_H_INCLUDED
