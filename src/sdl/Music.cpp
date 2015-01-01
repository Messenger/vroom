#include "Music.h"
#include <SDL2/SDL_mixer.h>

void Music::Start()
{
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    auto music = Mix_LoadMUS("content/background.ogg");
    Mix_PlayMusic(music, -1);
}

void Music::Update(const Time& time)
{

}
