//
//  TextureUtils.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 27/05/2022.
//

#include "TextureUtils.hpp"

SDL_Point TextureUtils::getsize(SDL_Texture *texture) {
    SDL_Point size;
    SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
    return size;
}

Uint32 TextureUtils::getPixel(SDL_Surface *surface, int x, int y)
{
    if(y < 0)
    {
        y = 0;
    }
    if(y > surface->h)
    {
        y = surface->h;
    }
    
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

switch (bpp)
{
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
      }
}


void TextureUtils::setPixel(SDL_Surface* surface, int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    Uint8 bpp = surface->format->BytesPerPixel;
    int pitch = surface->pitch;
    uint8_t * pixelsArr = (uint8_t *)surface->pixels;
    pixelsArr[y * pitch + x * bpp + 0] = b;
    pixelsArr[y * pitch + x * bpp + 1] = g;
    pixelsArr[y * pitch + x * bpp + 2] = r;
}

