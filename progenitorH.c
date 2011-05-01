/******** Archivo: progenitorH.c ********
Descripcion: Instancia un nuevo herbivoro al azar.
             Toma sus datos desde herbivores.txt
Funciones:   
    getDatosHerbivoro(char *name, int *hp, int *def, int *mov, int n)
    crearHerbivoro(struct Animal **ptr)
************************************************/

/******** Función: getDatosHerbivoro ********
Descripcion: Carga los datos de un herbivoro, desde
             herbivores.txt, y los devuelve en las variables.

Parámetros:             
            char *name   \
            int *hp       -> Datos del Animal. 
            int *def      ->
            int *mov     /
                                          
            int n        - > Número del animal en herbivores.txt
Retorno:    void. Modifica los punteros que recibe como args.
************************************************/

void getDatosHerbivoro(char *name, int *hp, int *def, int *mov, int n)
{
    FILE *herbivoreData = fopen("herbivores.txt","r");
    if(herbivoreData == NULL)
    {
        printf("ERROR: Archivo herbivores.txt no existe.\n\n");
        printf("Se debe crear un archivo con datos para\n");
        printf("configurar los animales antes de ejecutar!\n");
        exit(1);
    }
    int numAnimales;
    fscanf(herbivoreData,"%d",&numAnimales);
    n = (n % (numAnimales))+1;
    int i;
    for(i=0;i<n;i++)
    {
        fscanf(herbivoreData,"%s",name);
        fscanf(herbivoreData,"%d",hp);
        fscanf(herbivoreData,"%d",def);
        fscanf(herbivoreData,"%d",mov);
    }
}

/******** Función: crearHerbivoro ********
Descripcion: Crea un nuevo herbivoro al azar.
             Pide memoria, y carga los datos (via getDatosHerbivoro)

Parámetros: struct Animal **ptr: Puntero NULL donde se guardará la entidad.
Retorno:    void. Modifica el punteros que recibe como arg.
************************************************/

void crearHerbivoro(struct Animal **ptr)
{
    struct AnimalHerbivoro *paH = (struct AnimalHerbivoro *)malloc(sizeof(struct AnimalHerbivoro));
    *ptr = (struct Animal *)malloc(sizeof(struct Animal));
    getDatosHerbivoro(paH->nombre,&(paH->vida),&(paH->defensa),&(paH->rand_mov),rand());
    paH->nro_comidas = 0;
    (*ptr)->tipo = 'h';
    (*ptr)->pAnimalH = paH;   
    (*ptr)->pAnimalC = NULL;
    (*ptr)->pPlanta = NULL;
}
