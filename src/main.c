#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL_image.h>

static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void reshape(unsigned int width, unsigned int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1., 1., -1., 1.);
}

void setVideoMode(unsigned int width, unsigned int height) {
  if(NULL == SDL_SetVideoMode(width, height, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  
  reshape(width, height);
}


/** Fonctions de dessin canonique. **/

void draw_square(int full) {
  /** Dessine un carré (plein ou non) de côté 1 et centré en (0, 0). **/
  glBegin(full ? GL_QUADS : GL_LINE_LOOP);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(-0.5, -0.5);
  glEnd();
}

void draw_rounded_square(int full, float radius) {
  /** Dessine un carré (plein ou non) de côté 1 et centré en (0, 0), dont les bords sont arrondis de rayon = radius. **/
  glBegin(full ? GL_POLYGON : GL_LINES);
    glVertex2f(-0.5+radius, 0.5);
    glVertex2f(0.5-radius, 0.5);
    glVertex2f(0.5, 0.5-radius);
    glVertex2f(0.5, -0.5+radius);
    glVertex2f(0.5-radius, -0.5);
    glVertex2f(-0.5+radius, -0.5);
    glVertex2f(-0.5, -0.5+radius);
    glVertex2f(-0.5, 0.5-radius);
  glEnd();

  float j;

  glBegin(full ? GL_POLYGON : GL_LINE_STRIP);
  for(j=M_PI/2; j<M_PI; j+=0.01)
    glVertex2f(-0.5+radius+cos(j)*radius, 0.5-radius+sin(j)*radius);
  glEnd();

  glBegin(full ? GL_POLYGON : GL_LINE_STRIP);
  for(j=0; j<M_PI/2; j+=0.01)
    glVertex2f(0.5-radius+cos(j)*radius, 0.5-radius+sin(j)*radius);
  glEnd();

  glBegin(full ? GL_POLYGON : GL_LINE_STRIP);
  for(j=3*M_PI/2; j<2*M_PI; j+=0.01)
    glVertex2f(0.5-radius+cos(j)*radius, -0.5+radius+sin(j)*radius);
  glEnd();

  glBegin(full ? GL_POLYGON : GL_LINE_STRIP);
  for(j=M_PI; j<3*M_PI/2; j+=0.01)
    glVertex2f(-0.5+radius+cos(j)*radius, -0.5+radius+sin(j)*radius);
  glEnd();
}

void draw_circle(int full) {
  glBegin(full ? GL_POLYGON : GL_LINE_LOOP);
  float j;
  for(j=0; j<2*M_PI; j+=0.01) {
    glTexCoord2f(cos(j)+0.5, sin(j)+0.5);
    glVertex2f(cos(j), sin(j));
  }
  glEnd();
}

/** ------------------------------ **/

void draw_principal_arm() {
  /** Dessine le bras principal, à l'horizontal. **/

  glPushMatrix();
  glTranslatef(0.6, 0, 0);
  glScalef(0.1, 0.1, 1.0);
  draw_circle(0);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.2, 0.2, 1.0);
  draw_circle(0);
  glPopMatrix();

  glBegin(GL_LINES);
    glVertex2f(0, 0.2);
    glVertex2f(0.6, 0.1);
    glVertex2f(0, -0.2);
    glVertex2f(0.6, -0.1);
  glEnd();

}



int main(int argc, char** argv) {
  unsigned int WINDOW_WIDTH = 600;
  unsigned int WINDOW_HEIGHT = 600;
  
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }
   
  setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);

  SDL_WM_SetCaption("Arkanopong", NULL);

  /* TEXTURE DE LA BALLE */
  GLuint textureBalle;

  SDL_Surface *image = IMG_Load("images/balle.jpg");
  if(image == NULL)
    printf("Erreur, l'image n'a pas pu être chargée\n");

  glGenTextures(1, &textureBalle);
  glBindTexture(GL_TEXTURE_2D, textureBalle);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glBindTexture(0, textureBalle);

  GLenum format;
  switch(image->format->BytesPerPixel) {
    case 1:
      format = GL_RED;
      break;

    case 3:
      format = GL_RGB;
      break;

    case 4:
      format = GL_RGBA;
      break;
      
    default:
      return EXIT_FAILURE;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

  float rayonBalle = 0.05;
  float posX = -0.3;
  float posY = 0;
  float vitesseX = 0.01;
  float vitesseY = 0.01;

  int loop = 1;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    /* Dessin */
    
    glClearColor(255, 255, 255, 1); // Fond en blanc
    glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(255, 0, 0); // Eléments en rouge
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureBalle);

    /* Affichage de la balle */
    glPushMatrix();
    glTranslatef(posX, posY, 0);
    glScalef(rayonBalle*2, rayonBalle*2, 1);
    draw_circle(1);
    
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    SDL_GL_SwapBuffers();

    if(posX+rayonBalle >= 1-rayonBalle || posX-rayonBalle <= -1+rayonBalle) {
        vitesseX *= -1;
    }
    if(posY+rayonBalle >= 1-rayonBalle || posY-rayonBalle <= -1+rayonBalle) {
        vitesseY *= -1;
    }

    posX += vitesseX;
    posY += vitesseY;

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

  glDeleteTextures(1, &textureBalle);
  SDL_FreeSurface(image);
  
  SDL_Quit();
  
  return EXIT_SUCCESS;
}
