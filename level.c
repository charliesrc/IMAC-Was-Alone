#include "functions.h"


void createLvl1(Rectangle* perso[], Rectangle* obs[]){

  perso[0] = createRectangle(8, 3, 0, 0, 50, 20, 1.7);
  perso[1] = createRectangle(4, 4, -4, 0, 10, 25, 1.3);


  obs[0] = createRectangle(20, 160, -80, -20, 0, 0, 0);
  obs[1] = createRectangle(10, 30, 30, 0, 0, 0, 0);
  obs[2] = createRectangle(10, 40, -10, 15, 0, 0, 0);
  obs[3] = createRectangle(10, 20, 40, 10, 0, 0, 0);


  obs[4] = createRectangle(150, 50, -130, -30, 0, 0, 0);
  obs[5] = createRectangle(150, 50, 80, -30, 0, 0, 0);
}

void createLvl2(Rectangle* perso[], Rectangle* obs[]){

  perso[0] = createRectangle(2, 8, -54, 80, 49, 80, 1.5);//JAUNE
  perso[1] = createRectangle(4, 4, -60, 80, 37, 68, 1.7);//ROUGE
  perso[2] = createRectangle(10, 2, -56, 80, 55, 48, 2);//BLEU


  obs[0] = createRectangle(150, 50, -110, -30, 0, 0, 0);
  obs[1] = createRectangle(150, 50, 60, -30, 0, 0, 0);

  obs[2] = createRectangle(20, 120, -60, -20, 0, 0, 0);
  obs[3] = createRectangle(80, 20, -60, 0, 0, 0, 0);
  obs[4] = createRectangle(40, 12, -40, 0, 0, 0, 0);
  obs[5] = createRectangle(4, 4, -28, 20, 0, 0, 0);
  obs[6] = createRectangle(8, 8, -12, 0, 0, 0, 0);
  obs[7] = createRectangle(4, 8, -4, 16, 0, 0, 0);
  obs[8] = createRectangle(48, 56, 4, 0, 0, 0, 0);
  obs[9] = createRectangle(8, 8, 20, 48, 0, 0, 0);
  obs[10] = createRectangle(8, 8, 36, 60, 0, 0, 0);
  obs[11] = createRectangle(20, 16, 44, 60, 0, 0, 0);
  obs[12] = createRectangle(24, 52, -28, 72, 0, 0, 0);
  obs[13] = createRectangle(12, 36, -28, 60, 0, 0, 0);
  obs[14] = createRectangle(12, 12, -20, 48, 0, 0, 0);
  obs[15] = createRectangle(8, 8, -28, 52, 0, 0, 0);
  obs[16] = createRectangle(60, 120, -60, 96, 0, 0, 0);
}

void createLvl3(Rectangle* perso[], Rectangle* obs[]){

  perso[0] = createRectangle(10, 2, -80, 40, -18, 96, 2);
  perso[1] = createRectangle(4, 4, -78, 40, 64, 104, 1.2);
  perso[2] = createRectangle(6, 4, -74, 40, 36, 104, 1.5);

  obs[0] = createRectangle(150, 50, -130, -30, 0, 0, 0);
  obs[1] = createRectangle(150, 50, 80, -30, 0, 0, 0);

  obs[2] = createRectangle(20, 40, -80, -20, 0, 0, 0);
  obs[3] = createRectangle(52, 28, -8, -20, 0, 0, 0);
  obs[4] = createRectangle(4, 12, -20, 4, 0, 0, 0);
  obs[5] = createRectangle(8, 8, 20, 20, 0, 0, 0);
  obs[6] = createRectangle(8, 36, -80, 32, 0, 0, 0);
  obs[7] = createRectangle(4, 24, 16, 52, 0, 0, 0);
  obs[8] = createRectangle(8, 32, 36, 72, 0, 0, 0);
  obs[9] = createRectangle(4, 20, -48, 64, 0, 0, 0);
  obs[10] = createRectangle(4, 16, -24, 92, 0, 0, 0);
  obs[11] = createRectangle(4, 12, 32, 100, 0, 0, 0);
  obs[12] = createRectangle(4, 12, 60, 100, 0, 0, 0);
  obs[13] = createRectangle(2, 4, -12, 20, 0, 0, 0);

}
