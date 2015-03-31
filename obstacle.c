/******************************************************************************
 1- DEFINITION DE LA STRUCTURE
 ******************************************************************************/
typedef struct Obstacle {
  int hauteur;
  int largeur;
  float x;
  float y;
} Obstacle;

/******************************************************************************
 2- INITIALISATION DE L'OBSTACLE
 ******************************************************************************/
Obstacle* createObstacle(int hauteur, int largeur, float x, float y){

  Obstacle* obs = calloc(1, sizeof(Obstacle));
  obs->hauteur = hauteur;
  obs->largeur = largeur;
  obs->x = x;
  obs->y = y;

  return obs;
}
