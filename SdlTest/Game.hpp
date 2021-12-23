//
//  Game.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 23/12/2021.
//

#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <stdio.h>

class Game {
    
public:
    Game();
    ~Game();
    void init(const char* title, int xPos, int yPos, int width, int height, bool fulScreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running(){return  isRunning;}
    
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    
};
#endif
