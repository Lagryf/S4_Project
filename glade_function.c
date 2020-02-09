#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <err.h>


void on_Play_clicked()
{
    Mix_Resume(1);
}


void on_Pause_clicked()
{
    Mix_Pause(1);
}


void on_Stop_clicked()
{
    Mix_HaltChannel(1);
}


void on_Begin_clicked()
{
	Mix_RewindMusic();
}


void on_End_clicked()
{

}

void on_Restart_clicked()
{

}


int lower_volume(int volume)
{
	if(volume < 0)
	{
		volume = 0;
		return volume;
	}
		volume -= 20;
		Mix_Volume(1,volume);
	return volume;
}

int higher_volume(int volume)
{
	if(volume > 128)
	{
		volume = 128;
		return volume;
	}
	volume += 20;
	Mix_Volume(1, volume);
	return volume;
}

void Reverse_Stereo(int channel)
{
	if(!Mix_SetReverseStereo(1, 1)) 
	{
		printf("Mix_SetReverseStereo: %s\n", Mix_GetError());
	}
}

void Mix_Stereo(int channel, int left, int right)
{
	if(!Mix_SetPanning(1, 255, 127)) 
	{
		printf("Mix_SetPanning: %s\n", Mix_GetError());
	}
}
