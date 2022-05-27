//
//  GameObject.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//
#include "GameObject.hpp"

GameObject::GameObject(AtlasObj *o, int _x, int _y, int _w, int _h)
{
    atlas = o;
    x = _x;
    y = _y;
    destW = _w;
    destH = _h;
}

void GameObject::setFrame(std::string _name, int frameNum ) {
    frameCounter = frameNum;
    std::string key =_name + Utilities::getZeros(frameCounter, atlas->numZeros);
    if(atlas->frames.find(  key ) != atlas->frames.end()){
        Frame &frame = atlas->frames[key];
        srcRect.x = frame.x;
        srcRect.y = frame.y;
        srcRect.w = frame.w;
        srcRect.h = frame.h;
        //destW = frame.destW;
        //destH = frame.destH;
    }
    prevState = _name;
}

void GameObject::setAnimFrame(std::string _name) {
    
   //std::string id = std::to_string(identifier);
    
    if (_name.compare(prevState) != 0)
    {
       // std::cout << id << " " << _name << " is not equal to " << prevState << std::endl;
        frameCounter = 0;
    } else {

        frameCounter++;
       // std::cout << id << " " << _name << " is equal to " << prevState << std::endl;
        
    }
    std::string key =_name + Utilities::getZeros(frameCounter, atlas->numZeros);
    if(atlas->frames.find(  key ) != atlas->frames.end()){
        
        //std::cout << id << " found " << key << std::endl;
        
        Frame &frame = atlas->frames[key];
        srcRect.x = frame.x;
        srcRect.y = frame.y;
        srcRect.w = frame.w;
        srcRect.h = frame.h;
        destW = frame.destW;
        destH = frame.destH;
    }
    else
    {
        frameCounter = 0;
        key =_name + Utilities::getZeros(frameCounter, atlas->numZeros);
        
        //std::cout << id << " found " << key << std::endl;
        
        Frame &frame = atlas->frames[key];
        srcRect.x = frame.x;
        srcRect.y = frame.y;
        srcRect.w = frame.w;
        srcRect.h = frame.h;
        destW = frame.destW;
        destH = frame.destH;
    }


    prevState = _name;

}

void GameObject::update()
{
    destRect.x = (int)(x + SDL_Utils::cam->x);
    destRect.y = (int)(y + SDL_Utils::cam->y);
    destRect.w = (int)destW;
    destRect.h = (int)destH;
}
void GameObject::render(int dt)
{
    SDL_RenderCopy(SDL_Utils::renderer, atlas->texture, &srcRect, &destRect);
}
void GameObject::destroy()
{
    
}

GameObject::~GameObject()
{
    
}
