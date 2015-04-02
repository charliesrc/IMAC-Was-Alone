#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

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
Rectangle* createRectancle(int hauteur, int largeur, float x, float y, float xfin, float yfin, float puissance){

  Rectangle* rect = calloc(1, sizeof(Rectangle));
  rect->hauteur = hauteur;
  rect->largeur = largeur;
  rect->x = x;
  rect->y = y;
  rect->xfin = xfin;
  rect->yfin = yfin;
  rect->puissance = puissance;
  rect->next = NULL;

  return rect;
}

/******************************************************************************
3- INSÉRER EN BOUT DE LISTE
 ******************************************************************************/

Rectangle * addToListR(Rectangle * tete, int v)
{
    /* Empty list */
    if (tete == NULL)
    {
        return createRectangle(10,10,0,0,30,20,3);
        fprintf(stderr,"Insertion impossible: Empty list !\n");
        exit(1);
    }

    tete->next = addToListR(tete->next,v);
    return tete;
}


/******************************************************************************
4- LIBÉRER LA LISTE
 ******************************************************************************/

/* ATTENTION il faut remettre le pointeur de la liste à NULL
*   donc passage de l'adresse du pointeur
*/
void freeListR(Rectangle ** tete)
{
    /* Empty list */
    if (*tete == NULL)
    {
        return;
    }

    if ((*tete)->next != NULL)
    {
        freeListR((*tete)->next);
    }
    free(*tete);
    *tete = NULL;
}











