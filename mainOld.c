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

  return rect;
}

/******************************************************************************
1- COLLISIONS --  essayer tout d'un coup et stopper dès que collision
 ******************************************************************************/

int collisionDroite(Rectangle* perso, Rectangle* newObs){

  if((perso->x + perso->largeur > newObs->x - 0.5) && (perso->x + perso->largeur <= newObs->x + 0.5) && (perso->y < newObs->y + newObs->hauteur))
  {
    return 1;
  }
  return 0;
}

int collisionGauche(Rectangle* perso, Rectangle* newObs){

  if((perso->x < newObs->x + newObs->largeur + 0.5) && (perso->x >= newObs->x + newObs->largeur - 0.5) && (perso->y < newObs->y + newObs->hauteur))
  {
    return 1;
  }
  return 0;
}

int collisionBas(Rectangle* perso, Rectangle* newObs, int *hauteurArret){

  if((perso->x + perso->largeur > newObs->x) && (perso->x < newObs->x + newObs->largeur) && (perso->y <= newObs->y + newObs->hauteur))
  {
    *hauteurArret = newObs->y + newObs->hauteur;
    return 1;
  }
  return 0;
}


int collisionHaut(Rectangle* perso, Rectangle* newObs){

  if(((perso->x + perso->largeur < newObs->x) || (perso->x > newObs->x + newObs->largeur)) && (perso->y + perso->hauteur < newObs->y))
  {
    return 0;
  }
  return 1;
}

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

void drawPersonnage(Rectangle * perso){

  glBegin(GL_QUADS);

  glVertex2f(perso->x, perso->y);
  glVertex2f(perso->x + perso->largeur, perso->y);
  glVertex2f(perso->x + perso->largeur, perso->y + perso->hauteur);
  glVertex2f(perso->x, perso->y + perso->hauteur);
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

  int nbPerso = 1;
  int nbObs = 3;
  int rightPressed = 0;
  int leftPressed = 0;
  int upPressed = 0;
  float vitessex = 0;
  float acceleration = 0.0;
  float accelerationChute= 0.0;
  float gravite = 0.2;
  int colBas = 0;
  int colHaut = 0;
  int colGauche = 0;
  int colDroite = 0;
  int hauteurArret = 0;
  Rectangle * Perso[nbPerso];
  Rectangle * Obs[nbObs];

  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  setVideoMode(windowWidth, windowHeight);

  SDL_WM_SetCaption("IMAC Was Alone", NULL);

  Perso[1] = createRectangle(10, 2, 0, 0, 20, 0, 4);
  float saut = Perso[1]->puissance;

  Obs[1] = createRectangle(10, 100, -10, 0,  0, 0, 0);
  Obs[2] = createRectangle(10, 30, 10, 0,  0, 0, 0);
  Obs[3] = createRectangle(30, 50, 50, 20,  0, 0, 0);


  //Rectangle * addToListR(Rectangle * tete, int hauteur, int largeur, float x, float y, float xfin, float yfin, float puissance)
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

    printf("glLoadIdentity OK\n");
    printf("%f\n", Perso[1]->x);
    //glTranslatef(- Perso[1]->x, - Perso[1]->y, 0.0);
    printf("Translate OK\n");

    drawRepere();
    //drawFloor();
    drawObstacle(Obs[i]);

    glColor3ub(255,0,0);
    drawPersonnage(Perso[1]);

    glColor3ub(0,0,0);

    for(int i = 0; i < nbObs; i++){
      drawObstacle(Obs[i]);
    }
    SDL_GL_SwapBuffers();
    /* ****** */
    //printf("%f\n", Perso[1]->y);


    /*if(colHaut){
      Perso[1]->y = 0;
      upPressed = 0;

    }*/



   /* if (colBas) {

       else if (colGauche) {
        leftPressed = 0;
        Perso[1]->x = newObs->x + newObs->largeur;
      } else Perso[1]->y = newObs->hauteur;
    }*/

    //col = Collision(Perso[1], newObs, &colBas, &colHaut, &colDroite, &colGauche);

    // if(colBas == 1){
    //     gravite = 0;
    //     upPressed = 0;
    //     colBas = 0;
    //     saut = 0;
    // }

    for(int i=0; i < nbObs; i++){
      colGauche = collisionGauche(Perso[1], Obs[i]);
      colDroite = collisionDroite(Perso[1], Obs[i]);
      colBas = collisionBas(Perso[1], Obs[i], &hauteurArret);
    }

    /* Saut */
    if (colBas == 1){
      Perso[1]->y = hauteurArret;
      saut = Perso[1]->puissance;
      accelerationChute = 0;
    }
    else{
      gravite = 0.2;
      if(accelerationChute < 10){
        accelerationChute += 0.1;
      }
      Perso[1]->y -= gravite + accelerationChute ;
    }
    if(upPressed == 1){
        Perso[1]->y += saut;
        saut -= gravite;
        if(Perso[1]->y == hauteurArret){
          saut = Perso[1]->puissance;
          Perso[1]->y = hauteurArret;
          gravite = 0;
        }
    }



    /* Déplacement */


    printf("colHaut : %d\n", colHaut);
    printf("colBas : %d\n", colBas);
    printf("colDroite : %d\n", colDroite);
    printf("colGauche : %d\n", colGauche);
    printf("upPressed : %d\n", upPressed);

    if(rightPressed == 1){
      if (colDroite == 0) {
        vitessex = 0.4;
        if(acceleration < 0.6){
          acceleration += 0.1;
        }
        Perso[1]->x += (vitessex + acceleration);
      }
      if (colBas == 0 && Perso[1]->y > 0) {
        Perso[1]->y -= gravite;
      }
    }
    if(colDroite == 1){
      vitessex = 0;
      acceleration = 0;
      //Perso[1]->x = Perso[1]->x - 1;
      colDroite = 0;
    }

    if(leftPressed == 1){
      if (colGauche == 0) {
      vitessex = 0.4;
        if(acceleration < 0.6){
          acceleration += 0.1;
        }
      Perso[1]->x -= (vitessex + acceleration);
      }
      if (colBas == 0 && Perso[1]->y > 0) {
        Perso[1]->y -= gravite;
      }
    }
    if(colGauche == 1){
      vitessex = 0;
      acceleration = 0;
      //Perso[1]->x = Perso[1]->x + 1;
      colGauche = 0;
    }
    /* Gravité */
    if (Perso[1]->y > hauteurArret) {
      Perso[1]->y = Perso[1]->y - gravite;
    }

/*
    DEBUG
    printf("%f\n", acceleration);
    printf("%f\n", Perso[1]->x);
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
            upPressed = 0;

              acceleration = 0;
              break;

            case SDLK_RIGHT :
              rightPressed = 0;
              acceleration = 0;



              break;

            case SDLK_LEFT :
              leftPressed = 0;
              acceleration = 0;

              break;

            default : break;
          }
          break;

        case SDL_KEYDOWN :

          switch(e.key.keysym.sym){
            case SDLK_UP :
              upPressed = 1;
              break;

            case SDLK_RIGHT :
              // if(colDroite == 1){
              //   rightPressed = 0;
              //  } else {
              //   rightPressed = 1;
              //  }

              //  if (colDroite == 1) {
              //    rightPressed = 0;
              //    acceleration = 0;
              //    vitessex = 0;
              //    colDroite = 0;
              //    Perso[1]->x = newObs->x - Perso[1]->largeur;
              //  }
              //  else {
              //    rightPressed = 1;
              //   }

              colGauche = 0;

              rightPressed = 1;
              break;

            case SDLK_LEFT :
              colDroite = 0;
              leftPressed = 1;
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
