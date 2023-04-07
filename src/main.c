#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "consts.h"
#include "gestion_cases.h"
#include "gestion_window.h"
#include "couleurs.h"
#include "home.h"
#include "gestion_son.h"
#include "over.h"


int jeu(int cont){

// CREATION GLOBALE DE LA FENETRE ET DU RENDU BLANC
    SDL_Window *window = NULL;
    SDL_Renderer *rendu = NULL;
    create_window(&window, &rendu, WINDOW_SIZE, WINDOW_SIZE);

// donnons une icone a notre application 
    SDL_Surface *icon = IMG_Load("imgs/p11.png");
    SDL_SetWindowIcon(window, icon);


// HOME

// CREATION ET DESSIN INITIAL DU TABLEAU DE CASES
    Case cases[NOMBRE_CASES];
    init_cases(cases);
// CASE SELECTIONNE GLOBALEMENT
    Case selected_case;
// PREMIER JOUEUR GLOBAL
    int JOUEUR = -JOUEUR_BAS;

    if (cont)
    {
        get_stat(cases);
    }

    


    // --------------------------------------------------------------------
    


    SDL_Event event;
    int run = 1;
// BOUCLE DU PROGRAMME !!!
    while (run)
    {
// ON ATTEND LES EVENEMENTS...!!!
        SDL_WaitEvent(&event);
        // while(SDL_PollEvent(&event)){

            // Lorsquon decide de quitter
            if(event.type == SDL_QUIT){
                run = 0;
                SDL_DestroyRenderer(rendu);
                SDL_DestroyWindow(window);
            }

            // Lorsqu'on appui sur la souris
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
               
                
                SDL_Point current_point = {event.button.x, event.button.y};
               //------------------------
                for (size_t i = 0; i < NOMBRE_CASES; i++)
                {
              
                    if (SDL_PointInRect(&current_point, &cases[i].rect))
                    {

                        if (cases[i].selection_type != SELECTED && ( cases[i].state != TARGET && cases[i].state != TARGET * 2))
                        {   

                            // s'il s'agit de n'importe quelle case
                            cases[i].selection_type = SELECTED;
                            selected_case = cases[i];
                            reset_targets(cases);

                            // SI il s'agit d'un joueur simple
                            if(cases[i].state == JOUEUR){
                                set_targets(cases, cases[i]);
                                set_pick(cases, cases[i]);
                            }

                             // SI il s'agit d'une dame
                            if(cases[i].state == JOUEUR*2){
                                set_targets_dames(cases, cases[i]);
                                set_pick_dames(cases, cases[i]);
                            }
   
                        }                                  
                    }
                    else{
                        cases[i].selection_type = NONE;
                    }      
                }
                //-------------------------------------------


                //DEPLACEMENT DU PION
                for (size_t i = 0; i < NOMBRE_CASES; i++)
                {
                    if (SDL_PointInRect(&current_point, &cases[i].rect)){
                        
                        if(cases[i].state == TARGET/*case verte*/ || cases[i].state == TARGET * 2 /*case rouge*/){
                            JOUEUR = deplacement(JOUEUR, cases, selected_case, cases[i]);
                            // ON RESET TOUTES LES TARGETS
                            reset_targets(cases);   
                        }
                        
                    }
             
                }
                //-------------------------------------------
                save_stat(cases);
                if(verif_nbre_pion(cases) == NOIR_GAGNE){
                    printf("Les noirs ont gagné \n");
                    run = 0;
                    SDL_DestroyRenderer(rendu);
                    SDL_DestroyWindow(window);
                    game_over(JOUEUR_HAUT);

            
                }
                    

                if(verif_nbre_pion(cases) == BLANC_GAGNE){
                    printf("Les blancs ont gagné \n");
                    run = 0;
                    SDL_DestroyRenderer(rendu);
                    SDL_DestroyWindow(window);
                    game_over(JOUEUR_BAS);
                    
                }
                      
            }

    // FONCTION DE HOVER
            if(event.type == SDL_MOUSEMOTION){            
                SDL_Point current_point = {event.motion.x, event.motion.y};
                    hover(&current_point, cases);     
                }


    // APPUIS SUR UNE TOUCHE
        if(event.type == SDL_KEYDOWN){
            if (event.key.keysym.sym == SDLK_F5)
            {
                save_stat(cases);
            }

            if (event.key.keysym.sym == SDLK_F7){
                get_stat(cases);
            }
            
        }
        
    // }
            // ON DESSINE LES CASES ET ON PRESENTE LE RENDU
            draw_cases(&rendu, cases);
            SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);



            SDL_RenderPresent(rendu);

    // UN PEU DE FPS
    SDL_Delay(1);

}
    return EXIT_SUCCESS;

}


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING != -1);
    // init audio
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    TTF_Init();
    

    
    int game = start();
    while (game)
    {
        
        switch (game)
        {
        case JOUER:
            jeu(1);
            break;
        
        case REJOUER:
            jeu(0);
            break;
    
        default:
            continue;
        }
        game = start();
    }
    


 

    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;

}



