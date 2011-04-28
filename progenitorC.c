void crearCarnivoro(struct Animal **ptr,char *name,int hp,int atk)
{
    struct AnimalCarnivoro *paC = (struct AnimalCarnivoro *)malloc(sizeof(struct AnimalCarnivoro));
    *ptr = (struct Animal *)malloc(sizeof(struct Animal));
    strcpy(paC->nombre,name);
    paC->vida = hp;
    paC->nro_comidas = 0;
    paC->ataque = atk;
    (*ptr)->tipo = 'C';
    (*ptr)->pAnimalC = paC;   
    (*ptr)->pAnimalH = NULL;
    (*ptr)->pPlanta = NULL;
}
