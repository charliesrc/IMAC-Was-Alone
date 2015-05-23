/******************************************************************************
 1- DEFINITION DE LA STRUCTURE
 ******************************************************************************/
typedef struct Personnage {
  int hauteur;
  int largeur;
  float x;
  float y;
  float xfin;
  float yfin;
  float puissance;
} Personnage;

/******************************************************************************
 2- INITIALISATION DU PERSONNAGE
 ******************************************************************************/
Personnage* createPersonnage(int hauteur, int largeur, float x, float y, float xfin, float yfin, float puissance){

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
