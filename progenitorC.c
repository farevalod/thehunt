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
    if(carnivoreData == NULL)
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

/******** Función: crearCarnivoro ********
Descripcion: Crea un nuevo carnívoro al azar.
             Pide memoria, y carga los datos (via getDatosCarnivoro)

Parámetros: struct Animal **ptr: Puntero NULL donde se guardará la entidad.
Retorno:    void. Modifica el punteros que recibe como arg.
************************************************/

void crearCarnivoro(struct Animal **ptr)
{
    struct AnimalCarnivoro *paC = (struct AnimalCarnivoro *)malloc(sizeof(struct AnimalCarnivoro));
    *ptr = (struct Animal *)malloc(sizeof(struct Animal));
    getDatosCarnivoro(paC->nombre,&(paC->vida),&(paC->ataque),rand());
    paC->nro_comidas = 0;
    (*ptr)->tipo = 'c';
    (*ptr)->pAnimalC = paC;
    (*ptr)->pAnimalH = NULL;
    (*ptr)->pPlanta = NULL;
}
