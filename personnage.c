/******************************************************************************
 1- DEFINITION DE LA STRUCTURE
 ******************************************************************************/
typedef struct Personnage {
  int hauteur;
  int largeur;
  int x;
  int y;
  int xfin;
  int yfin;
  int puissance;
} Personnage;

/******************************************************************************
 2- INITIALISATION DU PERSONNAGE
 ******************************************************************************/
Personnage* createPersonnage(int hauteur, int largeur, int x, int y, int xfin, int yfin, int puissance){

  Personnage* perso = calloc(1, sizeof(Personnage));
  perso->hauteur = hauteur;
  perso->largeur = largeur;
  perso->x = x;
  perso->y = y;
  perso->xfin = xfin;
  perso->yfin = yfin;
  perso->puissance = puissance;

  return perso;
}
