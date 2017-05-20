// Tests de collision

    /* Collision avec la barre 1 */
    if(myBall.position.y-myBall.radius <= (myBar1.position.y + myBar1.longueur_y/2)) {
      /* Balle au centre */
      if(myBall.position.x <= (myBar1.position.x + myBar1.longueur_x/4) && myBall.position.x >= (myBar1.position.x - myBar1.longueur_x/4)) {
        myBall.vector.y *= -1;
      }
      /* Balle à droite */
      else if(myBall.position.x <= (myBar1.position.x + myBar1.longueur_x/2) && myBall.position.x > (myBar1.position.x + myBar1.longueur_x/4)) { // Balle à droite de la barre
        myBall.vector.x = 0.01;
        myBall.vector.y *= -1;
      }
      /* Balle à gauche */
      else if(myBall.position.x < (myBar1.position.x - myBar1.longueur_x/4) && myBall.position.x >= (myBar1.position.x - myBar1.longueur_x/2)) { // Balle à gauche de la barre
        myBall.vector.x = -0.01;
        myBall.vector.y *= -1;
      }
    }

    /* Collision avec la barre 2 */
    if(myBall.position.y+myBall.radius >= (myBar2.position.y - myBar2.longueur_y/2)) {
      /* Balle au centre */
      if(myBall.position.x >= (myBar2.position.x - myBar2.longueur_x/4) && myBall.position.x <= (myBar2.position.x + myBar2.longueur_x/4)) {
        myBall.vector.y *= -1;
      }
      /* Balle à droite */
      else if(myBall.position.x >= (myBar2.position.x - myBar2.longueur_x/2) && myBall.position.x < (myBar2.position.x - myBar2.longueur_x/4)) { // Balle à droite de la barre
        myBall.vector.x = -0.01;
        myBall.vector.y *= -1;
      }
      /* Balle à gauche */
      else if(myBall.position.x > (myBar2.position.x + myBar2.longueur_x/4) && myBall.position.x <= (myBar2.position.x + myBar2.longueur_x/2)) { // Balle à gauche de la barre
        myBall.vector.x = 0.01;
        myBall.vector.y *= -1;
      }
    }