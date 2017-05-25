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
  unsigned int WINDOW_WIDTH = 500;
  unsigned int WINDOW_HEIGHT = 500;

  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }
   
  setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);

  SDL_WM_SetCaption("Arkanopong", NULL);
  
  //************************************

  // Création des joueurs
  Player joueur1 = createPlayer("j1", 0, 3, ColorXY(0, 255, 0));
  Player joueur2 = createPlayer("j2", 0, 3, ColorXY(0, 0, 255));

  //************************************

  // Création des balles

  Vector initDirection_1 = VectorXY(PointXY(0, 0), PointXY(0, -0.005));
  Point initPoint_1 = PointXY(0, 0.75);
  Vector initDirection_2 = VectorXY(PointXY(0, 0), PointXY(0, 0.005));
  Point initPoint_2 = PointXY(0, -0.75);
  float radius = 0.025;

  Ball myBall1 = createBall(radius, 1, ColorXY(255, 0, 0), initPoint_1, initDirection_1);
  Ball myBall2 = createBall(radius, 1, ColorXY(255, 0, 255), initPoint_2, initDirection_2);

  // IMAGE

  GLuint texture_coeur;
  SDL_Surface *image_coeur = IMG_Load("images/coeur.png");
  if(image_coeur == NULL)
    printf("Erreur, l'image n'a pas pu être chargée\n");
  glGenTextures(1, &texture_coeur);
  glBindTexture(GL_TEXTURE_2D, texture_coeur);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glBindTexture(0, texture_coeur);
  GLenum format;
  switch(image_coeur->format->BytesPerPixel) {
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
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_coeur->w, image_coeur->h, 0, format, GL_UNSIGNED_BYTE, image_coeur->pixels);



  //************************************

  // Variables pour les barres de jeu
  int barre_1_keyPressed_left = 0;
  int barre_1_keyPressed_right = 0;

  int barre_2_keyPressed_left = 0;
  int barre_2_keyPressed_right = 0;

  // BARRES DE JEU
  Bar myBar1 = createBar(0.4, 0.05, 1, joueur1.color, PointXY(0, -0.9));
  Bar myBar2 = createBar(0.4, 0.05, 1, joueur2.color, PointXY(0, 0.9));

  // Vecteurs directeurs de déplacements des barres de jeu
  Vector vector_to_left = VectorXY(PointXY(0.025,0), PointXY(0,0));
  Vector vector_to_right = VectorXY(PointXY(0,0), PointXY(0.025,0));

  //************************************

  // BRIQUES DE JEU
  
  int bricksIterator;

  FILE *brickFile;
  long input_file_size;
  char *brickFileContent;
  int nb_brick_x = -1;
  int nb_brick_y = -1;
  int nb_brick_total;
  int index = 0;
  int *bricksType;

  // Ouverture du fichier
  brickFile = fopen("files/brick.txt", "r");
  if (!brickFile) {
    perror("");
    exit(1);
  }

  // Lecture du fichier et stockage dans un string
  fseek(brickFile, 0, SEEK_END);
  input_file_size = ftell(brickFile);
  rewind(brickFile);
  brickFileContent = malloc(input_file_size * sizeof(char));
  fread(brickFileContent, sizeof(char), input_file_size, brickFile);
  fclose(brickFile);

  // Récupération des paramètres sur les briques
  char *token;
  token = strtok(brickFileContent, " ");
  while (token != NULL) {
    if (index == 0) {
      nb_brick_x = strtol(token, NULL, 10);
    }
    else if (index == 1) {
      nb_brick_y = strtol(token, NULL, 10);
    }
    else {
      if (index == 2) {
        nb_brick_total = nb_brick_x * nb_brick_y;
        bricksType = malloc(nb_brick_total * sizeof(int));
      }
      bricksType[index-2] = strtol(token, NULL, 10);
    }
    token = strtok(NULL, " ");
    index++;
  }

  // Tableau de briques
  Brick tab_bricks[nb_brick_total];

  float hauteur_brick = 0.1;
  float largeur_brick = (float)2/nb_brick_x;
  float brick_position_x = -1.0;
  float brick_position_y = nb_brick_y*hauteur_brick/2;
  int i = 0;
  int j = 0;
  int count = 0;

  // Chargement des textures
  GLuint texture;
  SDL_Surface *image_normal = IMG_Load("images/normal.jpg");
  if(image_normal == NULL) {
    printf("Erreur, l'image normal.jpg n'a pas pu être chargée\n");
  }
  SDL_Surface *image_indestructible = IMG_Load("images/indestructible.jpg");
  if(image_indestructible == NULL) {
    printf("Erreur, l'image indestructible.jpg n'a pas pu être chargée\n");
  }
  SDL_Surface *image_bonus1 = IMG_Load("images/bonus_1.jpg");
  if(image_bonus1 == NULL) {
    printf("Erreur, l'image bonus_1.jpg n'a pas pu être chargée\n");
  }
  SDL_Surface *image_bonus2 = IMG_Load("images/bonus_2.jpg");
  if(image_bonus2 == NULL) {
    printf("Erreur, l'image bonus_2.jpg n'a pas pu être chargée\n");
  }
  SDL_Surface *image_bonus3 = IMG_Load("images/bonus_3.jpg");
  if(image_bonus3 == NULL) {
    printf("Erreur, l'image bonus_3.jpg n'a pas pu être chargée\n");
  }
  SDL_Surface *image_bonus4 = IMG_Load("images/bonus_4.jpg");
  if(image_bonus4 == NULL) {
    printf("Erreur, l'image bonus_4.jpg n'a pas pu être chargée\n");
  }

  for (i = 0; i < nb_brick_x; i++) {
    for (j = 0; j < nb_brick_y; j++) {
        switch(bricksType[count]) {
          case 0: // Normal
              glGenTextures(1, &texture);
              glBindTexture(GL_TEXTURE_2D, texture);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
              glBindTexture(0, texture);

              switch(image_normal->format->BytesPerPixel) {
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
              glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_normal->w, image_normal->h, 0, format, GL_UNSIGNED_BYTE, image_normal->pixels);
              break;
          case 1: // Indestructible
              glGenTextures(1, &texture);
              glBindTexture(GL_TEXTURE_2D, texture);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
              glBindTexture(0, texture);

              switch(image_indestructible->format->BytesPerPixel) {
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
              glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_indestructible->w, image_indestructible->h, 0, format, GL_UNSIGNED_BYTE, image_indestructible->pixels);
              break;
          case 2: // Bonus 1 : agrandissement de la barre
              
              glGenTextures(1, &texture);
              glBindTexture(GL_TEXTURE_2D, texture);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
              glBindTexture(0, texture);

              switch(image_bonus1->format->BytesPerPixel) {
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
              glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_bonus1->w, image_bonus1->h, 0, format, GL_UNSIGNED_BYTE, image_bonus1->pixels);
              break;
          case 3: // Bonus 2 : ajout d'un point de vie
              glGenTextures(1, &texture);
              glBindTexture(GL_TEXTURE_2D, texture);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
              glBindTexture(0, texture);

              switch(image_bonus2->format->BytesPerPixel) {
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
              glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_bonus2->w, image_bonus2->h, 0, format, GL_UNSIGNED_BYTE, image_bonus2->pixels);
              break;
          case 4: // Bonus 3 : suppression d'un point de vie à l'adversaire
              glGenTextures(1, &texture);
              glBindTexture(GL_TEXTURE_2D, texture);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
              glBindTexture(0, texture);

              switch(image_bonus3->format->BytesPerPixel) {
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
              glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_bonus3->w, image_bonus3->h, 0, format, GL_UNSIGNED_BYTE, image_bonus3->pixels);
              break;
          case 5: // Bonus 4 : ajout d'une 3e balle
              glGenTextures(1, &texture);
              glBindTexture(GL_TEXTURE_2D, texture);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
              glBindTexture(0, texture);

              switch(image_bonus4->format->BytesPerPixel) {
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
              glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_bonus4->w, image_bonus4->h, 0, format, GL_UNSIGNED_BYTE, image_bonus4->pixels);
              break;
          default:
              glGenTextures(1, &texture);
              glBindTexture(GL_TEXTURE_2D, texture);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
              glBindTexture(0, texture);

              switch(image_normal->format->BytesPerPixel) {
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
              glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_normal->w, image_normal->h, 0, format, GL_UNSIGNED_BYTE, image_normal->pixels);
              break;
        }
      Point position_brick = PointXY(brick_position_x + largeur_brick * i, brick_position_y - hauteur_brick * j);
      tab_bricks[count] = createBrick(largeur_brick, hauteur_brick, 1, bricksType[count], texture, position_brick);
      count++;
    }
  }

  printf("-- %.3f\n",(tab_bricks[0].position.y-tab_bricks[0].longueur));

  //printf("-- %.3f -- %.3f\n", hauteur_brick, tab_bricks[2].position.x);
  //affiche_tab(bricksType, nb_brick_total);

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
    
    glClearColor(0.25, 0.24, 0.30, 1); // Fond en blanc
    glClear(GL_COLOR_BUFFER_BIT);

    // Reperes
    //drawReperes();

    /* Affichage de la balle */
    drawBall(myBall1);
    drawBall(myBall2);

    /* Affichage des barres de déplacement */
    drawBar(myBar1);
    drawBar(myBar2);

    /* Affichage des briques */
    for (count = 0; count < nb_brick_total; count++) {
      draw_brick(tab_bricks[count]);
    }

    /* Affichage des points de vie */
    if(joueur1.life != 0 && joueur2.life != 0)
      draw_coeur(texture_coeur, joueur1.life, joueur2.life);
    else {
      myBall1 = createBall(radius, 1, ColorXY(255, 0, 0), initPoint_1, initDirection_1);
      myBall2 = createBall(radius, 1, ColorXY(255, 0, 255), initPoint_2, initDirection_2);
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
      myBall1 = createBall(radius, 1, ColorXY(255, 0, 0), initPoint_1, initDirection_1);
    }
    if(myBall1.position.y-myBall1.radius <= -1) {
      joueur1.life--;
      myBall1 = createBall(radius, 1, ColorXY(255, 0, 0), initPoint_1, initDirection_1);
    }

    if(myBall2.position.x+myBall2.radius >= 1 || myBall2.position.x-myBall2.radius <= -1) {
        myBall2.vector.x *= -1;
    }
    if(myBall2.position.y+myBall2.radius >= 1) {
      joueur2.life--;
      myBall2 = createBall(radius, 1, ColorXY(255, 0, 255), initPoint_2, initDirection_2);
    }
    if(myBall2.position.y-myBall2.radius <= -1) {
      joueur1.life--;
      myBall2 = createBall(radius, 1, ColorXY(255, 0, 255), initPoint_2, initDirection_2);
    }

    collisionWithBar(&myBall1, myBar1, 1);
    collisionWithBar(&myBall1, myBar2, 0);
    collisionWithBar(&myBall2, myBar1, 1);
    collisionWithBar(&myBall2, myBar2, 0);

    //collisionWithBrick(&myBall1, &tab_bricks[0]);

    for (bricksIterator = 0; bricksIterator < nb_brick_total; bricksIterator++) {
      collisionWithBrick(&myBall1, &tab_bricks[bricksIterator], &myBar1, &myBar2, &joueur1, &joueur2);
      collisionWithBrick(&myBall2, &tab_bricks[bricksIterator], &myBar1, &myBar2, &joueur1, &joueur2);
    }

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
