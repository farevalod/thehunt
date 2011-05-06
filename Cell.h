#ifndef CELL_H
#define CELL_H

#include "listaSeresVivos.h"

struct Cell
{
    struct Animal *entidad;
    int xpos;
    int ypos;
};

//Inicializar matriz con las coordenadas de cada celda.
int initMatrix(struct Cell matrix[9][9]);

//Cargar un animal al azar en la celda c.
int makeCell(struct Cell *c, struct Nodo **cList, struct Nodo **hList, struct Nodo **pList);

//Manejar las direcciones ingresadas por el usuario.
int apply(struct Cell matrix[9][9], struct Animal *player, struct Nodo **cList, struct Nodo **hList, struct Nodo **pList, char dir);

#endif
