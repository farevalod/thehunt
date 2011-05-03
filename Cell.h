#ifndef CELL_H
#define CELL_H

#include "listaSeresVivos.h"

struct Cell
{
    struct Animal *entidad;
    int xpos;
    int ypos;
};

int initMatrix(struct Cell matrix[9][9]);
int delCell(struct Cell *c);
int makeCell(struct Cell *c, struct Nodo **cList, struct Nodo **hList, struct Nodo **pList);
int apply(struct Cell matrix[9][9], struct Nodo **cList, struct Nodo **hList, struct Nodo **pList, char dir);

#endif
