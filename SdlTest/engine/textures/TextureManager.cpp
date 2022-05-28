//
//  TextureManager.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//
#include "SDL_Utils.hpp"
#include "TextureManager.hpp"


bool TextureManager::loadFromFile(TexureData& data, std::string path )
{
    //Get rid of preexisting texture

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to display format
        SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_GetWindowPixelFormat( SDL_Utils::window ), 0 );
        if( formattedSurface == NULL )
        {
            printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Create blank streamable texture
            newTexture = SDL_CreateTexture( SDL_Utils::renderer, SDL_GetWindowPixelFormat( SDL_Utils::window ), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
            if( newTexture == NULL )
            {
                printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Lock texture for manipulation
                SDL_LockTexture( newTexture, NULL, &data.mPixels, &data.mPitch );

                //Copy loaded/formatted surface pixels
                memcpy( data.mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

                //Unlock texture to update
                SDL_UnlockTexture( newTexture );

                //Get image dimensions
                data.mWidth = formattedSurface->w;
                data.mHeight = formattedSurface->h;
            }

            //Get rid of old formatted surface
            SDL_FreeSurface( formattedSurface );
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    data.mTexture = newTexture;
    return data.mTexture != NULL;
}





//SDL_Color *color=&fmt->palette->colors[index];
//SDL_PixelFormat *fmt = surface->format;



//this retrns raw pixel data
SDL_Surface* TextureManager::getSurface(std::string path)
{
    return IMG_Load(path.c_str());
}

void TextureManager::freeSurface(SDL_Surface* surface)
{
    SDL_FreeSurface(surface);
}

//this returns write only data
SDL_Texture* TextureManager::getTexture(SDL_Surface* surface)
{
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(SDL_Utils::renderer, surface);
    
    /*
     //lock if you want ro access pixels
     SDL_LockSurface(surface);
     
     SDL_FreeSurface(surf);
     // .. *and* the data used by the surface!
     stbi_image_free(data);
     */

    return texture;

}
