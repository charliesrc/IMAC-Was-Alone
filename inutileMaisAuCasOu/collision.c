/*int collisionBas(Rectangle* newPerso, Rectangle* newObs){

  if(newPerso->x + newPerso->largeur > newObs->x && newPerso->x < newObs->x + newObs->largeur){
    if(newPerso->y <= newObs->hauteur){
      return 1;
    }
    else{
      return 0;
    }
  }

  return 0;
}*/

// VERSION 1 COLLISIONS
// int collisionDroite(Rectangle* newPerso, Rectangle* newObs){
//
//   if((newPerso->x + newPerso->largeur > newObs->x) && (newPerso->y < newObs->y + newObs->hauteur) && (newPerso->x < newObs->x + newObs->largeur))
//   {
//     return 1;
//   }
//   return 0;
// }
//
// int collisionGauche(Rectangle* newPerso, Rectangle* newObs){
//
//   if((newPerso->x < newObs->x + newObs->largeur) && (newPerso->y < newObs->y + newObs->hauteur) && (newPerso->x + newPerso->largeur > newObs->x))
//   {
//     return 1;
//   }
//   return 0;
// }
