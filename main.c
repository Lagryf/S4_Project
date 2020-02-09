#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <err.h>
#include <gtk/gtk.h>
#include "glade_function.h"

GtkWidget *g_Play;
GtkWidget *g_Pause;
GtkWidget *g_Stop;
GtkWidget *g_Begin;
GtkWidget *g_End;
GtkWidget *g_Restart;

int main(int argc, char** argv)
{
	GtkBuilder *builder; 
    GtkWidget *window;
    
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "GUITemp.glade", NULL);
	
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
	
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    
    g_Play = GTK_WIDGET(gtk_builder_get_object(builder, "Play"));
    g_Pause = GTK_WIDGET(gtk_builder_get_object(builder, "Pause"));
    g_Stop = GTK_WIDGET(gtk_builder_get_object(builder, "Stop"));
    g_Begin = GTK_WIDGET(gtk_builder_get_object(builder, "Begin"));
    g_End = GTK_WIDGET(gtk_builder_get_object(builder, "End"));
    g_Restart = GTK_WIDGET(gtk_builder_get_object(builder, "Restart"));
    
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
						on_Pause_clicked();
						break;
					//Resume
					case SDLK_r:
						on_Play_clicked();
						break;
					//Revenir au debut
					case SDLK_LEFT:
						on_Begin_clicked();
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
    
    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();
    
    Mix_FreeChunk(music);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();

    return 0;
}



// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

