struct Animal{
    void (*mostraratributos) (void *);
    void (*ingresardato) (void  *);
    char tipo;    // ‘h’ o‘c’
        struct AnimalCarnivoro * pAnimalC;
        struct AnimalHerbivoro * pAnimalH;
    // es ptr animalcarnivoro o animalherbivoro.
};

struct AnimalCarnivoro{
     char nombre[20];
     int vida;
     int nro_comidas;
     int ataque;
};

struct AnimalHerbivoro{
     char nombre[20];
     int vida;
     int defensa;
     int nro_comidas;
     int rand_mov;
};
