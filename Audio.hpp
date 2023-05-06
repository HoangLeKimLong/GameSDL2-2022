#pragma once
#include "SDL_mixer.h"

void Music() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Chunk* sound = Mix_LoadWAV("Music.wav");
    Mix_PlayChannel(-1, sound, 10);
    while (Mix_Playing(-1)) {
        SDL_Delay(100);
    }
    Mix_FreeChunk(sound);
    Mix_CloseAudio();

}
class AUDIO
{
public:

};
