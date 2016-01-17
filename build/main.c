
#include "functions.h"
#include "menu.h"
#include "level.h"

#define  MAXPERSO 3
#define  MAXOBS 30


unsigned int windowWidth  = 800;
unsigned int windowHeight = 600;




int main(int argc, char** argv) {

  // Variables niveau 1
  int nbPersoLvl1 = 2;
  int nbObsLvl1 = 6;
  Rectangle * perso1[nbPersoLvl1];
  Rectangle * obs1[nbObsLvl1];

  // Variables niveau 2
  int nbPersoLvl2 = 3;
  int nbObsLvl2 = 17;
  Rectangle * perso2[nbPersoLvl2];
  Rectangle * obs2[nbObsLvl2];

  // Variable niveau 3
  int nbPersoLvl3 = 3;
  int nbObsLvl3 = 14;
  Rectangle * perso3[nbPersoLvl3];
  Rectangle * obs3[nbObsLvl3];

  // Variable niveau actuel
  int nbPerso = MAXPERSO;
  int nbObs;
  Rectangle * perso[MAXPERSO];
  Rectangle * obs[MAXOBS];
  int i;

  // Variable menu
  int enter = 0;
  int menu = 0;
  int selectLvl = 0;

  // Variable physique
  int cmptPerso = 0;
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
  int colDroitePerso = 0;
  int colGauchePerso = 0;
  int colHautPerso = 0;
  int verifColGauchePerso = 0;
  int verifColDroitePerso = 0;
  int verifColHaut = 0;
  int verifColBas = 0;
  int verifColGauche = 0;
  int verifColDroite = 0;
  int verifColHautPerso = 0;
  int hauteurArret = 0;
  int end = 0;


  float centerX = 0;
  float centerY = 0;
  int pause = 0;
  int fin[nbPerso];

  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  setVideoMode(windowWidth, windowHeight);

  SDL_WM_SetCaption("IMAC Was Alone", NULL);


  SDL_Surface* image = IMG_Load("level1.png");
  if(image == NULL) {
      fprintf(stderr, "Impossible de charger l'image \n");
      return EXIT_FAILURE;
  }
  GLuint level1;
  glGenTextures(1, &level1);
  glBindTexture(GL_TEXTURE_2D, level1);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, image->pixels);
  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(image);

  SDL_Surface* image2 = IMG_Load("level2.png");
  if(image2 == NULL) {
      fprintf(stderr, "Impossible de charger l'image \n");
      return EXIT_FAILURE;
  }
  GLuint level2;
  glGenTextures(1, &level2);
  glBindTexture(GL_TEXTURE_2D, level2);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image2->w, image2->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, image2->pixels);
  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(image2);

  SDL_Surface* image3 = IMG_Load("level3.png");
  if(image3 == NULL) {
      fprintf(stderr, "Impossible de charger l'image \n");
      return EXIT_FAILURE;
  }
  GLuint level3;
  glGenTextures(1, &level3);
  glBindTexture(GL_TEXTURE_2D, level3);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image3->w, image3->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, image3->pixels);
  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(image3);

  SDL_Surface* image4 = IMG_Load("menu.jpg");
  if(image4 == NULL) {
      fprintf(stderr, "Impossible de charger l'image \n");
      return EXIT_FAILURE;
  }
  GLuint textureMenu;
  glGenTextures(1, &textureMenu);
  glBindTexture(GL_TEXTURE_2D, textureMenu);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image4->w, image4->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, image4->pixels);
  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(image4);

  SDL_Surface* image5 = IMG_Load("background.png");
  if(image5 == NULL) {
      fprintf(stderr, "Impossible de charger l'image \n");
      return EXIT_FAILURE;
  }
  GLuint textureBackground;
  glGenTextures(1, &textureBackground);
  glBindTexture(GL_TEXTURE_2D, textureBackground);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image5->w, image5->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, image5->pixels);
  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(image5);

  //////////////////////////////////////
  /////////////// SDL MIXER ////////////
  //////////////////////////////////////

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
  {
    printf("%s", Mix_GetError());
  }

  Mix_AllocateChannels(3); //Allouer 3 canaux

  Mix_Chunk *musique; //Création du pointeur de type Mix_Music
  musique = Mix_LoadWAV("ambiance.wav"); //Chargement de la musique
  if(musique == NULL) {
      fprintf(stderr, "Impossible de charger le son %s\n", Mix_GetError());
      return EXIT_FAILURE;
  }

  Mix_Chunk *clic; //Création du pointeur de type Mix_Music
  clic = Mix_LoadWAV("clic.wav"); //Chargement de la musique
  if(clic == NULL) {
      fprintf(stderr, "Impossible de charger le son %s\n", Mix_GetError());
      return EXIT_FAILURE;
  }


  Mix_PlayChannel(0, musique, 5);//Joue le son 1 sur le canal 1 ; le joue une fois (0 + 1)



  int loop = 1;
  while(loop) {


    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* dessin */
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    if (menu == 0) {


      // Création des niveaux
      createLvl1(perso1, obs1);
      createLvl2(perso2, obs2);
      createLvl3(perso3, obs3);

      pause = 0;

        for (i = 0;  i< MAXPERSO; i++) {
          perso[i] = 0;
        }

        if(enter == 0){
          afficherMenu(selectLvl, textureMenu);

        }
        else {
          menu = selectLvl + 1;

          enter = 0;
        }
      }

      if (menu == 1) {
        //NIVEAU 1
        glPushMatrix();
        glTranslatef(perso1[cmptPerso]->x/(-5), perso1[cmptPerso]->y/(-50), 0.0);
        drawBackground(textureBackground);
        glPopMatrix();
        drawNumberLevel(menu, level1);



        nbPerso = nbPersoLvl1;
        nbObs = nbObsLvl1;

        mouvementCamera(perso1[cmptPerso], windowWidth, windowHeight, &centerX, &centerY);

        end = arrive(perso1[cmptPerso]);

          glColor3ub(34, 70, 255); // BLEU
          drawPersonnage(perso1[0]);
          glColor3ub(243, 44, 73); //ROUGE
          drawPersonnage(perso1[1]);

        if(end == 1){
          glColor3ub(255, 255, 255);
          drawPersonnage(perso1[cmptPerso]);
        }

        glColor3ub(0,0,0);
        drawObstacle(obs1[0]);
        drawObstacle(obs1[1]);
        drawObstacle(obs1[2]);
        drawObstacle(obs1[3]);
        drawObstacle(obs1[4]);
        drawObstacle(obs1[5]);

        glColor3ub(255,255,255);
        drawFinish(perso1[0]);
        drawFinish(perso1[1]);

        for(i = 0; i< nbPerso; i++){
          perso[i] = perso1[i];
        }
        for(i = 0; i< nbObs; i++){
          obs[i] = obs1[i];
        }
      }

      if(menu == 2){
        //Niveau 2
        glPushMatrix();
        glTranslatef(perso2[cmptPerso]->x/(-30), perso2[cmptPerso]->y/50, 0.0);
        drawBackground(textureBackground);
        glPopMatrix();
        drawNumberLevel(menu, level2);

        nbPerso = nbPersoLvl2;
        nbObs = nbObsLvl2;

        mouvementCamera(perso2[cmptPerso], windowWidth, windowHeight, &centerX, &centerY);

        end = arrive(perso2[cmptPerso]);


        glColor3ub(237, 255, 113); //JAUNE
        drawPersonnage(perso2[0]);
        glColor3ub(34, 70, 255); // BLEU
        drawPersonnage(perso2[1]);
        glColor3ub(243, 44, 73); //ROUGE
        drawPersonnage(perso2[2]);

        if(end == 1){
          glColor3ub(255, 255, 255);
          drawPersonnage(perso2[cmptPerso]);
        }

        glColor3ub(0,0,0);
        for(i = 0; i < nbObs; i++){
          drawObstacle(obs2[i]);
        }

        glColor3ub(255,255,255);
        drawFinish(perso2[0]);
        drawFinish(perso2[1]);
        drawFinish(perso2[2]);

        for(i = 0; i < nbPerso; i++){
          perso[i] = perso2[i];
        }
        for(i = 0; i < nbObs; i++){
          obs[i] = obs2[i];
        }

      }

      if(menu == 3){
        //Niveau 3
        glPushMatrix();
        glTranslatef(perso3[cmptPerso]->x/(-30), perso3[cmptPerso]->y/50, 0.0);
        drawBackground(textureBackground);
        glPopMatrix();

        drawNumberLevel(menu, level3);

        nbPerso = nbPersoLvl3;
        nbObs = nbObsLvl3;

        mouvementCamera(perso3[cmptPerso], windowWidth, windowHeight, &centerX, &centerY);

        end = arrive(perso3[cmptPerso]);


        glColor3ub(237, 255, 113); //JAUNE
        drawPersonnage(perso3[0]);
        glColor3ub(34, 70, 255); // BLEU
        drawPersonnage(perso3[1]);
        glColor3ub(243, 44, 73); //ROUGE
        drawPersonnage(perso3[2]);

        if(end == 1){
          glColor3ub(255, 255, 255);
          drawPersonnage(perso3[cmptPerso]);
        }

        glColor3ub(0,0,0);
        for(i = 0; i < nbObs; i++){
          drawObstacle(obs3[i]);
        }

        glColor3ub(255,255,255);
        drawFinish(perso3[0]);
        drawFinish(perso3[1]);
        drawFinish(perso3[2]);

        for(i = 0; i< nbPerso; i++){
          perso[i] = perso3[i];
        }
        for(i = 0; i< nbObs; i++){
          obs[i] = obs3[i];
        }
      }



    if (pause == 1) {
      /* Afficher le menu de pause -> un rectangle avec une texture "pause"*/
      centerX = 5;
      centerY = -10;
      mouvementCamera(perso2[cmptPerso], windowWidth, windowHeight, &centerX, &centerY);

      drawPause();
      SDL_GL_SwapBuffers();

    }
    else {
      if(menu != 0){

      drawFleche(perso[cmptPerso]);

      //printf("drawObstacle ok\n");



      SDL_GL_SwapBuffers();

      colBas = 0; //ne pas toucher

      colHaut = 0;
      colGauche = 0;
      colDroite = 0;
      colHautPerso = 0;
      colGauchePerso = 0;
      colDroitePerso = 0;
      float saut = perso[cmptPerso]->puissance;

      //////////////////////////////////////////
      // COLLISIONS ENTRE PERSOS ET OBSTACLES //
      //////////////////////////////////////////

      for(i=0; i < nbObs; i++){
        verifColBas = 0;
        verifColHaut = 0;
        verifColGauche = 0;
        verifColDroite = 0;
        verifColGauche = collisionGauche(perso[cmptPerso], obs[i]);
        verifColDroite = collisionDroite(perso[cmptPerso], obs[i]);
        verifColHaut = collisionHaut(perso[cmptPerso], obs[i]);
        verifColBas = collisionBas(perso[cmptPerso], obs[i], &hauteurArret);
        if(verifColGauche == 1){
          colGauche = 1;
        }
        if(verifColDroite == 1){
          colDroite = 1;
        }
        if(verifColBas == 1){
          colBas = 1;
        }
        if(verifColHaut == 1){
          colHaut = 1;
        }
      }

      //////////////////////////////////////////
      //////// COLLISIONS ENTRE PERSOS  ////////
      //////////////////////////////////////////

      for(i = 0; i < nbPerso; i++){
        verifColBas = 0;
        verifColHautPerso = 0;
        verifColGauchePerso = 0;
        verifColDroitePerso = 0;
        if (i != cmptPerso) {
          verifColGauchePerso = collisionGauche(perso[cmptPerso], perso[i]);
          if(verifColGauchePerso == 1){
            colGauchePerso = 1;
          }
          verifColDroitePerso = collisionDroite(perso[cmptPerso], perso[i]);
          if(verifColDroitePerso == 1){
            colDroitePerso = 1;
          }
          verifColHautPerso = collisionHaut(perso[cmptPerso], perso[i]);
          if(verifColHautPerso == 1){
            colHautPerso = 1;
          }
          verifColBas = collisionBas(perso[cmptPerso], perso[i], &hauteurArret);
          if(verifColBas == 1){
            colBas = 1;
          }
        }
      }

      /* Saut à revoir*/
      if (colBas == 1){
        perso[cmptPerso]->y = hauteurArret;
        saut = perso[cmptPerso]->puissance;
        accelerationChute = 0;
      }
      else{
        gravite = 0.1;
        if(accelerationChute < 4){
          accelerationChute += 0.05;
        }
        perso[cmptPerso]->y -= gravite + accelerationChute ;
      }

      if(colHautPerso == 1){
        rightPressed = 0;
        leftPressed = 0;
        upPressed = 0;
        saut = 0;
      }

      if(upPressed == 1){
          perso[cmptPerso]->y += saut;
          saut -= gravite;
          if(perso[cmptPerso]->y == hauteurArret){
            saut = perso[cmptPerso]->puissance;
            perso[cmptPerso]->y = hauteurArret;
            gravite = 0;
          }
          colBas = 0;
      }

      if(colHaut == 1){
        upPressed = 0;
        saut = 0;
      }


    /*Déplacement*/


      if(rightPressed == 1){
        if (colDroite == 0 && colDroitePerso == 0) {
          vitessex = 0.2;
          if(acceleration < 0.4){
            acceleration += 0.05;
          }
          perso[cmptPerso]->x += (vitessex + acceleration);
        }
        if (colBas == 0 && perso[cmptPerso]->y > 0) {
          perso[cmptPerso]->y -= gravite;
        }
      }
      if(colDroite == 1 || colDroitePerso == 1){
        vitessex = 0;
        acceleration = 0;
        colDroite = 0;
      }

      if(leftPressed == 1){
        if (colGauche == 0 && colGauchePerso == 0) {
        vitessex = 0.2;
          if(acceleration < 0.4){
            acceleration += 0.05;
          }
        perso[cmptPerso]->x -= (vitessex + acceleration);
        }
        if (colBas == 0 && perso[cmptPerso]->y > 0) {
          perso[cmptPerso]->y -= gravite;
        }
      }
      if(colGauche == 1 || colGauchePerso == 1){
        vitessex = 0;
        acceleration = 0;
        colGauche = 0;
      }
      /* Gravité */
      if (perso[cmptPerso]->y > hauteurArret) {
        perso[cmptPerso]->y = perso[cmptPerso]->y - gravite;
      }


      /*Détection de la fin :*/
      fin[cmptPerso] = arrive(perso[cmptPerso]);
      menu = finNiveau(perso, nbPerso, fin, menu);

      /*Si un personnage tombe :*/
      if(perso[cmptPerso]->y < -200){
        menu = 0;
      }
    }
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
              if(selectLvl < 2 && menu == 0){
                selectLvl = (selectLvl + 1) % 3;
                Mix_PlayChannel(1, clic, 0);//Joue le son 1 sur le canal 1 ; le joue une fois (0 + 1)

              }

              break;

            case SDLK_LEFT :
              leftPressed = 0;
              acceleration = 0;
              if(selectLvl > 0 && menu == 0){
                selectLvl = (selectLvl - 1) % 3;
                Mix_PlayChannel(1, clic, 0);//Joue le son 1 sur le canal 1 ; le joue une fois (0 + 1)
              }

              break;

            case SDLK_SPACE :
              upPressed = 0;
              break;

            case 'p' :
              if(pause == 0) pause = 1;
              else pause = 0;
              break;

            case 'm' :
              menu = 0;
              break;

            case SDLK_TAB :
              if(colBas == 1){
                cmptPerso = (cmptPerso + 1) % nbPerso;
              }
              break;

            case SDLK_RETURN :
              enter = 1;
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

  /*FREE*/

  for(i=0; i<nbPersoLvl1; i++){
    free(perso1[i]);
  }
  for(i=0; i<nbPersoLvl2; i++){
    free(perso2[i]);
  }
  for(i=0; i<nbPersoLvl3; i++){
    free(perso3[i]);
  }

  for(i=0; i<nbObsLvl1; i++){
    free(obs1[i]);
  }
  for(i=0; i<nbObsLvl2; i++){
    free(obs2[i]);
  }
  for(i=0; i<nbObsLvl3; i++){
    free(obs3[i]);
  }
  Mix_FreeChunk(musique); //Libération de la musique
  Mix_FreeChunk(clic); //Libération de la musique

  Mix_CloseAudio(); //Fermeture de l'API

  SDL_Quit();

  return EXIT_SUCCESS;
}
