//
//  BattleZone.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 11/03/2022.
//

#include "BattleZone.hpp"


BattleZone::BattleZone()
{
   // player = new Player(200.0f, 200.0f);
    
}

SDL_Surface* surface = nullptr;


void BattleZone::onloaded()
{
    
    //surface = TextureManager::getSurface(imgPath);
    //TextureManager::loadFromFile(data, imgPath);
    //SDL_LockSurface(surface);

   // SDL_memset(surface->pixels, 0, surface->h * surface->pitch);
    //std::string a = typeof( surface->pixels[1] );
    
    //
    //std::cout << a << " found " << std::endl;
    
    std::string imgPath = "/Users/yonnizohar/Desktop/c++ projects/SdlTest/SdlTest/assets/img.png";
    SDL_Surface* surface = TextureManager::getSurface(imgPath);
    SDL_Texture* texture = TextureManager::getTexture(surface);
    
    Camera3d::init(Point3d::create(0, 0, 0),Point3d::create(0, 0, 0));
    cube1 = new Cube(Point3d::create(0, 0, 1000), Point3d::create(0, 0, 0), 1, surface);
    entities3d.push_back(cube1);

}

void BattleZone::update(int dt)
{
    super::update(dt);
    
    //player->update();
}

void BattleZone::draw(int dt)
{
    //Allocate format from window
    //SDL_LockTexture( texture );
    /*
    Uint32 format = SDL_GetWindowPixelFormat( Game::window );
    SDL_PixelFormat* mappingFormat = SDL_AllocFormat( format );

    //Get pixel data
    Uint32* pixels = (Uint32*)data.mPixels;
    int pixelCount = ( data.mPitch / 4 ) * data.mHeight;

    //Map colors
    Uint32 colorKey = SDL_MapRGB( mappingFormat, 0, 0xFF, 0xFF );
    Uint32 transparent = SDL_MapRGBA( mappingFormat, 0xFF, 0xFF, 0xFF, 0x00 );

    //Color key pixels
    for( int i = 0; i < pixelCount; ++i )
    {
        if( pixels[ i ] == colorKey )
        {
            pixels[ i ] = transparent;
        }
    }

    //Unlock texture
    SDL_UnlockTexture( texture );

    //Free format
    SDL_FreeFormat( mappingFormat );
    
    
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 100;
    srcRect.h = 100;

    //SDL_RenderCopy(Utilities::renderer, texture,&srcRect, &srcRect);//,
    
    
    Pixel p;
    */
    //SDL_PixelFormat *fmt = surface->format;
    
    
    /*
    for(int y = 0; y < 100; y++)
    {
        for(int x = 0; x < 100; x++)
        {
            Uint32 pixel = TextureManager::getPixel( surface, x, y);
            SDL_Color *color=&fmt->palette->colors[pixel];
            SDL_SetRenderDrawColor(Utilities::renderer, color->r, color->g, color->b, 255);
            SDL_RenderDrawPoint(Utilities::renderer, x , y);
        }
    }
     */
    
    super::draw( dt);
    
    
}



