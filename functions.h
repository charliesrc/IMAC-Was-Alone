#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


/* 1- DEFINITION DE LA STRUCTURE */

typedef struct Rectangle {
  float hauteur;
  float largeur;
  float x;
  float y;
  float xfin;
  float yfin;
  float puissance;
} Rectangle;


/* 2- INITIALISATION D'UN RECTANGLE */

Rectangle * createRectangle(float hauteur, float largeur, float x, float y, float xfin, float yfin, float puissance);


/* 3- COLLISION */

 int collisionDroite(Rectangle* perso, Rectangle* newObs);

 int collisionGauche(Rectangle* perso, Rectangle* newObs);

 int collisionBas(Rectangle* perso, Rectangle* newObs, int *hauteurArret);

 int collisionHaut(Rectangle* perso, Rectangle* newObs);


 /* 4- DETECTION FIN DE NIVEAU */

 int arrive(Rectangle * perso);


/* 5- FONCTIONS POUR DESSINER */

void drawRepere();

void drawPersonnage(Rectangle * perso);

void drawFinish(Rectangle * perso);

void drawObstacle(Rectangle * newObs);

void drawFleche(Rectangle * perso);

void reshape(int winWidth, int winHeight);

void setVideoMode(int winWidth, int winHeight);


/* 6- FONCTION POUR INITIALISER UN NIVEAU A PARTIR D'UN FICHIER */





