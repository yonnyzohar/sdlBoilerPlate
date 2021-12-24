#include "Game.hpp"


SDL_Renderer *Game::renderer = nullptr;

SDL_Event Game::event;

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
            Game::renderer = SDL_CreateRenderer(window, -1, 0);
            if(Game::renderer)
            {
                SDL_SetRenderDrawColor(Game::renderer, 100, 255, 100, 100);
                
                

                isRunning = true;
                //this is where we know that sdl window is ready
                onloaded();
                
                
                
                
               // SDL_PumpEvents();
                
                
            }
        }
    }
    else
    {
        isRunning = false;
    }
    
}


void Game::onloaded()
{
    
}

void Game::handleEvents(){
    
    SDL_PollEvent(&Game::event);
    switch (Game::event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (Game::event.key.keysym.sym){
                case SDLK_w:
                    break;
                case SDLK_a:
                    break;
                case SDLK_s:
                    break;
                case SDLK_d:
                    break;
                default:
                    break;
            }
            
            break;
        case SDL_KEYUP:
            break;
            
        default:
            break;
    }
    
}

void Game::update()
{
    
}

void Game::draw()
{
    
}


void Game::render(){
    SDL_RenderClear(Game::renderer);
    ///this is where we handle out game in the MyGame clas - the actual implementation
    draw();
    ////
    SDL_RenderPresent(Game::renderer);
}
void Game::clean(){
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
}


