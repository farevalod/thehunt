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
        fscanf(carnivoreData,"%d",&hp);
        fscanf(carnivoreData,"%d",&atk);
    }
}

void crearCarnivoro(struct Animal **ptr)
{
    struct AnimalCarnivoro *paC = (struct AnimalCarnivoro *)malloc(sizeof(struct AnimalCarnivoro));
    *ptr = (struct Animal *)malloc(sizeof(struct Animal));
    getDatosCarnivoro(paC->nombre,&(paC->vida),&(paC->ataque),rand());
    paC->nro_comidas = 0;
    (*ptr)->tipo = 'C';
    (*ptr)->pAnimalC = paC;
    (*ptr)->pAnimalH = NULL;
    (*ptr)->pPlanta = NULL;
}
