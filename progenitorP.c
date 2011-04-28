void crearPlanta(struct Animal **ptr,char *name,int trn)
{
    struct Planta *paP = (struct Planta *)malloc(sizeof(struct Planta));
    *ptr = (struct Animal *)malloc(sizeof(struct Animal));
    strcpy(paP->nombre,name);
    paP->turnos = trn;
    (*ptr)->tipo = 'P';
    (*ptr)->pPlanta = paP;   
    (*ptr)->pAnimalC = NULL;
    (*ptr)->pAnimalH = NULL;
}
