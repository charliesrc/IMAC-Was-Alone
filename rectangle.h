#ifndef RECTANGLE_H
#define RECTANGLE_H

/******************************************************************************
 1- DEFINITION DE LA STRUCTURE
 ******************************************************************************/
typedef struct Rectangle {
  int hauteur;
  int largeur;
  float x;
  float y;
  float xfin;
  float yfin;
  float puissance;
  struct Rectangle* next;
} Rectangle;

/******************************************************************************
 2- INITIALISATION D'UN RECTANGLE
 ******************************************************************************/
Rectangle * createRectangle(int hauteur, int largeur, float x, float y, float xfin, float yfin, float puissance);

/******************************************************************************
3- INSÉRER EN BOUT DE LISTE
 ******************************************************************************/

Rectangle * addToListR(Rectangle * tete, int hauteur, int largeur, float x, float y, float xfin, float yfin, float puissance);


/******************************************************************************
4- LIBÉRER LA LISTE
 ******************************************************************************/

/* ATTENTION il faut remettre le pointeur de la liste à NULL
*   donc passage de l'adresse du pointeur
*/
void freeListR(Rectangle ** tete);


#endif








