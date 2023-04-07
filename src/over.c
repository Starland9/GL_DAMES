#include "over.h"


int game_over(int joueur){

    SDL_Window *window = SDL_CreateWindow("Resultats", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVER_SCREEN_SIZE, OVER_SCREEN_SIZE, 0);
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);

    SDL_Rect rect_logo = {150-125, 150, 250, 132};
    SDL_Rect rect_img = {150-64, 32, 128, 128};
    

    SDL_Surface *s_logo = IMG_Load("imgs/logo_victoire.png");
    SDL_Texture *t_logo = SDL_CreateTextureFromSurface(render, s_logo);
    SDL_FreeSurface(s_logo);

    SDL_Surface *s_bg = IMG_Load("imgs/ground.png");
    SDL_Texture *t_bg = SDL_CreateTextureFromSurface(render, s_bg);
    SDL_FreeSurface(s_bg);

    SDL_Surface *s_pion;
    if (joueur == JOUEUR_BAS)
        s_pion = IMG_Load("imgs/p11.png");
    else
        s_pion = IMG_Load("imgs/p22.png");
    SDL_Texture *t_pion = SDL_CreateTextureFromSurface(render, s_pion);
    SDL_FreeSurface(s_pion);
    

    int r = 1;
    while (r)
    {

        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderClear(render);

        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                r = 0;
                SDL_DestroyRenderer(render);
                SDL_DestroyWindow(window);

            }
        }

        SDL_RenderCopy(render, t_bg, NULL, NULL);
        SDL_RenderCopy(render, t_logo, NULL, &rect_logo);
        SDL_RenderCopy(render, t_pion, NULL, &rect_img);



        SDL_RenderPresent(render);
    }
    

    return EXIT_SUCCESS;
    
}