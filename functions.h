#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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

/*

en gros ça permet de mettre tous tes fichiers .h dans un dossier "includes",
tous tes fichiers .c dans un dossier "src" et faut que tu créé un dossier "bin"
pour mettre tous tes fichiers .o dedans. Et c'est généré automatiquement,
plus besoin d'écrire un nouveau fichier (comme function.o) à chaque fois que tu en fais un,
suffit de le mettre dans le dossier et ça récupère tout!!

*/


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

int finNiveau(Rectangle* perso[], int nbPerso, int fin[], int menu);


/* 5- FONCTIONS POUR DESSINER */

void drawRepere();

int drawPause();

int drawNumberLevel(int level);

void drawPersonnage(Rectangle * perso);

void drawFinish(Rectangle * perso);

void drawObstacle(Rectangle * newObs);

void drawFleche(Rectangle * perso);

void reshape(int winWidth, int winHeight);

void setVideoMode(int winWidth, int winHeight);


/* 6-FONCTION POUR DÉPLACER LA CAMÉRA */
void mouvementCamera(Rectangle* perso, int windowWidth, int windowHeight, float* centreX, float* centreY);

/* 7- FONCTION POUR INITIALISER UN NIVEAU A PARTIR D'UN FICHIER */
