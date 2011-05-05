/******** Archivo: progenitorP.c ********
Descripcion: Instancia una nueva planta al azar.
             Toma sus datos desde plants.txt
Funciones:   
    getDatosPlanta(char *name, int *trn, int n)
    crearPlanta(struct Animal **ptr)
************************************************/

/******** Función: getDatosPlanta ********
Descripcion: Carga los datos de una planta, desde
             plants.txt, y los devuelve en las variables.

Parámetros:             
            char *name   \
            int *trn     /-> Datos de la Planta.
                                          
            int n        - > Número de la planta en plants.txt
Retorno:    void. Modifica los punteros que recibe como args.
************************************************/

void getDatosPlanta(char *name, int n)
{
    FILE *plantData = fopen("plants.txt","r");
    if(plantData == NULL)
    {
        printf("ERROR: Archivo plants.txt no existe.\n\n");
        printf("Se debe crear un archivo con datos para\n");
        printf("configurar las plantas antes de ejecutar!\n");
        exit(1);
    }
    int numPlantas;
    fscanf(plantData,"%d",&numPlantas);
    n = (n % (numPlantas))+1;
    int i;
    for(i=0;i<n;i++)
    {
        fscanf(plantData,"%s",name);
    }
}

/******** Función: crearPlanta ********
Descripcion: Crea una nueva planta al azar.
             Pide memoria, y carga los datos (via getDatosPlanta)

Parámetros: struct Animal **ptr: Puntero NULL donde se guardará la entidad.
Retorno:    void. Modifica el punteros que recibe como arg.
************************************************/

void crearPlanta(struct Animal **ptr)
{
    struct Planta *paP = (struct Planta *)malloc(sizeof(struct Planta));
    *ptr = (struct Animal *)malloc(sizeof(struct Animal));
    getDatosPlanta(paP->nombre,rand());
    (*ptr)->tipo = 'p';
    (*ptr)->pPlanta = paP;   
    (*ptr)->pAnimalC = NULL;
    (*ptr)->pAnimalH = NULL;
}
