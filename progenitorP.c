void getDatosPlanta(char *name, int *trn, int n)
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
        fscanf(plantData,"%d",&trn);
    }
}

void crearPlanta(struct Animal **ptr)
{
    struct Planta *paP = (struct Planta *)malloc(sizeof(struct Planta));
    *ptr = (struct Animal *)malloc(sizeof(struct Animal));
    getDatosPlanta(paP->nombre,&(paP->turnos),rand());
    (*ptr)->tipo = 'P';
    (*ptr)->pPlanta = paP;   
    (*ptr)->pAnimalC = NULL;
    (*ptr)->pAnimalH = NULL;
}
