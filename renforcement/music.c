#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int main()
{
/* On déclare la variable qui représentera notre musique une fois chargée */
    Mix_Music* myMus;

    /* On initialise le son */
    SDL_Init(SDL_INIT_AUDIO);

    /* On ouvre un device audio */
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

    /* On charge un fichier musical */
    myMus = Mix_LoadMUS("WATRWave_Mer vagues (ID 0266)_LS.wav");

    /* On lance la musique */
    Mix_PlayMusic(myMus, 1);

    while (Mix_PlayingMusic() == 1)
    {
        /* Tant que la musique n'est pas terminée, on fait quelque chose
           car sinon le programme s'éteint et le son aussi */
        SDL_Delay(10);
    }

    /* La musique est terminée, on la libère */
    Mix_FreeMusic(myMus);

    /* On libère le matériel */
    Mix_CloseAudio();

    return 0;
}