//
//  TextureManager.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL.h>
#include "Utilities.hpp"
#include <stdio.h>

struct TexureData{
    SDL_Texture* mTexture;
    void* mPixels;
    int mPitch;

    //Image dimensions
    int mWidth;
    int mHeight;
    
};

struct Pixel{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class TextureManager{
public:
    static SDL_Surface* getSurface(std::string path);
    
    static bool loadFromFile( TexureData& data, std::string path );
    
    
    
    static void freeSurface(SDL_Surface* surface);

    //this returns write only data
    static SDL_Texture* getTexture(SDL_Surface* surface);
    
    
    
    
};


#endif /* TextureManager_hpp */
