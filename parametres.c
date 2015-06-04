// niveau 2  

  perso2[0] = createRectangle(4, 4, -60, 80, 40, 68, 1.4);
  perso2[1] = createRectangle(10, 2, -56, 80, 58, 48, 2);
  perso2[2] = createRectangle(4, 8, -54, 80, 52, 80, 1);


  obs2[0] = createRectangle(150, 50, -110, -30, 0, 0, 0);
  obs2[1] = createRectangle(150, 50, 60, -30, 0, 0, 0);

  obs2[2] = createRectangle(20, 120, -60, -20, 0, 0, 0);
  obs2[3] = createRectangle(80, 20, -60, 0, 0, 0, 0);
  obs2[4] = createRectangle(40, 12, -40, 0, 0, 0, 0);
  obs2[5] = createRectangle(4, 4, -28, 20, 0, 0, 0);
  obs2[6] = createRectangle(8, 8, -12, 0, 0, 0, 0);
  obs2[7] = createRectangle(4, 8, -4, 16, 0, 0, 0);
  obs2[8] = createRectangle(48, 56, 4, 0, 0, 0, 0);
  obs2[9] = createRectangle(8, 8, 20, 48, 0, 0, 0);
  obs2[10] = createRectangle(8, 8, 36, 60, 0, 0, 0);
  obs2[11] = createRectangle(20, 16, 44, 60, 0, 0, 0);
  obs2[12] = createRectangle(24, 52, -28, 72, 0, 0, 0);
  obs2[13] = createRectangle(12, 36, -28, 60, 0, 0, 0);
  obs2[14] = createRectangle(12, 12, -20, 48, 0, 0, 0);
  obs2[15] = createRectangle(8, 8, -28, 52, 0, 0, 0);
  obs2[16] = createRectangle(60, 120, -60, 96, 0, 0, 0);


// boucle affichage niveau 2

  for(i = 0; i < nbPerso; i++){
    drawPersonnage(perso2[i]);
  }

  for(i = 0; i < nbObs; i++){
    drawObstacle(obs2[i]);
  }

// niveau 3

  perso3[0] = createRectangle(10, 2, -80, 40, -26, 96, 2);
  perso3[1] = createRectangle(4, 4, -78, 40, 64, 104, 1.3);
  perso3[2] = createRectangle(6, 4, -74, 40, 36, 104, 1);

  obs3[0] = createRectangle(150, 50, -130, -30, 0, 0, 0);
  obs3[1] = createRectangle(150, 50, 80, -30, 0, 0, 0);

  obs3[2] = createRectangle(20, 40, -80, -20, 0, 0, 0);
  obs3[3] = createRectangle(52, 28, -8, -20, 0, 0, 0);
  obs3[4] = createRectangle(4, 12, -20, 4, 0, 0, 0);
  obs3[5] = createRectangle(8, 8, 20, 20, 0, 0, 0);
  obs3[6] = createRectangle(8, 36, -80, 32, 0, 0, 0);
  obs3[7] = createRectangle(4, 24, 16, 52, 0, 0, 0);
  obs3[8] = createRectangle(8, 32, 36, 72, 0, 0, 0);
  obs3[9] = createRectangle(4, 20, -48, 64, 0, 0, 0);
  obs3[10] = createRectangle(4, 16, -32, 92, 0, 0, 0);
  obs3[11] = createRectangle(4, 12, 32, 100, 0, 0, 0);
  obs3[12] = createRectangle(4, 12, 60, 100, 0, 0, 0);


// boucle affichage niveau 3

  for(i = 0; i < nbPerso; i++){
    drawPersonnage(perso3[i]);
  }

  for(i = 0; i < nbObs; i++){
    drawObstacle(obs3[i]);
  }







