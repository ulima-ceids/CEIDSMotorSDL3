#include "file_management.h"
#include <string>
#include <spdlog/spdlog.h>
#include <tuple>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <random>

struct Megaman
{
    float posX;
    float posY;
    float velocidadX;
    float velocidadY;
    SDL_Texture* textura;
};

std::vector<Megaman> SpawnearMegamans(int cantidad, SDL_Texture* textura)
{

}

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        // error
        spdlog::error("Error inicializando SDL");
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Ejercicio Individual 1", 
        800, 
        600,
        SDL_WINDOW_FULLSCREEN
    );
    if (window == nullptr)
    {
        spdlog::error("Error creando ventana SDL");
        return -1;
    }

    SDL_Renderer* renderer =  SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr)
    {
        spdlog::error("Error obteniendo renderer SDL");
        return -1;
    }

    SDL_Surface* surface = IMG_Load("./assets/megaman.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    bool isRunning = true;
    
    while (isRunning)
    {
        // Getting Input data from player
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    isRunning = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (!event.key.repeat &&
                        event.key.key == SDLK_ESCAPE) 
                    {
                        isRunning = false;
                    }
                    break;
            }
        }


        // Updating
        Megaman m{100.f, 100.f, 0.f, 0.f, texture};

        // Renderer

        SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
        SDL_RenderClear(renderer);

        SDL_FRect rectMegaman{
            m.posX, 
            m.posY,
            60,
            68 
        };
        SDL_RenderTexture(
            renderer, 
            m.textura,
            nullptr,
            &rectMegaman
        );

        SDL_RenderPresent(renderer);
    }

    return 0;
}