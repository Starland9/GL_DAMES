#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include "consts.h"
#include "gestion_cases.h"
#include "gestion_son.h"



// ----------------------------------------------------------------------------------------------
Case CASE_BOUFFE;
Case CASE_TARGET_BOUFFE;

Case CASES_BOUFS[10];
int TARGET_VALUE = TARGET;
// Tableau contenant les cases qui declanchent le mangement du roi
Case CASES_TARGETS_BOUFS[10];

// LES NOMBRES DE PIONS
int NBRE_BLANC = 0;
int NBRE_NOIR = 0;
// bouffe
int BOUFFE = 0;
// PLUS POUR LES DAMES
// TABLEAU CONTENANT LES PIONS A BOUFFER !!!
int current_case_tchop = 0;
int current_case_target = 0;
// ----------------------------------------------------------------------------------------------




// FONCTION QUI REND UN PION DAME
void set_dame(Case cases[], Case my_case);

// FONCTION QUI CREER DIRECTEMENT UNE TEXTURE IMAGE
SDL_Texture* load_img(SDL_Renderer **rendu, const char *file);

// FONCTION QUI DETERMINE SI DEUX CASES SONT ADJASCENTES
int adj_cases(Case case1, Case case2);

// FONCTION QUI DETERMINE SI UNE CASE EST DERRIERE LE PION SELECTIONNE
int deriere_pion(Case selected_case, Case target_case);

// FONCTION QUI RENVOI LA POSITION DE TARGET_CASE PAR RAPPORT A SELECTED_CASE
int get_pos_cases(Case selected_case, Case target_case);

// // FONCTION QUI DEVOILE LES MANGEMENTS !!!
// int set_pick(Case cases[], Case selected_case);

// FONCTION QUI CHANGE LE STATUT D'UNE CASE
void set_stat(Case cases[], Case my_case, int new_stat);

// FONCTION DE BOUFFE
void bouffe(Case cases[], Case my_case, int BOUFFE);

// FONCTION QUI DIT SI DEUX CASES SONT EQUIVALANTES
int equal_cases(Case case1, Case case2);


// FONCTION QUI TARGET UN PION A UNE POSITION DONNEE
void target_at_pos(Case cases[], Case selected_case, int position);



// FONCTION QUI RECOLORIE TOUTES LES CASES
void recolor_cases(SDL_Renderer *rendu, Case cases[]){
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        SDL_RenderFillRect(rendu, &cases[i].rect);
    }
    
}

SDL_Color blanc = {255, 255, 255, 255};

// PREMIERE FONCTION QUI INITIALISE LES CASES, LEUR ATTRIBUT, LEUR OCUPATION ET LEUR POSITION PAR DEFAUT
int temp_passe = 0;
int s=0, m=0;
void init_cases(Case cases[]){
// quelques initialisations
int state = 0;
int current_case = 0;
s = 0, m = 0;

    for (size_t c = 0; c < WINDOW_SIZE; c+=CASE_SIZE)
    {
        state++;
        for (size_t l = 0; l < WINDOW_SIZE; l+=CASE_SIZE)
        {
            if(state % 2 == 0){
                SDL_Rect rect = {l, c, CASE_SIZE, CASE_SIZE};
                Case my_case = {rect, LIBRE, NONE};

                if(c < CASE_SIZE * 4){
                    my_case.state = OCCUPE_1;
                    NBRE_BLANC++;
                }
                if(c >= (WINDOW_SIZE - CASE_SIZE*4)){
                    my_case.state = OCCUPE_2;
                    NBRE_NOIR++;
                }

                // on rempli notre tableau de cases
                cases[current_case] = my_case;
                current_case++;  
            }
            state++;
        }  
    }
    
}


//FONCTION QUI DESSINE LE TABLEAU DE CASES SUR LE RENDU 
void draw_cases(SDL_Renderer **rendu, Case cases[]){
// LOAD DE TOUTES LES IMAGES DU JEU
    SDL_Texture *p2 = load_img(rendu, "imgs/p11.png");
    SDL_Texture *p1 = load_img(rendu, "imgs/p22.png");
    SDL_Texture *d2 = load_img(rendu, "imgs/d11.png");
    SDL_Texture *d1 = load_img(rendu, "imgs/d22.png");

    SDL_Texture *selector = load_img(rendu, "imgs/pan2.png");
    SDL_Texture *ground = load_img(rendu, "imgs/ground.png");


    SDL_SetRenderDrawBlendMode(*rendu, SDL_BLENDMODE_BLEND);
    // SDL_SetRenderDrawColor(*rendu, 220, 250, 210, 150);
    SDL_RenderClear(*rendu);
    SDL_RenderCopy(*rendu, ground, NULL, NULL);

    char nbre1[5], nbre2[5], c_sec[10];
    
    if(SDL_GetTicks() - temp_passe > 1000){
        temp_passe = SDL_GetTicks();
        s++;
        if(s > 60){
            s = 0;
            m++;
        }
        
    }
    
    sprintf(nbre1, ": %d", NBRE_BLANC);
    sprintf(nbre2, ": %d", NBRE_NOIR);

    sprintf(c_sec, "%d:%d", m, s);

    // Gestion de la barre d'outil du jeu
    SDL_Rect barre_outil = {0, WINDOW_SIZE, WINDOW_SIZE, 64};
    TTF_Font *font = TTF_OpenFont("fonts/f2.ttf", 50);
    SDL_Rect r1 = {100, WINDOW_SIZE+7, 60, 40};
    SDL_Rect img_r1 = {32, WINDOW_SIZE+7, 45, 45};
    SDL_Surface *s1 = TTF_RenderText_Blended(font, nbre1, blanc);
    SDL_Texture *t1 = SDL_CreateTextureFromSurface(*rendu, s1);

    SDL_Rect r2 = {WINDOW_SIZE-150+20, WINDOW_SIZE+7, 60, 40};
    SDL_Rect img_r2 = {WINDOW_SIZE-150-64-5+20, WINDOW_SIZE+7, 45, 45};
    SDL_Surface *s2 = TTF_RenderText_Blended(font, nbre2, blanc);
    SDL_Texture *t2 = SDL_CreateTextureFromSurface(*rendu, s2);

    SDL_Rect rect_time = {WINDOW_SIZE/2-40, WINDOW_SIZE+18, 60, 30};
    // SDL_Rect img_rect_time = {WINDOW_SIZE-150-64-5+20, WINDOW_SIZE+7, 50, 50};
    SDL_Surface *s_time = TTF_RenderText_Blended(font, c_sec, blanc);
    SDL_Texture *t_time = SDL_CreateTextureFromSurface(*rendu, s_time);
    SDL_FreeSurface(s_time);
    SDL_FreeSurface(s1);
    SDL_FreeSurface(s2);
    TTF_CloseFont(font);

    
    SDL_RenderFillRect(*rendu, &barre_outil);
    // Gestion des ecriture sur la barre d'outil
    SDL_RenderCopy(*rendu, t1, NULL, &r1);
    SDL_RenderCopy(*rendu, t2, NULL, &r2);
    SDL_RenderCopy(*rendu, p2, NULL, &img_r1);
    SDL_RenderCopy(*rendu, p1, NULL, &img_r2);
    SDL_RenderCopy(*rendu, t_time, NULL, &rect_time);


    int state = 0;
    int currect_case = 0;
    for (size_t c = 0; c < WINDOW_SIZE; c+=CASE_SIZE)
    {
        state++;
        for (size_t l = 0; l < WINDOW_SIZE; l+=CASE_SIZE)
        {
            if(state % 2 == 0){
                SDL_Rect current_rect = cases[currect_case].rect;

                // rectangle de l'affichage des pions
                SDL_Rect rect_img = cases[currect_case].rect;
                rect_img.h -= PADDING;
                rect_img.w -= PADDING;
                rect_img.x += PADDING/2;
                rect_img.y += PADDING/2;

                
                SDL_SetRenderDrawColor(*rendu, 0, 0, 0, 110);
                SDL_RenderCopy(*rendu, ground, NULL, &current_rect);
                SDL_RenderFillRect(*rendu, &current_rect);
                    
                if(cases[currect_case].selection_type == SELECTED || cases[currect_case].selection_type == HOVERED){
                    SDL_RenderCopy(*rendu, selector, NULL, &current_rect);
                }

                if(cases[currect_case].state == OCCUPE_1){
                    SDL_RenderCopy(*rendu, p1, NULL, &rect_img);
                }

                if(cases[currect_case].state == OCCUPE_2){
                    SDL_RenderCopy(*rendu, p2, NULL, &rect_img);
                
                }

                if(cases[currect_case].state == DAME_1){
                    SDL_RenderCopy(*rendu, d1, NULL, &rect_img);
                }

                if(cases[currect_case].state == DAME_2){
                    SDL_RenderCopy(*rendu, d2, NULL, &rect_img);
                
                }

                if(cases[currect_case].state == TARGET){
                    SDL_SetRenderDrawColor(*rendu, 0, 255, 0, 70);
                    SDL_RenderFillRect(*rendu, &current_rect);
                    // SDL_RenderCopy(*rendu, selector, NULL, &current_rect);
                }

                if(cases[currect_case].state == TARGET * 2){
                    SDL_SetRenderDrawColor(*rendu, 255, 0, 0, 70);
                    SDL_RenderFillRect(*rendu, &current_rect);
                    // SDL_RenderCopy(*rendu, selector, NULL, &current_rect);
                }


                currect_case++;   
            }
            state++;
        }  
    }

    SDL_DestroyTexture(ground);
    SDL_DestroyTexture(selector);
    SDL_DestroyTexture(d1);
    SDL_DestroyTexture(d2);
    SDL_DestroyTexture(p1);
    SDL_DestroyTexture(p2);
    SDL_DestroyTexture(t1);
    SDL_DestroyTexture(t2);
}




// FONCTION QUI CREER DIRECTEMENT UNE TEXTURE IMAGE
SDL_Texture* load_img(SDL_Renderer **rendu, const char *file){
    SDL_Surface *sur = IMG_Load(file);
    SDL_Texture *t_sur = SDL_CreateTextureFromSurface(*rendu, sur);
    SDL_FreeSurface(sur);
    return t_sur;
}


// FONCTION HOVER SUR UNE CASE
void hover(SDL_Point *point, Case cases[]){
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        if(SDL_PointInRect(point, &cases[i].rect))
        {
            if(cases[i].selection_type == SELECTED)
                continue;
            else
            {
                cases[i].selection_type = HOVERED;
                
            }
                
        }
        else{
            if(cases[i].selection_type == SELECTED)
                continue;
            else{
                cases[i].selection_type = NONE;
            }
                
        }
        }
        

}


// FONCTION QUI TROUVE LES TARGET DE my_case DANS LE TABLEAU cases[]
void set_targets(Case cases[], Case my_case){

    // si my_case est selectionnée ou elle est une target
    if(my_case.selection_type == SELECTED || my_case.state == TARGET){
        // on parcours le tableau de cases
        for (size_t i = 0; i < NOMBRE_CASES; i++){
            // lorsquon trouve une case qui est adjacente a my_case
            if( adj_cases(my_case, cases[i]) ){
                // si la case trouvée n'est pas deriere la my_case et la case est libre
                if(!deriere_pion(my_case, cases[i]) && cases[i].state == LIBRE){
                        cases[i].state = TARGET;
                        play_sound("audio/click.wav", 0);

                    }
                    
                    
                }
                // set_targets(cases, cases[i]);
                
            }
        }
    }

// FONCTION QUI REND UN PION DAME
void set_dame(Case cases[], Case my_case){
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        if(cases[i].state == OCCUPE_2 && cases[i].rect.y == 0){
            set_stat(cases, cases[i], DAME_2);
        }

        if(cases[i].state == OCCUPE_1 && cases[i].rect.y == WINDOW_SIZE - cases[i].rect.h){
            set_stat(cases, cases[i], DAME_1);
        }
    
}
}


// FONCTION QUI DETERMINE SI DEUX CASES SONT ADJASCENTES
int adj_cases(Case case1, Case case2){

    // on cree un carre plus gros que la case1 
    SDL_Rect tmp_rect;
    tmp_rect.x = case1.rect.x - 5;
    tmp_rect.y = case1.rect.y - 5;
    tmp_rect.w = case1.rect.w + 20;
    tmp_rect.h = case1.rect.h + 20;

    // si la case2 est en intersection avec la grosse case alors la case2 est adjacente
    if(SDL_HasIntersection(&tmp_rect, &case2.rect) && !equal_cases(case1, case2)){
        return 1;
    }
    else{
        return 0;
    }

}


// FONCTION QUI RESET TOUTES LES TARGETS
void reset_targets(Case cases[]){
    // on effectu le parcours de nos cases
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        // si la case courante est en target, on la remet a libre
        if(cases[i].state == TARGET || cases[i].state == TARGET * 2){
            cases[i].state = LIBRE;
        


}
}
}

//Fonction qui reset les cases a bouffe
void reset_boufs(Case cases[]){
        // on effectu le parcours de nos cases
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        if(cases[i].to_bouf == OUI){
            cases[i].to_bouf = NON;
        }  
    }

}


// FONCTION QUI RESET TOUTES LES TARGETS QUI NE SONT PAS ROUGE !!
void reset_targets_red(Case cases[]){
    // on effectu le parcours de nos cases
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        // si la case courante est en target, on la remet a libre
        if(cases[i].state == TARGET && cases[i].state != TARGET * 2){
            cases[i].state = LIBRE;
        }  

}
}

// FONCTION QUI DIT SI DEUX CASES SONT EQUIVALANTES
int equal_cases(Case case1, Case case2){
    if (case1.rect.x == case2.rect.x && case1.rect.y == case2.rect.y)
    {
        return 1;
    }
    else{
        return 0;
    }   
}

// FONCTION DE DEPLACEMENT DU PION de de_case vers la case vers_case
int deplacement(int JOUEUR, Case cases[], Case de_case, Case vers_case){
    int statut_de_case = de_case.state;
    set_stat(cases, de_case, LIBRE);
    set_stat(cases, vers_case, statut_de_case);

    if( (BOUFFE && equal_cases(CASE_TARGET_BOUFFE, vers_case) )/* || ( BOUFFE && vers_case.state == TARGET * 2)*/){
        Case bouf = CASE_BOUFFE;
        bouffe(cases, bouf, BOUFFE);
        BOUFFE = 0;
    }

    bouf_of_dame(cases);
    // si les circonstantes sont bien comme il faut, le pion devient dame
    set_dame(cases, vers_case);
    // on passe la main a l'autre joueur
    return -JOUEUR;
   
}


// FONCTION QUI DETERMINE SI UNE CASE EST DERRIERE LE PION SELECTIONNE
int deriere_pion(Case selected_case, Case target_case){
    if(selected_case.state == OCCUPE_2){
        if(target_case.rect.y > selected_case.rect.y && target_case.state != -selected_case.state){
            return 1;
        }
    }

    else if(selected_case.state == OCCUPE_1){
        if(target_case.rect.y < selected_case.rect.y && target_case.state != -selected_case.state){
            return 1;
        }
    }

    return 0;

}


    
// FONCTION QUI DEVOILE LES MANGEMENTS !!!
int set_pick(Case cases[], Case selected_case){
BOUFFE = 0;
// on parcours toutes les cases
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        // Si la case sur laquelle on est est adjacente a la case sur laquelle on a clické et la case est un adversaire
        if( adj_cases(selected_case, cases[i]) && ( cases[i].state == -selected_case.state || cases[i].state == -selected_case.state * 2 )){
              // IL YA TCHOP
            target_at_pos(cases, cases[i], get_pos_cases(selected_case, cases[i]));
            return 1;
            }
            }
            return 0;
        }


// FONCTION QUI RENVOI LA POSITION DE TARGET_CASE PAR RAPPORT A SELECTED_CASE
int get_pos_cases(Case selected_case, Case target_case){

        // Si la case sur laquelle on est est adjacente a la selected_case
        if( adj_cases(selected_case, target_case)){
            
            // si la adjacente est au dessus
            if(target_case.rect.y < selected_case.rect.y){
                // si la case est a gauche
                if(target_case.rect.x < selected_case.rect.x){
                    return HAUT_GAUCHE;
                    
                }
                // si la case est a droite
                if(target_case.rect.x > selected_case.rect.x){
                    return HAUT_DROITE;  
                }

            }

            // si la case adj est en dessous
            if(target_case.rect.y > selected_case.rect.y){
                // si la case est a gauche
                if(target_case.rect.x < selected_case.rect.x){
                    return BAS_GAUCHE;  
                }
                // si la case est a droite
                if(target_case.rect.x > selected_case.rect.x){
                    return BAS_DROITE;
                }
            }

        }
        return 0;
    }


// FONCTION QUI TARGET UN PION A UNE POSITION DONNEE
void target_at_pos(Case cases[], Case selected_case, int position){

    // on parcours
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        // si la case courante est adj a la case selectionnée
        if( adj_cases(selected_case, cases[i]) ){
              
            // si la case courante a la position donnée par rapport a la case selectionnée
             if(get_pos_cases(selected_case, cases[i]) == position){
                 // si la case courante est libre, on reset toutes les targets et on target juste elle et la bouf passe a 1
                 if(cases[i].state == LIBRE){
                    reset_targets(cases);
                    cases[i].state = TARGET*2;
                    BOUFFE = 1;
                    CASE_BOUFFE = selected_case;
                    CASE_TARGET_BOUFFE = cases[i];
        
                 }
                 
                }
                
             }
        }  
    }

// FONCTION QUI CHANGE LE STATUT D'UNE CASE
void set_stat(Case cases[], Case my_case, int new_stat){

    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        if(cases[i].rect.x == my_case.rect.x && cases[i].rect.y == my_case.rect.y){
            cases[i].state = new_stat;
            break;
        }
    }
    
}


// FONCTION DE BOUFFE
void bouffe(Case cases[], Case my_case, int BOUFFE){
    if(BOUFFE){

        set_stat(cases, my_case, LIBRE);

    }


}
   
    
 

// ----------------------------------------------------------------------------
//--------------GESTION DES DAMES-------------------------------------------
// ------------------------------------------------------------------------

// case selectionnee globalement
Case GLOBAL_SELECTED_CASE;

// Le nombre de pion qui bloc le target du dame
int MAX_PION = 2;

// variable qui sert a definir s'il faut effacer les pions non rouge
int RESET_RED = 0;


// FONCTION QUI DONNE LES TARGETS DES DAMES
void set_targets_dames(Case cases[], Case my_case){
    TARGET_VALUE = TARGET;
    GLOBAL_SELECTED_CASE = my_case;
    MAX_PION = 2;
    reset_boufs(cases);
 

        for (size_t i = 0; i < NOMBRE_CASES; i++){
            // lorsquon trouve une case qui est adjacente a my_case
                target_at_pos_dames(cases, my_case, -get_pos_cases(cases[i], my_case));
            }
        // on efface les targets non rouges
        if(RESET_RED){
            reset_targets_red(cases);
            RESET_RED = 0;
        }

}

//Fonction qui verifie si une case est seule afin de la manger
int possible_bouf(Case my_case, Case cases[]){
    int p = 1;
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        
        if(adj_cases(my_case, cases[i]) && ( cases[i].state == OCCUPE_1 || cases[i].state == OCCUPE_2 ||
                        cases[i].state == DAME_1 || cases[i].state == DAME_2 )){
            if(adj_cases(my_case, cases[i]) && equal_cases(cases[i], GLOBAL_SELECTED_CASE)){
                return 1;
            }
            p = 0;
                
        }
    }
    return p;
}




// FONCTION QUI DONNE LES TARGETS DES DAMES SUR LA POSITION DONNEE
void target_at_pos_dames(Case cases[], Case selected_case, int position){
    // VALEUR DE LA TARGET EN FONCTION DE LA POSITION DES SELECTEURS
        // on parcours
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        // si la case courante est adj a la case selectionnée
        if( adj_cases(selected_case, cases[i]) ){
            // si la case courante a la position donnée par rapport a la case selectionnée
             if(get_pos_cases(selected_case, cases[i]) == position){
                 // si la case courante est libre, on target juste elle
                 // On ne prend que les cases qui sont adversaire au roi
                if(cases[i].state != GLOBAL_SELECTED_CASE.state && cases[i].state != GLOBAL_SELECTED_CASE.state / 2){

                   // si la case est occupe,
                    if(cases[i].state != LIBRE){

                        if(GLOBAL_SELECTED_CASE.state == -cases[i].state || GLOBAL_SELECTED_CASE.state == -cases[i].state * 2){
                                TARGET_VALUE *= 2;
                                if (possible_bouf(cases[i], cases))
                                {
                                    cases[i].to_bouf = OUI;
                                    RESET_RED = 1;
                                }
                                target_at_pos_dames(cases, cases[i], position);
                        }
                        
                    }
                    else{
                            cases[i].state = TARGET_VALUE;
                            target_at_pos_dames(cases, cases[i], position);
                            TARGET_VALUE = TARGET;
                        }

                        
                        
                    }
                    
                    
                }
                 }
                

}
        
    }
       

   




// FONCTION QUI DEVOILE LES MANGEMENTS DES DAMES !!!
int .set_pick_dames(Case cases[], Case selected_case){
BOUFFE = 0;
// on parcours toutes les cases
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        // Si la case sur laquelle on est est adjacente a la case sur laquelle on a clické et la case est un adversaire
        if( adj_cases(selected_case, cases[i]) && ( cases[i].state == -selected_case.state || cases[i].state == -selected_case.state / 2
        || cases[i].state == -selected_case.state * 2 )){
              // IL YA TCHOP
            target_at_pos_dames(cases, cases[i], get_pos_cases(selected_case, cases[i]));
            return 1;
            }
            }
            return 0;
        }

// FONCTION QUI GERE LES CHOSES AUTOMATIQUEMENT SUR LE DAMIER
// FONCTION TRES COMPLEXE LANDRY!!!!!!!
// void auto_dame(Case cases[]){
//     for (size_t i = 0; i < NOMBRE_CASES; i++){
//         printf("%d", cases[i].selection_type);
//     }
// }


// FONCTION QUI REND LIBRE TOUTES LES CASES BOUFEES PAR LA DAME
void bouf_of_dame(Case cases[]){
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        if(cases[i].to_bouf == OUI){
            cases[i].state = LIBRE;
        } 
    }    
}


// FONCTION QUI REINITIALISE TOUTES LES CASES DE BOUF
void reset_cases_bouf_dame(Case cases_bouf[]){
    SDL_Rect r = {1, 1, 0, 0};
    Case c = {r, 0, 0};
    for (size_t i = 0; i < 10; i++)
    {
        cases_bouf[i] = c;
    }
    
}

// FONCTION QUI REINITIALISE LE TABLEAU CONTENANT LES CASES QUI DOIVENT DECLANCHER LE MANGEMENT DU ROI
void reset_cases_target_boufs(){
    SDL_Rect r = {1, 1, 0, 0};
    Case c = {r, 0, 0};
    for (size_t i = 0; i < 10; i++)
    {
        CASES_TARGETS_BOUFS[i] = c;
    }

}

// FONCTION QUI VERIFIE SI LA CASE CLIQUE EST LA BONNE POUR DECLANCHER LA BOUFE DU ROI
int in_cases_target_bouf(Case my_case){
    int ok = 0;
    for (size_t i = 0; i < 10; i++)
    {
        if(equal_cases(CASES_TARGETS_BOUFS[i], my_case)){
            ok = 1;
        }
    }
    return ok;
}



// ---------------------------------------------------------
// GESTION DES FICHIER
// ----------------------------------------------------------
// FONCTION POUR SAUVEGARDER UN ETAT

char *filename = "savegame/stat.save";

void save_stat(Case cases[]){

    FILE *fichier = fopen(filename, "w+");
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        fprintf(fichier, "%d ", cases[i].state);
    }
    fclose(fichier);

}


// FONCTION POUR RECUPERER UN ETAT
void get_stat(Case cases[]){

    FILE *fichier = fopen(filename, "r");
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        fscanf(fichier, "%d ", &cases[i].state);
    }
    fclose(fichier);

}

int verif_nbre_pion(Case cases[]){
    NBRE_BLANC = 0;
    NBRE_NOIR = 0;
    for (size_t i = 0; i < NOMBRE_CASES; i++)
    {
        if (cases[i].state == OCCUPE_1 || cases[i].state == DAME_1)
        {
            NBRE_NOIR++;
        }
        if (cases[i].state == OCCUPE_2 || cases[i].state == DAME_2)
        {
            NBRE_BLANC++;
        }
            
    }

    if (NBRE_BLANC == 0)
    {
       return NOIR_GAGNE;  
    }
    if (NBRE_NOIR == 0)
    {
       return BLANC_GAGNE;  
    }
    
    return 7;
    
}