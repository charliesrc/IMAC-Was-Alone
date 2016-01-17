
#include "functions.h"

/******************************************************************************
 1- INITIALISATION D'UN RECTANGLE
 ******************************************************************************/
Rectangle * createRectangle(float hauteur, float largeur, float x, float y, float xfin, float yfin, float puissance){

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
 2- COLLISION
 ******************************************************************************/

 int collisionDroite(Rectangle* perso, Rectangle* newObs){

   if((perso->x + perso->largeur > newObs->x - 0.6) && (perso->x + perso->largeur <= newObs->x) && (perso->y <= newObs->y + newObs->hauteur) && (perso->y + perso->hauteur >= newObs->y))
   {
     return 1;
   }
   return 0;
 }

 int collisionGauche(Rectangle* perso, Rectangle* newObs){

   if((perso->x < newObs->x + newObs->largeur + 0.6) && (perso->x >= newObs->x + newObs->largeur) && (perso->y <= newObs->y + newObs->hauteur) && (perso->y + perso->hauteur >= newObs->y))
   {
     return 1;
   }
   return 0;
 }

 int collisionBas(Rectangle* perso, Rectangle* newObs, int *hauteurArret){

   if((perso->x + perso->largeur > newObs->x) && (perso->x < newObs->x + newObs->largeur) && (perso->y <= newObs->y + newObs->hauteur) && (perso->y >= newObs->y + newObs->hauteur - 3))
   {
     *hauteurArret = newObs->y + newObs->hauteur;
     return 1;
   }
   return 0;
 }

  int collisionHaut(Rectangle* perso, Rectangle* newObs){

   if((perso->x + perso->largeur > newObs->x) && (perso->x < newObs->x + newObs->largeur) && (perso->y + perso->hauteur >= newObs->y - 1) && (perso->y < newObs->y + newObs->hauteur - 1))
   {
     return 1;
   }
   return 0;
 }

 /******************************************************************************
  3- DETECTION FIN DE NIVEAU
  ******************************************************************************/

 int arrive(Rectangle * perso){

   int end = 0;

   if((perso->x > perso->xfin) && (perso->x < perso->xfin + perso->largeur) && (perso->y == perso->yfin)){
     end = 1;
   }
   else{
     end = 0;
   }
   return end;
 }

 int finNiveau(Rectangle* perso[], int nbPerso, int fin[], int menu){
    int cpt = 0, i;

    for(i = 0; i < nbPerso; i++){
      if(fin[i]) cpt ++;
    }
    if(cpt == nbPerso){
      menu = menu + 1;
      if(menu > 3){
        menu = 0;
      }
    }

    return menu;
 }


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

void drawFinish(Rectangle * perso){

  glLineWidth(4);

  glBegin(GL_LINE_LOOP);
  glVertex2f(perso->xfin, perso->yfin);
  glVertex2f(perso->xfin + perso->largeur + 1, perso->yfin);
  glVertex2f(perso->xfin + perso->largeur + 1, perso->yfin + perso->hauteur + 1);
  glVertex2f(perso->xfin, perso->yfin + perso->hauteur + 1);
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

void drawFleche(Rectangle * perso){

  glBegin(GL_TRIANGLES);

  glVertex2f(perso->x + ((perso->largeur) / 2), perso->y + perso->hauteur);
  glVertex2f(perso->x + ((perso->largeur) / 2) + 1, perso->y + perso->hauteur + 1);
  glVertex2f(perso->x + ((perso->largeur) / 2) - 1, perso->y + perso->hauteur + 1);

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
}

int drawNumberLevel(int level, GLuint textureId){

    //glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glBegin(GL_QUADS);

    glColor3f(1, 1, 1);

    glTexCoord2f(0, 1);
    glVertex2f(-40, -15);

    glTexCoord2f(1, 1);
    glVertex2f(40, -15);

    glTexCoord2f(1, 0);
    glVertex2f(40, 45);

    glTexCoord2f(0, 0);
    glVertex2f(-40, 45);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);

    return 0;
  }

  int drawBackground(GLuint textureId){

      //glClear(GL_COLOR_BUFFER_BIT);

      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, textureId);

      glBegin(GL_QUADS);

      glColor3f(1, 1, 1);

      glTexCoord2f(0, 1);
      glVertex2f(-80, -30);

      glTexCoord2f(1, 1);
      glVertex2f(80, -30);

      glTexCoord2f(1, 0);
      glVertex2f(80, 90);

      glTexCoord2f(0, 0);
      glVertex2f(-80, 90);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, 0);

      glDisable(GL_TEXTURE_2D);

      return 0;
    }

int drawPause(){

      SDL_Surface* image = image = IMG_Load("pause.png");

      if(image == NULL) {
          fprintf(stderr, "Impossible de charger l'image \n");
          return EXIT_FAILURE;
      }


      GLuint textureId;
      glGenTextures(1, &textureId);
      glBindTexture(GL_TEXTURE_2D, textureId);
      glEnable(GL_BLEND);
            //la couleur de l'objet va être (1-alpha_de_l_objet) * couleur du fond et (le_reste * couleur originale)
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, image->pixels);

      glBindTexture(GL_TEXTURE_2D, 0);

      SDL_FreeSurface(image);

      //glClear(GL_COLOR_BUFFER_BIT);

      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, textureId);

      glBegin(GL_QUADS);

      glColor3f(1, 1, 1);

      glTexCoord2f(0, 1);
      glVertex2f(-40, -15);

      glTexCoord2f(1, 1);
      glVertex2f(40, -15);

      glTexCoord2f(1, 0);
      glVertex2f(40, 45);

      glTexCoord2f(0, 0);
      glVertex2f(-40, 45);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, 0);

      glDisable(GL_TEXTURE_2D);

      return 0;
    }




/******************************************************************************
 5- FONCTION POUR DÉPLACER LA CAMÉRA
 ******************************************************************************/

void mouvementCamera(Rectangle* perso, int windowWidth, int windowHeight, float* centreX, float* centreY){
  float xRapport, yRapport;
  float distanceCentreX, distanceCentreY;

  if(perso){

    distanceCentreX = perso->x - (*centreX);
    distanceCentreY = perso->y - (*centreY);

    xRapport = 0.01*windowWidth;
    yRapport = 0.01*windowHeight;

    if(distanceCentreX > xRapport){
      (*centreX) += +1 * (distanceCentreX - xRapport) / 10;
    }
    else if (distanceCentreX < (-xRapport)){
      (*centreX) -= -1 * (distanceCentreX + xRapport) / 10;
    }

    if(distanceCentreY > yRapport){
      (*centreY) += +1 * (distanceCentreY - yRapport) / 10;
    }
    else if (distanceCentreY < (-yRapport)){
      (*centreY) -= -1 * (distanceCentreY + yRapport) / 1;
    }

    glTranslatef(-(*centreX), -(*centreY), 0.0);

  }
}
