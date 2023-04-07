#include <SDL2/SDL.h>
#include <stdio.h>

// #include "Structs.h"



// Case 
typedef struct Case
{
    SDL_Rect rect;
    int state;
    int selection_type;
    int to_bouf;
  
}Case;


// BOUTONS
typedef struct Bouton
{
    SDL_Rect rect;
    int selection_type;
    int function;

}Bouton;




// // FONCTION QUI RECOLORIE TOUTES LES CASES
// void recolor_cases(SDL_Renderer *rendu, SDL_Rect *rect[]);

// PREMIERE FONCTION QUI INITIALISE LES CASES, LEUR ATTRIBUT, LEUR OCUPATION ET LEUR POSITION PAR DEFAUT
void init_cases(Case cases[]);

//FONCTION QUI DESSINE LE TABLEAU DE CASES SUR LE RENDU 
void draw_cases(SDL_Renderer **rendu, Case cases[]);

// FONCTION QUI CREER DIRECTEMENT UNE TEXTURE IMAGE
SDL_Texture* load_img(SDL_Renderer **rendu, const char *file);

// FONCTION HOVER SUR UNE CASE
void hover(SDL_Point *point, Case cases[]);

// FONCTION QUI TROUVE LES TARGET
void set_targets(Case cases[], Case my_case);

// FONCTION QUI RESET TOUTES LES TARGETS
void reset_targets(Case cases[]);

// FONCTION DE DEPLACEMENT DU PION
int deplacement(int JOUEUR, Case cases[], Case de_case, Case vers_case);

// FONCTION QUI DEVOILE LES MANGEMENTS !!!
int set_pick(Case cases[], Case selected_case);




// ----------------GESTION DES DAMES--------------------------------------

void set_targets_dames(Case cases[], Case my_case);

// FONCTION QUI DONNE LES TARGETS DES DAMES SUR LA POSITION DONNEE
void target_at_pos_dames(Case cases[], Case selected_case, int position);

// FONCTION QUI DEVOILE LES MANGEMENTS DES DAMES !!!
int set_pick_dames(Case cases[], Case selected_case);


//
// FONCTION QUI GERE LES CHOSES AUTOMATIQUEMENT SUR LE DAMIER
// FONCTION TRES COMPLEXE LANDRY!!!!!!!
void auto_dame(Case cases[]);

// FONCTION QUI REND LIBRE TOUTES LES CASES BOUFEES PAR LA DAME
void bouf_of_dame(Case cases[]);

// FONCTION QUI REINITIALISE TOUTES LES CASES DE BOUF
void reset_cases_bouf_dame(Case cases_bouf[]);

// FONCTION QUI RESET TOUTES LES TARGETS QUI NE SONT PAS ROUGE !!
void reset_targets_red(Case cases[]);

// FONCTION QUI REINITIALISE LE TABLEAU CONTENANT LES CASES QUI DOIVENT DECLANCHER LE MANGEMENT DU ROI
void reset_cases_target_boufs();

// FONCTION QUI VERIFIE SI LA CASE CLIQUE EST LA BONNE POUR DECLANCHER LA BOUFE DU ROI
int in_cases_target_bouf(Case my_case);

//Fonction qui reset les cases a bouffe
void reset_boufs(Case cases[]);


//Fonction qui verifie si une case est seule afin de la manger
int possible_bouf(Case my_case, Case cases[]);



// FONCTION POUR SAUVEGARDER UN ETAT
void save_stat( Case cases[]);

// FONCTION POUR RECUPERER UN ETAT
void get_stat(Case cases[]);

// Fonction qui verifie le nombre de pion sur le plateau
int verif_nbre_pion(Case cases[]);