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
    if(!herbivoreData)
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

void getHerbivoreName(struct Animal *p, char *buf)
{
    strcpy(buf,p->pAnimalH->nombre);
    return;
}

int eatH(struct Animal *p, int inc)
{
    p->pAnimalH->nro_comidas += inc;
    return p->pAnimalH->nro_comidas;
}

int dieH(struct Animal *p)
{
    p->tipo = 'x';
    p->pAnimalH->nro_comidas = 3;
    return 0;
}

int getHerbivoreHP(struct Animal *p)
{
    return p->pAnimalH->vida;
}

int hitHHP(struct Animal *p, int amount)
{
    p->pAnimalH->vida -= amount;
    return p->pAnimalH->vida;
}

/******** Función: crearHerbivoro ********
Descripcion: Crea un nuevo herbivoro al azar.
             Pide memoria, y carga los datos (via getDatosHerbivoro)

Parámetros: struct Animal **ptr: Puntero NULL donde se guardará la entidad.
Retorno:    void. Modifica el punteros que recibe como arg.
************************************************/

void crearHerbivoro(struct Animal **ptr, int n)
{
    struct AnimalHerbivoro *paH = (struct AnimalHerbivoro *)malloc(sizeof(struct AnimalHerbivoro));
    *ptr = (struct Animal *)malloc(sizeof(struct Animal));
    if( n == 0 )
        getDatosHerbivoro(paH->nombre,&(paH->vida),&(paH->defensa),&(paH->rand_mov),rand());
    else
        getDatosHerbivoro(paH->nombre,&(paH->vida),&(paH->defensa),&(paH->rand_mov),n-1);
    paH->nro_comidas = 0;
    (*ptr)->tipo = 'h';
    (*ptr)->getName = &getHerbivoreName;
    (*ptr)->getHP = &getHerbivoreHP;
    (*ptr)->hitHP = &hitHHP;
    (*ptr)->eat = &eatH;
    (*ptr)->die = &dieH;
    (*ptr)->pAnimalH = paH;   
    (*ptr)->pAnimalC = NULL;
    (*ptr)->pPlanta = NULL;
}
