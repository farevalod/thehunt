void crearHerbivoro(struct Animal **ptr,char *name,int hp,int def, int mov)
{
    struct AnimalHerbivoro *paH = (struct AnimalHerbivoro *)malloc(sizeof(struct AnimalHerbivoro));
    *ptr = (struct Animal *)malloc(sizeof(struct Animal));
    strcpy(paH->nombre,name);
    paH->vida = hp;
    paH->nro_comidas = 0;
    paH->defensa = def;
    paH->rand_mov = mov;
    (*ptr)->tipo = 'H';
    (*ptr)->pAnimalH = paH;   
    (*ptr)->pAnimalC = NULL;
}
