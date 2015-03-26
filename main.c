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

#include "personnage.c"


static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

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

void drawPersonnage(Personnage* newPerso){

  glBegin(GL_QUADS);

  glVertex2f(newPerso->x, newPerso->y);
  glVertex2f(newPerso->x + newPerso->largeur, newPerso->y);
  glVertex2f(newPerso->x + newPerso->largeur, newPerso->y + newPerso->hauteur);
  glVertex2f(newPerso->x, newPerso->y + newPerso->hauteur);
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
  float acceleration = 0.0;

  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  setVideoMode(windowWidth, windowHeight);

  SDL_WM_SetCaption("IMAC Was Alone", NULL);

  Personnage* newPerso = createPersonnage(10, 6, 0, 0, 20, 0, 3);


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

    SDL_GL_SwapBuffers();
    /* ****** */

    if(rightPressed == 1){
      if(acceleration < 0.6){
        acceleration += 0.1;
      }
      newPerso->x += (0.5 + acceleration);
    }

    if(leftPressed == 1){
      if(acceleration < 0.6){
        acceleration += 0.1;
      }
      newPerso->x -= (0.5 + acceleration);
    }

    printf("%f\n", acceleration);
    printf("%f\n", newPerso->x);


    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }

      switch(e.type) {
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

        case SDL_KEYUP :
          switch (e.key.keysym.sym) {
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
            case SDLK_RIGHT :
              rightPressed = 1;
              break;

            case SDLK_LEFT :
              leftPressed = 1;
              break;

            case 'q' :
            case SDLK_ESCAPE :
              loop = 0;
              break;

            default : break;
          }
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
