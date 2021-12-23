//
//  main.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 23/12/2021.
///Library/Frameworks/SDL2.framework/Versions/A/Headers/

#include "Game.hpp"
#include <iostream>

Game *game = nullptr;

//setting up basis sdl window
//https://www.youtube.com/watch?v=lHAUc6F_B3Y
//sdl must be dwonloaded and placed under Library/frameWorks/ and connected to this project under "Build Phases"->"Link binaries with libraries.
//important!!! for this work- under signing&capabilities, "hardened runtime" mut be true, and underneath it,
//Disble Library Validation must be checked. otherwise apple will not let sdl work
int main() {
    
    game = new Game();
    game->init("yonny", 0, 0, 800, 600, false);
    while(game->running())
    {
        game->handleEvents();
        game->update();
        game->render();
    }
    
    game->clean();

    
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

