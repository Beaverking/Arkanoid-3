#include <SDL_mixer.h>
#include "audio.h"
#include "game.h"

Mix_Chunk* beep;
Mix_Music* music;

void LoadAudioFiles()
{
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    beep = Mix_LoadWAV("assets/beep.wav");


    music = Mix_LoadMUS("assets/music.mp3");
    
    if (beep == NULL)
    {
        printf("Failed to load beep sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    if (music == NULL)
    {
        printf("Failed to load music file! SDL_mixer Error: %s\n", Mix_GetError());
    }
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(64);

}

void PlayBeep()
{
    Mix_PlayChannel(-1, beep, 0);
}
