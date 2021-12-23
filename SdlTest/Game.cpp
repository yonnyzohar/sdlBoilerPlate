#include "Game.hpp"

Game::Game()
{
    
}

Game::~Game()
{
    
}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fulScreen)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        uint flags = SDL_WINDOW_SHOWN;
        if(fulScreen)
        {
            flags = SDL_WINDOW_FULLSCREEN;
        }
        window  = SDL_CreateWindow(title,
                                   xPos,
                                   yPos,
                                   width, width, flags);
        
        if(window)
        {
            renderer = SDL_CreateRenderer(window, -1, 0);
            if(renderer)
            {
                SDL_SetRenderDrawColor(renderer, 100, 255, 100, 100);
                SDL_PumpEvents();
                
                isRunning = true;
                
            }
        }
    }
    else
    {
        isRunning = false;
    }
    
}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
            
        default:
            break;
    }
    
}
void Game::render(){
    SDL_RenderClear(renderer);
    ///here
    SDL_RenderPresent(renderer);
}
void Game::clean(){
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::update()
{
    
}
