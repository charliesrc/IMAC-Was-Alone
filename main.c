
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
  int nbPerso;
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




  int loop = 1;
  while(loop) {

    printf("menu : %d\n", menu);
    printf("enter : %d\n", enter);



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

        for (i = 0;  i< MAXPERSO; i++) {
          perso[i] = 0;
        }

        if(enter == 0){
          afficherMenu(selectLvl);
          printf("selectLvl : %d\n", selectLvl);

        }
        else {
          menu = selectLvl + 1;
          printf("menu : %d\n", menu);

          printf("selectLvl : %d\n", selectLvl);

          enter = 0;
        }
      }

      if (menu == 1) {
        //NIVEAU 1

        printf("niveau 1 \n");
        nbPerso = nbPersoLvl1;
        nbObs = nbObsLvl1;

        printf("nbPerso : %d\n", nbPerso);
        printf("nbObs : %d\n", nbObs);

        mouvementCamera(perso1[cmptPerso], windowWidth, windowHeight, &centerX, &centerY);


        glColor3ub(34, 70, 255); // BLEU
        drawPersonnage(perso1[0]);
        glColor3ub(243, 44, 73); //ROUGE
        drawPersonnage(perso1[1]);

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
        printf("niveau 2 \n");
        nbPerso = nbPersoLvl2;
        nbObs = nbObsLvl2;
        printf("nbPerso %d\n", nbPerso);
        printf("cmptPerso %d\n", cmptPerso);

        mouvementCamera(perso2[cmptPerso], windowWidth, windowHeight, &centerX, &centerY);


        glColor3ub(237, 255, 113); //JAUNE
        drawPersonnage(perso2[0]);
        glColor3ub(34, 70, 255); // BLEU
        drawPersonnage(perso2[1]);
        glColor3ub(243, 44, 73); //ROUGE
        drawPersonnage(perso2[2]);

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
        printf("niveau 3 \n");
        nbPerso = nbPersoLvl3;
        nbObs = nbObsLvl3;

        mouvementCamera(perso3[cmptPerso], windowWidth, windowHeight, &centerX, &centerY);

        glColor3ub(237, 255, 113); //JAUNE
        drawPersonnage(perso3[0]);
        glColor3ub(34, 70, 255); // BLEU
        drawPersonnage(perso3[1]);
        glColor3ub(243, 44, 73); //ROUGE
        drawPersonnage(perso3[2]);

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

        printf("nbPerso : %d\n", nbPerso);
        printf("nbObs : %d\n", nbObs);
      }



    if (pause == 1) {
      /* Afficher le menu de pause -> un rectangle avec une texture "pause"*/
      printf("Pause\n");
    }
    else if (pause == 2) {
      /*Afficher la fin*/
      printf("FIN\n");
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


      /* Déplacement */


      printf("colHautPerso : %d\n", colHautPerso);
      printf("verifColHautPerso : %d\n", verifColHautPerso);
      printf("colBas : %d\n", colBas);
      printf("colDroite : %d\n", colDroite);
      printf("colGauche : %d\n", colGauche);
      //printf("upPressed : %d\n", upPressed);
      printf("verifColBas : %d\n", verifColBas);
      //printf("cmptPerso : %d\n", cmptPerso);



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
        printf("GAME OVER\n");
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
              if(selectLvl < 2){
                selectLvl = (selectLvl + 1) % 3;
              }
              break;

            case SDLK_LEFT :
              leftPressed = 0;
              acceleration = 0;
              if(selectLvl > 0){
                selectLvl = (selectLvl - 1) % 3;
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

  // Mix_FreeMusic(musique); Libération de la musique
  // Mix_CloseAudio(); Fermeture de l'API
  SDL_Quit();

  return EXIT_SUCCESS;
}
