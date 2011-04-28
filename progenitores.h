struct Animal{
    void (*mostraratributos) (void *);
    void (*ingresardato) (void  *);
    char tipo;    // ‘h’ o‘c’ (o 'p'!)
        struct AnimalCarnivoro * pAnimalC;
        struct AnimalHerbivoro * pAnimalH;
        struct Planta *pPlanta;
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

struct Planta{      //La estructura planta permite darle un poco más de personalidad
    char nombre[20];//a distintas plantas en el juego.
    int turnos;
};
