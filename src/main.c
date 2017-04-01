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

  // Définition de la balle
  Color3D colorBall = ColorXY(255, 0, 0);
  Point positionBall = PointXY(-0.3, 0);
  Vector vectorBall = VectorXY(PointXY(0, 0), PointXY(0.01, 0.01));
  Ball myBall = createBall(0.05, 1, colorBall, positionBall, vectorBall);

  // Variables pour la barre de jeu
  int barre_1_keyPressed_left = 0;
  int barre_1_keyPressed_right = 0;

  // Position de la barre de jeu (du bas)
  Point position_barre = PointXY(0, -0.9);
  Color3D colorBlack = ColorXY(0, 0, 0);
  Bar myBar = createBar(0.5, 0.05, 1, colorBlack, position_barre);

  // Vecteurs directeurs de déplacements des barres de jeu
  Vector vector_to_left = VectorXY(PointXY(0.025,0), PointXY(0,0));
  Vector vector_to_right = VectorXY(PointXY(0,0), PointXY(0.025,0));

  int loop = 1;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    // Déplacement de la barre de jeu
    if (barre_1_keyPressed_left) {
      if (myBar.position.x > -0.75) {
        Point newPosition = PointPlusVector(myBar.position, vector_to_left);
        myBar.position = newPosition;
      }
    }
    if (barre_1_keyPressed_right) {
      if (myBar.position.x < 0.75) {
        Point newPosition = PointPlusVector(myBar.position, vector_to_right);
        myBar.position = newPosition;
      }
    }

    /* Dessin */
    
    glClearColor(255, 255, 255, 1); // Fond en blanc
    glClear(GL_COLOR_BUFFER_BIT);

    /* Affichage de la balle */
    drawBall(myBall);

    /* Affichage de la barre de déplacement */
    drawBar(myBar);

    SDL_GL_SwapBuffers();

    if(myBall.position.x+myBall.radius >= 1 || myBall.position.x-myBall.radius <= -1) {
        myBall.vector.x *= -1;
    }
    if(myBall.position.y+myBall.radius >= 1 || myBall.position.y-myBall.radius <= -1) {
        myBall.vector.y *= -1;
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
          break;

        case SDL_KEYUP:          
          barre_1_keyPressed_left = e.key.state;
          barre_1_keyPressed_right = e.key.state;

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
