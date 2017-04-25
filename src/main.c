#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL_image.h>

#include "drawing.h"
#include "ball.h"
#include "bar.h"
#include "brick.h"
#include "geometry.h"
#include "player.h"

static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void reshape(unsigned int width, unsigned int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1., 1., -1., 1.);
}

void setVideoMode(unsigned int width, unsigned int height) {
  if(NULL == SDL_SetVideoMode(width, height, BIT_PER_PIXEL, SDL_OPENGL)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  
  // Fenêtre non redimensionnable
  //reshape(width, height);
}

/** ------------------------------------------------------------------------------------------------ **/

int main(int argc, char** argv) {
  unsigned int WINDOW_WIDTH = 600;
  unsigned int WINDOW_HEIGHT = 600;
  
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }
   
  setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);

  SDL_WM_SetCaption("Arkanopong", NULL);

  // Joueur 1
  Player joueur1 = createPlayer("j1", 0, 3, ColorXY(0, 255, 0));

  // Joueur 2
  Player joueur2 = createPlayer("j2", 0, 3, ColorXY(0, 0, 255));

  // BALLE
  Ball myBall = createBall(0.05, 1, ColorXY(255, 0, 0), PointXY(-0.3, 0), VectorXY(PointXY(0, 0), PointXY(0.01, 0.01)));

  // Variables pour les barres de jeu
  int barre_1_keyPressed_left = 0;
  int barre_1_keyPressed_right = 0;

  int barre_2_keyPressed_left = 0;
  int barre_2_keyPressed_right = 0;

  // BARRES DE JEU
  Bar myBar1 = createBar(0.5, 0.05, 1, joueur1.color, PointXY(0, -0.9));
  Bar myBar2 = createBar(0.5, 0.05, 1, joueur2.color, PointXY(0, 0.9));

  // Vecteurs directeurs de déplacements des barres de jeu
  Vector vector_to_left = VectorXY(PointXY(0.025,0), PointXY(0,0));
  Vector vector_to_right = VectorXY(PointXY(0,0), PointXY(0.025,0));

  int loop = 1;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    // Déplacement de la barre 1
    if (barre_1_keyPressed_left) {
      if (myBar1.position.x > -0.75) {
        Point newPosition = PointPlusVector(myBar1.position, vector_to_left);
        myBar1.position = newPosition;
      }
    }
    if (barre_1_keyPressed_right) {
      if (myBar1.position.x < 0.75) {
        Point newPosition = PointPlusVector(myBar1.position, vector_to_right);
        myBar1.position = newPosition;
      }
    }

    // Déplacement de la barre 2
    if (barre_2_keyPressed_left) {
      if (myBar2.position.x > -0.75) {
        Point newPosition = PointPlusVector(myBar2.position, vector_to_left);
        myBar2.position = newPosition;
      }
    }
    if (barre_2_keyPressed_right) {
      if (myBar2.position.x < 0.75) {
        Point newPosition = PointPlusVector(myBar2.position, vector_to_right);
        myBar2.position = newPosition;
      }
    }

    /* Dessin */
    
    glClearColor(255, 255, 255, 1); // Fond en blanc
    glClear(GL_COLOR_BUFFER_BIT);


    /* Affichage de la balle */
    drawBall(myBall);

    /* Affichage de la barre de déplacement */
    drawBar(myBar1);
    drawBar(myBar2);

    SDL_GL_SwapBuffers();

    /* Collision avec les bords de la fenêtre */
    if(myBall.position.x+myBall.radius >= 1 || myBall.position.x-myBall.radius <= -1) {
        myBall.vector.x *= -1;
    }
    if(myBall.position.y+myBall.radius >= 1) {
      myBall.vector.y *= -1;
      joueur2.life--;
    }
    if(myBall.position.y-myBall.radius <= -1) {
      myBall.vector.y *= -1;
      joueur1.life--;
    }

    if(joueur1.life <= 0)
      joueur2.score += 10;
    if(joueur2.life <= 0)
      joueur1.score += 10;

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

    myBall.position = PointPlusVector(myBall.position, myBall.vector);

    /* ****** */    

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }
      
      switch(e.type) {          
        case SDL_VIDEORESIZE:
          WINDOW_WIDTH = e.resize.w;
          WINDOW_HEIGHT = e.resize.h;
          setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
          break;

        case SDL_KEYDOWN:
          if (e.key.keysym.sym == 'q' || e.key.keysym.sym == SDLK_ESCAPE) {
            loop = 0;
          }
          if (e.key.keysym.sym == SDLK_LEFT) {
              barre_1_keyPressed_left = e.key.state;
          }
          if (e.key.keysym.sym == SDLK_RIGHT) {
              barre_1_keyPressed_right = e.key.state;
          }
          if (e.key.keysym.sym == SDLK_a) {
              barre_2_keyPressed_left = e.key.state;
          }
          if (e.key.keysym.sym == SDLK_z) {
              barre_2_keyPressed_right = e.key.state;
          }
          break;

        case SDL_KEYUP:          
          barre_1_keyPressed_left = e.key.state;
          barre_1_keyPressed_right = e.key.state;
          barre_2_keyPressed_left = e.key.state;
          barre_2_keyPressed_right = e.key.state;

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

  
  SDL_Quit();
  
  return EXIT_SUCCESS;
}
