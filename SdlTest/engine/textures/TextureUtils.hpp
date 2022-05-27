//
//  TextureUtils.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 27/05/2022.
//

#ifndef TextureUtils_hpp
#define TextureUtils_hpp

#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>

class TextureUtils{
public:
    static Uint32 getPixel( SDL_Surface *surface, int x, int y);
    static void setPixel( SDL_Surface* surface, int x, int y, uint8_t r, uint8_t g, uint8_t b );
    static SDL_Point getsize(SDL_Texture *texture);
};


#endif /* TextureUtils_hpp */
