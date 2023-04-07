#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_SIZE 600

#define CASE_SIZE WINDOW_SIZE / 10


// LES DIFFERENTS STATES D'UNE CASE 
#define LIBRE 5
#define OCCUPE_1 -1
#define OCCUPE_2 1
#define TARGET 3
#define DAME_1 -2
#define DAME_2 2

// LES DIFFERENTS TYPES DE SELECTION D'UNE CASE
#define SELECTED 0
#define HOVERED 1
#define NONE -1


// LE NOMBRE DE RECTANGLES
#define NOMBRE_CASES 50


// LES JOUEURS 
#define JOUEUR_BAS -1
#define JOUEUR_HAUT 1
#define CPU 0

// LES AUTRES
#define PADDING 10


// LES DIFFERENTES POSITION DES CASES
#define HAUT_GAUCHE -2
#define HAUT_DROITE -1
#define BAS_GAUCHE 1
#define BAS_DROITE 2


// MES FONCTION DES BOUTTONS
#define START 1
#define QUIT 0


// Autre pour la bouf
#define OUI 1
#define NON 0


#define BLANC_GAGNE 1
#define NOIR_GAGNE 0