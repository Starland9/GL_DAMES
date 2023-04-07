#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>



void play_sound(const char *filename, int loop){
    Mix_Music *music = Mix_LoadMUS(filename);
    Mix_PlayMusic(music, loop);
    
}


void play_background(){
    Mix_Music *music_bg = Mix_LoadMUS("audio/back.ogg");
    Mix_PlayMusic(music_bg, 1);
}