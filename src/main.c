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
#include "images.h"

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
  
  //************************************

  // Joueur 1
  Player joueur1 = createPlayer("j1", 0, 3, ColorXY(0, 255, 0));

  // Joueur 2
  Player joueur2 = createPlayer("j2", 0, 3, ColorXY(0, 0, 255));

  //************************************

  // BALLE
    Ball myBall1 = createBall(0.05, 1, ColorXY(255, 0, 0), PointXY(0, 0.5), VectorXY(PointXY(0, 0), PointXY(0, -0.01)));
    Ball myBall2 = createBall(0.05, 1, ColorXY(255, 0, 255), PointXY(0, -0.5), VectorXY(PointXY(0, 0), PointXY(0, 0.01)));

  // Variables pour les barres de jeu
  int barre_1_keyPressed_left = 0;
  int barre_1_keyPressed_right = 0;

  int barre_2_keyPressed_left = 0;
  int barre_2_keyPressed_right = 0;

  //************************************

  // BARRES DE JEU
  Bar myBar1 = createBar(0.5, 0.05, 1, joueur1.color, PointXY(0, -0.9));
  Bar myBar2 = createBar(0.5, 0.05, 1, joueur2.color, PointXY(0, 0.9));

  // Vecteurs directeurs de déplacements des barres de jeu
  Vector vector_to_left = VectorXY(PointXY(0.025,0), PointXY(0,0));
  Vector vector_to_right = VectorXY(PointXY(0,0), PointXY(0.025,0));

  //************************************

  // BRIQUES
  int nb_brick_x = 6;
  int nb_brick_y = 3;
  int nb_brick_total = nb_brick_x * nb_brick_y;
  float brick_space_y = (float)(WINDOW_HEIGHT/4)/WINDOW_HEIGHT;
  float hauteur_brick = brick_space_y/nb_brick_y;
  float largeur_brick = (float)(WINDOW_WIDTH/nb_brick_x)/WINDOW_WIDTH;
  float brick_position_x = largeur_brick/2;
  float brick_position_y = (float)(WINDOW_HEIGHT/4)/WINDOW_HEIGHT + (hauteur_brick)/2;
  Brick tab_bricks[nb_brick_total];
  int i = 0;
  int j = 0;
  int count = 0;
  printf("height %d - hau %.3f - lar %.3f\n - pos %.3f - posY %.3f", WINDOW_HEIGHT, hauteur_brick, largeur_brick, brick_position_x, brick_position_y);

  Color3D colorBrick = ColorXY(0, 0, 0);
  for (i = 0; i < nb_brick_x; i++) {
    for (j = 0; j < nb_brick_y; j++) {
      Point position_brick = PointXY(brick_position_x * (i+1)-1, brick_position_y * (j+1)-0.5);
      if (count == 0)
        printf("%.3f\n", brick_position_x * (i+1)-1 );
      tab_bricks[count] = createBrick(largeur_brick, hauteur_brick, 0, 1, colorBrick, position_brick);
      count++;
    }
  }

  //Brick aBrick = createBrick(0.5, 0.5, 1, 1, colorBrick, PointXY(0.5, 0.5));

  

  //************************************

  int loop = 1;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    /* Déplacement de la barre 1 */
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

    /* Déplacement de la barre 2 */
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
    drawBall(myBall1);
    drawBall(myBall2);

    /* Affichage de la barre de déplacement */
    drawBar(myBar1);
    drawBar(myBar2);

    /* Affichage des briques */
    /*for (count = 0; count < nb_brick_total; count++) {
      drawBrick(tab_bricks[count]);
    }
    drawBrick(tab_bricks[0]);*/
    //drawBrick(aBrick);

    /* Affichage des points de vie */
    if(joueur1.life != 0 && joueur2.life != 0)
      image_coeur(joueur1.life, joueur2.life);
    else {
      myBall1 = createBall(0.05, 1, ColorXY(255, 0, 0), PointXY(0, 0.5), VectorXY(PointXY(0, 0), PointXY(0, -0.01)));
      myBall2 = createBall(0.05, 1, ColorXY(255, 0, 255), PointXY(0, -0.5), VectorXY(PointXY(0, 0), PointXY(0, 0.01)));
      if(joueur1.life == 0) {
        joueur1.life = 3;
        joueur2.score++;
      }
      if(joueur2.life == 0) {
        joueur2.life = 3;
        joueur1.score++;
      }
    }

    
    /* Collision avec les bords de la fenêtre */
    if(myBall1.position.x+myBall1.radius >= 1 || myBall1.position.x-myBall1.radius <= -1) {
        myBall1.vector.x *= -1;
    }
    if(myBall1.position.y+myBall1.radius >= 1) {
      joueur2.life--;
      myBall1 = createBall(0.05, 1, ColorXY(255, 0, 0), PointXY(0, 0.5), VectorXY(PointXY(0, 0), PointXY(0, -0.01)));
      myBall2 = createBall(0.05, 1, ColorXY(255, 0, 255), PointXY(0, -0.5), VectorXY(PointXY(0, 0), PointXY(0, 0.01)));
    }
    if(myBall1.position.y-myBall1.radius <= -1) {
      joueur1.life--;
      myBall1 = createBall(0.05, 1, ColorXY(255, 0, 0), PointXY(0, 0.5), VectorXY(PointXY(0, 0), PointXY(0, -0.01)));
      myBall2 = createBall(0.05, 1, ColorXY(255, 0, 255), PointXY(0, -0.5), VectorXY(PointXY(0, 0), PointXY(0, 0.01)));
    }

    if(myBall2.position.x+myBall2.radius >= 1 || myBall2.position.x-myBall2.radius <= -1) {
        myBall2.vector.x *= -1;
    }
    if(myBall2.position.y+myBall2.radius >= 1) {
      joueur2.life--;
      myBall1 = createBall(0.05, 1, ColorXY(255, 0, 0), PointXY(0, 0.5), VectorXY(PointXY(0, 0), PointXY(0, -0.01)));
      myBall2 = createBall(0.05, 1, ColorXY(255, 0, 255), PointXY(0, -0.5), VectorXY(PointXY(0, 0), PointXY(0, 0.01)));
    }
    if(myBall2.position.y-myBall2.radius <= -1) {
      joueur1.life--;
      myBall1 = createBall(0.05, 1, ColorXY(255, 0, 0), PointXY(0, 0.5), VectorXY(PointXY(0, 0), PointXY(0, -0.01)));
      myBall2 = createBall(0.05, 1, ColorXY(255, 0, 255), PointXY(0, -0.5), VectorXY(PointXY(0, 0), PointXY(0, 0.01)));
    }

    collisionWithBar(&myBall1, myBar1, 1);
    collisionWithBar(&myBall1, myBar2, 0);
    collisionWithBar(&myBall2, myBar1, 1);
    collisionWithBar(&myBall2, myBar2, 0);

    myBall1.position = PointPlusVector(myBall1.position, myBall1.vector);
    myBall2.position = PointPlusVector(myBall2.position, myBall2.vector);

    SDL_GL_SwapBuffers();

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
