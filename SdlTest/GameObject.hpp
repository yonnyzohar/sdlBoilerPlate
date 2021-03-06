//
//  GameObject.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "TextureManager.hpp"
#include "Game.hpp"
#include "AtlasObj.hpp"
#include <stdio.h>

class GameObject{
public:
    GameObject(AtlasObj *o, int w, int h);
    ~GameObject();
    void update();
    void render();
    void destroy();
    
private:
    int x;
    int y;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    AtlasObj *atlas;
    //SDL_Texture *myTexture;
   // Json::Value *myData;
    
};

#endif /* GameObject_hpp */
