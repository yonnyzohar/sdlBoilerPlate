//
//  GameObject.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "TextureManager.hpp"
#include "AtlasObj.hpp"
#include <stdio.h>
#include "Utilities.hpp"
#include "Camera2d.hpp""
#include <iostream>

class GameObject{
public:
    GameObject(AtlasObj *o, int x, int y, int w, int h);
    ~GameObject();
    virtual void update();
    void render(int dt);
    void destroy();
    void setAnimFrame(std::string _name);
    void setFrame(std::string _name, int frameNum = 0) ;
    std::string prevState;
    float x;
    float y;
    int identifier;
    
protected:
    
    SDL_Rect srcRect;
    SDL_Rect destRect;
    AtlasObj *atlas;
    int frameCounter = 0;
    int destW;
    int destH;
    int timeCounter = 0;
    //SDL_Texture *myTexture;
   // Json::Value *myData;
    
};

#endif /* GameObject_hpp */
