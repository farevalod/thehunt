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
        fscanf(herbivoreData,"%d",&hp);
        fscanf(herbivoreData,"%d",&def);
        fscanf(herbivoreData,"%d",&mov);
    }
}

void crearHerbivoro(struct Animal **ptr)
{
    struct AnimalHerbivoro *paH = (struct AnimalHerbivoro *)malloc(sizeof(struct AnimalHerbivoro));
    *ptr = (struct Animal *)malloc(sizeof(struct Animal));
    getDatosHerbivoro(paH->nombre,&(paH->vida),&(paH->defensa),&(paH->rand_mov),rand());
    paH->nro_comidas = 0;
    (*ptr)->tipo = 'H';
    (*ptr)->pAnimalH = paH;   
    (*ptr)->pAnimalC = NULL;
    (*ptr)->pPlanta = NULL;
}
