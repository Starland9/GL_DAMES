#include <stdio.h>
#include <SDL2/SDL.h>

#include "consts.h"
#include "gestion_cases.h"



// CREATION DU WINDOW ET ATTRIBUTION DU RENDERER AVEC UNE COULEUR BLANCHE
void create_window(SDL_Window **win, SDL_Renderer **rendu, int W, int H){
    

    SDL_Window *window = SDL_CreateWindow("GL* DAMES", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H+64,
                                         SDL_WINDOW_SHOWN);
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 1);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    *win = window;
    *rendu = renderer;

}



