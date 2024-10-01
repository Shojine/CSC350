#include "Renderer.h"

bool Renderer::Initalize()
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool Renderer::CreateWindow()
{
    // create window
    // returns pointer to window if successful or nullptr if failed
    m_window = SDL_CreateWindow("Game Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
    {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    return true;
}

void Renderer::RenderClear()
{
    SDL_RenderClear(m_renderer);
}

void Renderer::RenderPresent()
{
    SDL_RenderPresent(m_renderer);
}

void Renderer::SetRenderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}
