int collisionBas(Personnage* newPerso, Obstacle* newObs){

  if(newPerso->y == newObs->y + newObs->hauteur){
    return 1;
  }

  return 0;
  // && newPerso->x > newObs->x && newPerso->x < newObs->x + newObs->largeur
}
