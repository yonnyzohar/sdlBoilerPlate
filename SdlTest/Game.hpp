//
//  Game.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 23/12/2021.
//

#ifndef Game_hpp
#define Game_hpp


#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "json.h"
#include "reader.h"
#include "value.h"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "AtlasObj.hpp"

class Game {
    
public:
    Game();
    ~Game();
    void init(const char* title, int xPos, int yPos, int width, int height, bool fulScreen);
    void handleEvents();
    virtual void update();
    void render();
    void clean();
    virtual void onloaded();
    virtual void draw();
    bool running(){return  isRunning;}
    
    static SDL_Renderer *renderer;
    static SDL_Event event;
    std::map<std::string, AtlasObj> m;
    
protected:
    bool isRunning;
    SDL_Window *window;
    
    
    
    
};
#endif
