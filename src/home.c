#include "home.h"

int start(){

    SDL_Window *window = SDL_CreateWindow("Acceuil", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HOME_SCREEN_SIZE, HOME_SCREEN_SIZE, 0);
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);

    play_background();

    int posY = 120;
    // int hover = 0;
    SDL_Rect rect_btn_play = {POS_CENTER-120, POS_CENTER+posY, BTN_SIZE, BTN_SIZE};
    SDL_Rect rect_btn_reload = {POS_CENTER, POS_CENTER+posY, BTN_SIZE, BTN_SIZE};
    SDL_Rect rect_btn_quit = {POS_CENTER+120, POS_CENTER+posY, BTN_SIZE, BTN_SIZE};
    SDL_Rect rect_logo = {POS_CENTER-150, POS_CENTER-150, BTN_SIZE+300, BTN_SIZE+100};
    // SDL_Rect rect_hover = {0, 0, BTN_SIZE, BTN_SIZE};
    

    SDL_Surface *s_btn_play = IMG_Load("imgs/play_1.png");
    SDL_Texture *t_btn_play = SDL_CreateTextureFromSurface(render, s_btn_play);
    SDL_FreeSurface(s_btn_play);
    SDL_Surface *s_btn_quit = IMG_Load("imgs/exit_1.png");
    SDL_Texture *t_btn_quit = SDL_CreateTextureFromSurface(render, s_btn_quit);
    SDL_FreeSurface(s_btn_quit);
    SDL_Surface *s_bg = IMG_Load("imgs/ground.png");
    SDL_Texture *t_bg = SDL_CreateTextureFromSurface(render, s_bg);
    SDL_FreeSurface(s_bg);
    SDL_Surface *s_reload = IMG_Load("imgs/reload.png");
    SDL_Texture *t_reload = SDL_CreateTextureFromSurface(render, s_reload);
    SDL_FreeSurface(s_reload);
    SDL_Surface *s_logo = IMG_Load("imgs/logo_jeu.png");
    SDL_Texture *t_logo = SDL_CreateTextureFromSurface(render, s_logo);
    SDL_FreeSurface(s_logo);
    

    int run = 1;
    while(run)
    {

        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderClear(render);

        SDL_Event event;
        SDL_WaitEvent(&event);
        // while(SDL_PollEvent(&event)){

            if(event.type == SDL_QUIT){
                return QUITTER;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    return JOUER;
                    break;
                
                default:
                    break;
                }
                    
            }

            if (event.type == SDL_MOUSEBUTTONUP)
            {
                
                SDL_Point p = {event.button.x, event.button.y};
                if(SDL_PointInRect(&p, &rect_btn_play)){
                    SDL_DestroyRenderer(render);
                    SDL_DestroyWindow(window);
                    return JOUER;
                }
                if(SDL_PointInRect(&p, &rect_btn_quit)){
                    SDL_DestroyRenderer(render);
                    SDL_DestroyWindow(window);
                    return QUITTER;
                    
                }
                if(SDL_PointInRect(&p, &rect_btn_reload)){
                    SDL_DestroyRenderer(render);
                    SDL_DestroyWindow(window);
                    return REJOUER;
                    
                }
                    
            }

            
        // }


        SDL_RenderCopy(render, t_bg, NULL, NULL);
        SDL_RenderCopy(render, t_btn_play, NULL, &rect_btn_play);
        SDL_RenderCopy(render, t_reload, NULL, &rect_btn_reload);
        SDL_RenderCopy(render, t_btn_quit, NULL, &rect_btn_quit);
        SDL_RenderCopy(render, t_logo, NULL, &rect_logo);


       

        SDL_RenderPresent(render);
        SDL_Delay(5);
    }

    SDL_DestroyTexture(t_btn_play);
    SDL_DestroyTexture(t_btn_quit);
    SDL_DestroyTexture(t_bg);
    SDL_DestroyTexture(t_reload);
    SDL_DestroyTexture(t_logo);
    return JOUER;
    
}


