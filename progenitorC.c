/******** Archivo: progenitorC.c ********
Descripcion: Instancia un nuevo carnívoro al azar.
             Toma sus datos desde carnivores.txt
Funciones:   
    getDatosCarnivoro(char *name, int *hp, int *atk, int n)
    crearCarnivoro(struct Animal **ptr)
************************************************/

/******** Función: getDatosCarnivoro ********
Descripcion: Carga los datos de un carnívoro, desde
             carnivores.txt, y los devuelve en las variables.

Parámetros: char *name  \
            int *hp      - > Datos del Animal.
            int *atk    /
            int n        - > Número del animal en carnivores.txt
Retorno:    void. Modifica los punteros que recibe como args.
************************************************/

void getDatosCarnivoro(char *name, int *hp, int *atk, int n)
{
    FILE *carnivoreData = fopen("carnivores.txt","r");
    if(!carnivoreData)
    {
        printf("ERROR: Archivo carnivores.txt no existe.\n\n");
        printf("Se debe crear un archivo con datos para\n");
        printf("configurar los animales antes de ejecutar!\n");
        exit(1);
    }
    int numAnimales;
    fscanf(carnivoreData,"%d",&numAnimales);
    n = (n % (numAnimales))+1;
    int i;
    for(i=0;i<n;i++)
    {
        fscanf(carnivoreData,"%s",name);
        fscanf(carnivoreData,"%d",hp);
        fscanf(carnivoreData,"%d",atk);
    }
}

void getCarnivoreName(struct Animal *p, char *buf)
{
    strcpy(buf,p->pAnimalC->nombre);
    return;
}

int eatC(struct Animal *p, int inc)
{
    p->pAnimalC->nro_comidas += inc;
    return p->pAnimalC->nro_comidas;
}

int dieC(struct Animal *p)
{
    p->tipo = 'x';
    p->pAnimalC->nro_comidas = 3;
    return 0;
}

int getCarnivoreHP(struct Animal *p)
{
    return p->pAnimalC->vida;
}

int hitCHP(struct Animal *p, int amount)
{
    p->pAnimalC->vida -= amount;
    return p->pAnimalC->vida;
}

/******** Función: crearCarnivoro ********
Descripcion: Crea un nuevo carnívoro al azar.
             Pide memoria, y carga los datos (via getDatosCarnivoro)

Parámetros: struct Animal **ptr: Puntero NULL donde se guardará la entidad.
Retorno:    void. Modifica el punteros que recibe como arg.
************************************************/

void crearCarnivoro(struct Animal **ptr, int n)
{
    struct AnimalCarnivoro *paC = (struct AnimalCarnivoro *)malloc(sizeof(struct AnimalCarnivoro));
    *ptr = (struct Animal *)malloc(sizeof(struct Animal));
    if(n == 0) //Si no especifica animal, se elige uno al azar.
        getDatosCarnivoro(paC->nombre,&(paC->vida),&(paC->ataque),rand());
    else
        getDatosCarnivoro(paC->nombre,&(paC->vida),&(paC->ataque),n-1);
    paC->nro_comidas = 0;
    (*ptr)->tipo = 'c';
    (*ptr)->getName = &getCarnivoreName;
    (*ptr)->getHP = &getCarnivoreHP;
    (*ptr)->hitHP = &hitCHP;
    (*ptr)->eat = &eatC;
    (*ptr)->die = &dieC;
    (*ptr)->pAnimalC = paC;
    (*ptr)->pAnimalH = NULL;
    (*ptr)->pPlanta = NULL;
}
