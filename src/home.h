#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gestion_son.h"

#define HOME_SCREEN_SIZE 500
#define BTN_SIZE 100

#define POS_CENTER HOME_SCREEN_SIZE / 2 - BTN_SIZE / 2

#define QUITTER 0
#define JOUER 1
#define REJOUER 2

// Fonction de la fenetre de start
int start();