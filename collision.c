int collisionBas(Personnage* newPerso, Obstacle* newObs){

  if(newPerso->x + newPerso->largeur > newObs->x && newPerso->x < newObs->x + newObs->largeur){
    if(newPerso->y <= newObs->hauteur){
      return 1;
    }
    else{
      return 0;
    }
  }

  return 0;
}
