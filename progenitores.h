/******** Archivo: progenitores.h ********
Descripcion: Define Animal, AnimalCarnivoro, AnimalHerbivoro, y Planta
             Son las estructuras que guardan los datos de cada entidad.
************************************************/

#ifndef PROGENITORES_H
#define PROGENITORES_H
struct Animal
{
    void (*getName) (struct Animal *p, char *buf);  //Guarda el nombre de la entidad en el buffer.
    int (*getHP) (struct Animal *p);                //Devuelve los HPs de la entidad.  
    int (*hitHP) (struct Animal *p, int amount);    //Devuelve los HPs de la entidad, menos amount.
    int (*eat)   (struct Animal *p, int inc);
    int (*die)  (struct Animal *p);
    char tipo;    // ‘h’ o‘c’ (o 'p'!) (o 'x'! [cadaver])
        struct AnimalCarnivoro * pAnimalC;
        struct AnimalHerbivoro * pAnimalH;
        struct Planta *pPlanta;
    // es ptr animalcarnivoro o animalherbivoro.
};

struct AnimalCarnivoro
{
     char nombre[20];   //Nombre de la entidad
     int vida;          //Hit Points
     int nro_comidas;   //Contador de comidas
     int ataque;        //Bonificación de ataque
};

struct AnimalHerbivoro
{
     char nombre[20];   //Nombre de la entidad
     int vida;          //Hit points
     int defensa;       //Actúa como Armor Class
     int nro_comidas;   //Contador de comidas
     int rand_mov;      //Número de espacios ganados por salto.
};

struct Planta
{                       //La estructura planta permite darle un poco más de personalidad
    char nombre[20];    //a distintas plantas en el juego.
};

void getDatosCarnivoro(char *name, int *hp, int *atk, int n);
void crearCarnivoro(struct Animal **ptr, int n);
void getDatosHerbivoro(char *name, int *hp, int *def, int *mov, int n);
void crearHerbivoro(struct Animal **ptr, int n);

#endif
