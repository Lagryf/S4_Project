#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		printf("the program needs 2 argument : The file to convert and the name and extension of the file converted\nExample : ./convert mymusic.wav mymusic.mp3\n");
		exit(1);
	}
	FILE * fichier = fopen(argv[2], "r+");
	if (fichier != NULL)
	{
		printf("the file already exist\n");
		fclose(fichier);
		exit(1);
	}

	char s1[500] = "ffmpeg -i ";
	strcat(s1,argv[1]);	
	strcat(s1," ");
	strcat(s1,argv[2]);
	char s2[] = " &> /dev/null";
	strcat(s1,s2);
	int status = system(s1);
	if(status != 0)
	{
		printf("convert failed !\n");
		exit(1);
	}
	printf("file converted !\n");
	return 0;
}
