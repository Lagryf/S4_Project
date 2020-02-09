#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <err.h>


void play_music()
{
        Mix_Resume(1);
}


void pause_music()
{
        Mix_Pause(1);
}


void stop_music()
{
    Mix_HaltChannel(1);
}


void begin_music()
{
	Mix_RewindMusic();
}


void end_music()
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
