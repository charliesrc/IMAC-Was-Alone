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

/******************************************************************************
 1- DEFINITION DE LA STRUCTURE
 ******************************************************************************/
typedef struct Rectangle {
  float hauteur;
  float largeur;
  float x;
  float y;
  float xfin;
  float yfin;
  float puissance;
} Rectangle;

/******************************************************************************
 2- INITIALISATION D'UN RECTANGLE
 ******************************************************************************/
Rectangle * createRectangle(float hauteur, float largeur, float x, float y, float xfin, float yfin, float puissance){

  Rectangle * rect = calloc(1, sizeof(Rectangle));
  rect->hauteur = hauteur;
  rect->largeur = largeur;
  rect->x = x;
  rect->y = y;
  rect->xfin = xfin + 2;
  rect->yfin = yfin + 2;
  rect->puissance = puissance;

  return rect;
}

/******************************************************************************
 3- COLLISION
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

/******************************************************************************
 4- FONCTIONS POUR DESSINER
 ******************************************************************************/

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
  int nbObs = 2;
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
  int verifColBas = 0;
  int hauteurArret = 0;
  Rectangle * perso[nbPerso];
  Rectangle * obs[nbObs];

  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  setVideoMode(windowWidth, windowHeight);

  SDL_WM_SetCaption("IMAC Was Alone", NULL);


  perso[0] = createRectangle(10, 2, 0, 2, 0, 0, 4);
  float saut = perso[0]->puissance;


  obs[0] = createRectangle(10, 100, -50, -10, 0, 0, 0);
  obs[1] = createRectangle(10, 30, 30, 0, 0, 0, 0);


  int loop = 1;
  while(loop) {

    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* dessin */
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslatef(- perso[0]->x, - perso[0]->y, 0.0);

    drawRepere();

    //printf("drawRepere ok\n");

    glColor3ub(255, 0, 0);
    drawPersonnage(perso[0]);

    glColor3ub(0,0,0);
    drawObstacle(obs[0]);
    drawObstacle(obs[1]);
    //printf("drawObstacle ok\n");



    SDL_GL_SwapBuffers();


    for(int i=0; i < nbObs; i++){
      colGauche = collisionGauche(perso[0], obs[i]);
      colDroite = collisionDroite(perso[0], obs[i]);
      verifColBas = collisionBas(perso[0], obs[i], &hauteurArret);
      if(verifColBas == 1){
        colBas = 1;
      }
    }

    /* Saut */
    if (colBas == 1){
      perso[0]->y = hauteurArret;
      saut = perso[0]->puissance;
      accelerationChute = 0;
    }
    else{
      gravite = 0.2;
      if(accelerationChute < 10){
        accelerationChute += 0.1;
      }
      perso[0]->y -= gravite + accelerationChute ;
    }
    if(upPressed == 1){
        perso[0]->y += saut;
        saut -= gravite;
        if(perso[0]->y == hauteurArret){
          saut = perso[0]->puissance;
          perso[0]->y = hauteurArret;
          gravite = 0;
        }
        colBas = 0;
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
        perso[0]->x += (vitessex + acceleration);
      }
      if (colBas == 0 && perso[0]->y > 0) {
        perso[0]->y -= gravite;
      }
    }
    if(colDroite == 1){
      vitessex = 0;
      acceleration = 0;
      //perso[0]->x = perso[0]->x - 1;
      colDroite = 0;
    }

    if(leftPressed == 1){
      if (colGauche == 0) {
      vitessex = 0.4;
        if(acceleration < 0.6){
          acceleration += 0.1;
        }
      perso[0]->x -= (vitessex + acceleration);
      }
      if (colBas == 0 && perso[0]->y > 0) {
        perso[0]->y -= gravite;
      }
    }
    if(colGauche == 1){
      vitessex = 0;
      acceleration = 0;
      //perso[0]->x = perso[0]->x + 1;
      colGauche = 0;
    }
    /* Gravité */
    if (perso[0]->y > hauteurArret) {
      perso[0]->y = perso[0]->y - gravite;
    }




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
