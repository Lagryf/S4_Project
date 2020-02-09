#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <err.h>
#include "glade_function.h"


int main(int argc, char** argv)
{
	
	//Initialisation de SDL et SDL_MIXER
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	int flags = MIX_INIT_FLAC|MIX_INIT_MOD|MIX_INIT_MP3|MIX_INIT_OGG;
	int initted = Mix_Init(flags);
	
	//Detection d'erreur
	
	if(initted&flags != flags) 
	{
		printf("Mix_Init: Failed to init required ogg and mod support!\n");
		printf("Mix_Init: %s\n", Mix_GetError());
	}
	
	//Definition des variables importantes
	
	int volume = 128;
	Mix_AllocateChannels(16);
	SDL_Surface* screen;
    Mix_Chunk* music;
    SDL_Event event;
    int running = 1;
    int i = 2;
    if(argc == 3)
    {
		i = *argv[2]%48;
		printf("%i\n",i);
	}
    
	//Detection des arguments
	
	if(argc < 2)
	{
		printf("This program need at least 1 argument. Example : ./a.out my_music.mp3\n");
		exit(1);
	} 
  
	//Ouverture de Mix avec detection d'erreur
	
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, i, 4096) == -1)
	{
		printf("An error has occured : %s\n",Mix_GetError());
		exit(1);
	}	
	
	//Chargement du fichier et de l'ecran
	
    music = Mix_LoadWAV(argv[1]);
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    
    //Joue le fichier avec detection d'erreur
    if(Mix_PlayChannel(1,music, -1) == -1)
    {
        printf("An error has occured : %s\n",Mix_GetError());
        exit(1);
    }
	
	//boucle des raccoucis claviers
    while(running == 1) 
    {
		
       SDL_WaitEvent(&event);
        switch(event.type)
        {
			case SDL_QUIT:
				running = 0;
				printf("\n");
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					//Pause
					case SDLK_p:
						pause_music();
						break;
					//Resume
					case SDLK_r:
						play_music();
						break;
					//Revenir au debut
					case SDLK_LEFT:
						begin_music();
						break;
					//Augmenter le volume
					case SDLK_UP:
                        volume = higher_volume(volume);	
						break;
					//Baisser le volume
					case SDLK_PAGEUP:
						Reverse_Stereo(1);
						break;
                    case SDLK_DOWN:
                        volume = lower_volume(volume);
						break;
					//Quitter
					case SDLK_q:
						running = 0;
						printf("\n");
						break;
					
					
				}
				break;
        }
    }
    
    //Liberation de la memoire utilisee
    
    Mix_FreeChunk(music);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();

    return 0;
}

