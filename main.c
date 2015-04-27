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

/*#include "rectangle.h"
#include "collision.c"*/


static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;



/******************************************************************************
                        FONCTIONS À DÉPLACER PLUS TARD
 ******************************************************************************/

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
Rectangle * createRectangle(int hauteur, int largeur, float x, float y, float xfin, float yfin, float puissance){

  Rectangle * rect = calloc(1, sizeof(Rectangle));
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

Rectangle * addToListR(Rectangle * tete, int hauteur, int largeur, float x, float y, float xfin, float yfin, float puissance)
{
    /* Empty list */
    if (tete == NULL)
    {
        return createRectangle(hauteur, largeur, x, y, xfin, yfin, puissance);
        fprintf(stderr,"Insertion impossible: Empty list !\n");
        exit(1);
    }

    tete->next = addToListR(tete->next, hauteur, largeur, x, y, xfin, yfin, puissance);
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
        freeListR(&(*tete)->next);
    }
    free(*tete);
    *tete = NULL;
}



/******************************************************************************
1- COLLISIONS --  essayer tout d'un coup et stopper dès que collision
 ******************************************************************************/

int collisionDroite(Rectangle* newPerso, Rectangle* newObs){

  if((newPerso->x + newPerso->largeur > newObs->x) && (newPerso->y < newObs->y + newObs->hauteur))
  {
    return 1;
  }
  return 0;
}

int collisionGauche(Rectangle* newPerso, Rectangle* newObs){

  if((newPerso->x > newObs->x + newObs->largeur) && (newPerso->y > newObs->y + newObs->hauteur))
  {
    return 0;
  } else return 1;
}

int collisionBas(Rectangle* newPerso, Rectangle* newObs){

  if((newPerso->x + newPerso->largeur > newObs->x) && (newPerso->x < newObs->x + newObs->largeur) && (newPerso->y < newObs->y + newObs->hauteur))
  {
    return 1;
  }
  return 0;
}


int collisionHaut(Rectangle* newPerso, Rectangle* newObs){

  if(((newPerso->x + newPerso->largeur < newObs->x) || (newPerso->x > newObs->x + newObs->largeur)) && (newPerso->y + newPerso->hauteur < newObs->y))
  {
    return 0;
  }
  return 1;
}



/*


    || (newPerso->x >= newObs->x + newObs->largeur) // trop à droite
    || (newPerso->y >= newObs->y + newObs->hauteur) // trop en bas
    || (newPerso->y + newPerso->hauteur <= newObs->y) ) // trop en haut



bool Collision(AABB box1,AABB box2)
{
   if((box2.x >= box1.x + box1.w)      // trop à droite
    || (box2.x + box2.w <= box1.x) // trop à gauche
    || (box2.y >= box1.y + box1.h) // trop en bas
    || (box2.y + box2.h <= box1.y))  // trop en haut
          return false; 
   else
          return true; 
}*/





  /*
//vieille collisionBas

  if(newPerso->x + newPerso->largeur > newObs->x && newPerso->x < newObs->x + newObs->largeur){
    if(newPerso->y <= newObs->hauteur){
      return 1;
    }
    else{
      return 0;
    }
  }
*/


unsigned int windowWidth  = 800;
unsigned int windowHeight = 600;

void drawRepere(){
  glBegin(GL_LINES);
  glColor3ub(255,0,0);
  glVertex2f(0,0);
  glVertex2f(0,1);
  glColor3ub(0,255,0);
  glVertex2f(0,0);
  glVertex2f(1,0);
  glEnd();
}

void drawFloor(){
  glColor3ub(0,0,0);

  glBegin(GL_QUADS);

  glVertex2f(-40, 0);
  glVertex2f(40,0);
  glVertex2f(40,-20);
  glVertex2f(-40,-20);
  glEnd();
}

void drawPersonnage(Rectangle * newPerso){

  glBegin(GL_QUADS);

  glVertex2f(newPerso->x, newPerso->y);
  glVertex2f(newPerso->x + newPerso->largeur, newPerso->y);
  glVertex2f(newPerso->x + newPerso->largeur, newPerso->y + newPerso->hauteur);
  glVertex2f(newPerso->x, newPerso->y + newPerso->hauteur);
  glEnd();

}

void drawObstacle(Rectangle * newObs){

  glBegin(GL_QUADS);

  glVertex2f(newObs->x, newObs->y);
  glVertex2f(newObs->x + newObs->largeur, newObs->y);
  glVertex2f(newObs->x + newObs->largeur, newObs->y + newObs->hauteur);
  glVertex2f(newObs->x, newObs->y + newObs->hauteur);
  glEnd();

}

void reshape(int winWidth, int winHeight) {
  glViewport(0, 0, winWidth, winHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-40., 40., -20*(winHeight/(float)winWidth), 60*(winHeight/(float)winWidth));
}

void setVideoMode(int winWidth, int winHeight) {
  if(NULL == SDL_SetVideoMode(winWidth, winHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }

  reshape(winWidth,winHeight);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.2, 0.5, 0.5, 1);
  SDL_GL_SwapBuffers();
}

int main(int argc, char** argv) {

  int rightPressed = 0;
  int leftPressed = 0;
  int upPressed = 0;
  float vitessex = 0;
  float acceleration = 0.0;
  float gravite = 0.2;
  int colBas = 0;
  int colHaut = 0;
  int colGauche = 0;
  int colDroite = 0;

  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  setVideoMode(windowWidth, windowHeight);

  SDL_WM_SetCaption("IMAC Was Alone", NULL);

  Rectangle * newPerso = createRectangle(10, 2, 0, 0, 20, 0, 3);
  float saut = newPerso->puissance;

  Rectangle * newObs = createRectangle(10, 20, 30, 0,  0, 0, 0);
  //Rectangle * newObs = createRectangle(10, 40, 20, 0, 0, 0, 0);
  //addToListR(newObs, 10, 10, -10, 0,  0, 0, 0);

  // PARTIE AJOUT SON
  // if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
  //  {
  //     printf("%s", Mix_GetError());
  //  }
  //  else{
  //    printf("Music load\n");
  //  }
  //  Mix_Music *musique; //Création du pointeur de type Mix_Music
  //  musique = Mix_LoadMUS("bullit.mp3"); //Chargement de la musique
  //   if( musique == NULL )
  //   {
  //       printf("problem\n");
  //   }
  //  Mix_PlayMusic(musique, -1); //Jouer infiniment la musique

  int loop = 1;
  while(loop) {

    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* dessin */
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    drawRepere();
    drawFloor();
    glColor3ub(255,0,0);
    drawPersonnage(newPerso);

    glColor3ub(0,0,0);
    drawObstacle(newObs);
    //drawObstacle(newObs->next);

    SDL_GL_SwapBuffers();
    /* ****** */

    //printf("%d\n", colDroite);
    //printf("%f\n", newPerso->y);


    /*if(colHaut){
      newPerso->y = 0;
      upPressed = 0;

    }*/

      if (colDroite) {
        rightPressed = 0;
        acceleration = 0;
        vitessex = 0;
        newPerso->x = newObs->x - newPerso->largeur;
      }

   /* if (colBas) {

       else if (colGauche) {
        leftPressed = 0;
        newPerso->x = newObs->x + newObs->largeur;
      } else newPerso->y = newObs->hauteur;
    }*/




    /* Saut */
    if(upPressed == 1){

      newPerso->y += saut;
      saut -= gravite;

      if (newPerso->y <= 0){
        upPressed = 0;
        saut = newPerso->puissance;
        colBas = 0;
        newPerso->y = 0;
      }

    }

    /* Déplacement */

    
    if(rightPressed == 1){
      vitessex = 0.5;
      if(acceleration < 0.6){
        acceleration += 0.1;
      }
      newPerso->x += (vitessex + acceleration);
    } else{
      vitessex = 0;
    }

    if(leftPressed == 1){
      vitessex = 0.5;
      if(acceleration < 0.6){
        acceleration += 0.1;
      }
      newPerso->x -= (vitessex + acceleration);
    }

    /* Gravité */
    if (newPerso->y > 0) {
      newPerso->y = newPerso->y - gravite;
    }

/*
    DEBUG
    printf("%f\n", acceleration);
    printf("%f\n", newPerso->x);
*/

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }

      switch(e.type) {

        case SDL_KEYUP :

          switch (e.key.keysym.sym) {

            case SDLK_UP :
              acceleration = 0;
              break;

            case SDLK_RIGHT :
              rightPressed = 0;
              acceleration = 0;
              colBas = collisionBas(newPerso, newObs);
              colHaut = collisionHaut(newPerso, newObs);
              colDroite = collisionDroite(newPerso, newObs);
              colGauche = collisionGauche(newPerso, newObs);

              break;

            case SDLK_LEFT :
              leftPressed = 0;
              acceleration = 0;
              colBas = collisionBas(newPerso, newObs);
              colHaut = collisionHaut(newPerso, newObs);
              colDroite = collisionDroite(newPerso, newObs);
              colGauche = collisionGauche(newPerso, newObs);

              break;

            default : break;
          }
          break;

        case SDL_KEYDOWN :

          switch(e.key.keysym.sym){
            case SDLK_UP :
              upPressed = 1;
              colBas = collisionBas(newPerso, newObs);
              colHaut = collisionHaut(newPerso, newObs);
              colDroite = collisionDroite(newPerso, newObs);
              colGauche = collisionGauche(newPerso, newObs);
              break;

            case SDLK_RIGHT :
              colBas = collisionBas(newPerso, newObs);
              colHaut = collisionHaut(newPerso, newObs);
              colDroite = collisionDroite(newPerso, newObs);
              colGauche = collisionGauche(newPerso, newObs);
              if(colDroite == 1){
                rightPressed = 0;
               } else {
                rightPressed = 1;
               }
              break;

            case SDLK_LEFT :
              leftPressed = 1;
              colBas = collisionBas(newPerso, newObs);
              colHaut = collisionHaut(newPerso, newObs);
              colDroite = collisionDroite(newPerso, newObs);
              colGauche = collisionGauche(newPerso, newObs);
              break;

            case 'q' :
            case SDLK_ESCAPE :
              loop = 0;
              break;

            default : break;
          }
          break;

        case SDL_MOUSEBUTTONUP :
        if(e.button.button == SDL_BUTTON_RIGHT) {

        }
        if(e.button.button == SDL_BUTTON_LEFT) {

        }

          break;

        case SDL_MOUSEBUTTONDOWN :
          if(e.button.button == SDL_BUTTON_RIGHT){

          }
          break;

        case SDL_MOUSEMOTION :

          break;

        case SDL_VIDEORESIZE :
          windowWidth  = e.resize.w;
          windowHeight = e.resize.h;
          setVideoMode(windowWidth,windowHeight);
          break;

        default:

          break;
      }
    }

    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  // Mix_FreeMusic(musique); Libération de la musique
  // Mix_CloseAudio(); Fermeture de l'API
  SDL_Quit();

  return EXIT_SUCCESS;
}
