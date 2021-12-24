//
//  GameObject.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//
#include "GameObject.hpp"

GameObject::GameObject(AtlasObj *o, int w, int h)
{
    atlas = o;
    Json::Value data = o->data["frames"]["IDLE_E0000"]["frame"];
    
    srcRect.x = data["x"].asInt();
    srcRect.y = data["y"].asInt();
    srcRect.w = data["w"].asInt();
    srcRect.h = data["h"].asInt();
    
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = w;
    destRect.h = h;
    
}

void GameObject::update()
{
    
}
void GameObject::render()
{
    SDL_RenderCopy(Game::renderer, atlas->texture, &srcRect, &destRect);
}
void GameObject::destroy()
{
    
}
